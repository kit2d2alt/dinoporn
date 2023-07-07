#include <Server/Server.h>

#include <assert.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include <libwebsockets.h>

#include <Server/Client.h>
#include <Server/Logs.h>
#include <Server/Simulation.h>
#include <Shared/Bitset.h>
#include <Shared/Component/Physical.h>
#include <Shared/Crypto.h>
#include <Shared/Rivet.h>
#include <Shared/Utilities.h>
#include <Shared/Vector.h>
#include <Shared/pb.h>

#ifndef NDEBUG
#define MESSAGE_BUFFER_SIZE (32 * 1024 * 1024)
#else
#define MESSAGE_BUFFER_SIZE (1024 * 1024)
#endif
static uint8_t lws_message_data[MESSAGE_BUFFER_SIZE];
static uint8_t *outgoing_message = lws_message_data + LWS_PRE;

void rr_server_client_create_player_info(struct rr_server_client *this)
{
    puts("creating player info");
    this->player_info = rr_simulation_add_player_info(
        &this->server->simulation,
        rr_simulation_alloc_entity(&this->server->simulation));
    rr_component_player_info_set_slot_count(this->player_info, 10);
    for (uint64_t i = 0; i < this->player_info->slot_count; ++i)
    {
        uint8_t id = this->player_info->slots[i].id = this->loadout[i].id;
        uint8_t rarity = this->player_info->slots[i].rarity =
            this->loadout[i].rarity;
        this->player_info->slots[i].count = RR_PETAL_DATA[id].count[rarity];
        this->player_info->secondary_slots[i].id = this->loadout[i + 10].id;
        this->player_info->secondary_slots[i].rarity =
            this->loadout[i + 10].rarity;
    }
    // rr_server_client_create_flower(this);
}

void rr_server_client_free(struct rr_server_client *this)
{
    puts("client disconnected");
    if (this->server->simulation_active)
    {
        if (this->player_info->flower_id != RR_NULL_ENTITY)
            rr_simulation_request_entity_deletion(&this->server->simulation,
                                                  this->player_info->flower_id);
        rr_simulation_request_entity_deletion(&this->server->simulation,
                                              this->player_info->parent_id);
    }
}

void rr_server_client_encrypt_message(struct rr_server_client *this,
                                      uint8_t *start, uint64_t size)
{
    this->clientbound_encryption_key =
        rr_get_hash(this->clientbound_encryption_key);
    rr_encrypt(start, size, this->clientbound_encryption_key);
}

void rr_server_client_write_message(struct rr_server_client *this,
                                    uint8_t *message_start, uint64_t size)
{
    lws_write(this->socket_handle, message_start, size, LWS_WRITE_BINARY);
}

void rr_server_client_broadcast_update(struct rr_server_client *this)
{
    struct rr_server *server = this->server;
    // 128 KB (not needed but just in case)
    struct proto_bug encoder;
    proto_bug_init(&encoder, outgoing_message);
    proto_bug_write_uint8(&encoder, 0, "header");
    rr_simulation_write_binary(&server->simulation, &encoder,
                               this->player_info);
    rr_server_client_encrypt_message(this, encoder.start,
                                     encoder.current - encoder.start);
    rr_server_client_write_message(this, encoder.start,
                                   encoder.current - encoder.start);
}

void rr_server_client_tick(struct rr_server_client *this)
{
    if (this->server->simulation_active)
    {
        if (rr_simulation_has_entity(&this->server->simulation,
                                     this->player_info->flower_id))
        {
            struct rr_component_physical *physical = rr_simulation_get_physical(
                &this->server->simulation, this->player_info->flower_id);
            rr_component_player_info_set_camera_x(this->player_info,
                                                  physical->x);
            rr_component_player_info_set_camera_y(this->player_info,
                                                  physical->y);
            rr_vector_set(&physical->acceleration, this->player_accel_x,
                          this->player_accel_y);
        }
        rr_server_client_broadcast_update(this);
    }
    else
    {
        // 128 KB (not needed but just in case)
        struct proto_bug encoder;
        proto_bug_init(&encoder, outgoing_message);
        proto_bug_write_uint8(&encoder, 69, "header");
        proto_bug_write_uint8(
            &encoder, this->server->ticks_until_simulation_create, "countdown");
        for (uint32_t i = 0; i < 4; ++i)
        {
            proto_bug_write_uint8(
                &encoder, rr_bitset_get(&this->server->clients_in_use[0], i),
                "bitbit");
            proto_bug_write_uint8(&encoder, this->server->clients[i].ready,
                                  "ready");
            for (uint8_t j = 0; j < 20; ++j)
            {
                proto_bug_write_uint8(
                    &encoder, this->server->clients[i].loadout[j].id, "id");
                proto_bug_write_uint8(
                    &encoder, this->server->clients[i].loadout[j].rarity,
                    "rar");
            }
        }
        rr_server_client_encrypt_message(this, encoder.start,
                                         encoder.current - encoder.start);
        rr_server_client_write_message(this, encoder.start,
                                       encoder.current - encoder.start);
        // send squad info
    }
}

static void delete_entity_function(EntityIdx entity, void *_captures)
{
    rr_simulation_request_entity_deletion(_captures, entity);
}

int rr_server_lws_callback_function(struct lws *socket,
                                    enum lws_callback_reasons reason,
                                    void *context, void *packet, size_t size)
{
    struct rr_server *this =
        (struct rr_server *)lws_context_user(lws_get_context(socket));
    switch (reason)
    {
    case LWS_CALLBACK_ESTABLISHED:
    {
        if (this->simulation_active)
            return 0;
        for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
            if (!rr_bitset_get_bit(this->clients_in_use, i))
            {
                rr_bitset_set(this->clients_in_use, i);
                rr_server_client_init(this->clients + i);
                this->clients[i].server = this;
                this->clients[i].file_descriptor = lws_get_socket_fd(socket);
                this->clients[i].socket_handle = socket;
                lws_get_peer_simple(socket, this->clients[i].ip_address, 100);
                char log[100] = {"ip: `"};
                strcat(log, this->clients[i].ip_address);
                strcat(log, "`");
                // rr_discord_webhook_log("player status", "client connected",
                // log, 0x44ff44);

                // send encryption key
                struct proto_bug encryption_key_encoder;
                proto_bug_init(&encryption_key_encoder, outgoing_message);
                proto_bug_write_uint64(&encryption_key_encoder,
                                       this->clients[i].requested_verification,
                                       "verification");
                proto_bug_write_uint32(&encryption_key_encoder, rr_get_rand(),
                                       "useless bytes");
                proto_bug_write_uint64(
                    &encryption_key_encoder,
                    this->clients[i].clientbound_encryption_key,
                    "c encryption key");
                proto_bug_write_uint64(
                    &encryption_key_encoder,
                    this->clients[i].serverbound_encryption_key,
                    "s encryption key");
                rr_encrypt(outgoing_message, 1024, 21094093777837637ull);
                rr_encrypt(outgoing_message, 8, 1);
                rr_encrypt(outgoing_message, 1024, 59731158950470853ull);
                rr_encrypt(outgoing_message, 1024, 64709235936361169ull);
                rr_encrypt(outgoing_message, 1024, 59013169977270713ull);
                rr_server_client_write_message(this->clients + i,
                                               outgoing_message, 1024);
                return 0;
            }
        RR_UNREACHABLE("max clients reached");
    }
    case LWS_CALLBACK_CLOSED:
    {
        int file_descriptor = lws_get_socket_fd(socket);
        for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
            if (rr_bitset_get(this->clients_in_use, i))
            {
                if (this->clients[i].file_descriptor == file_descriptor)
                {
                    rr_bitset_unset(this->clients_in_use, i);
#ifdef RIVET_BUILD
                    rr_rivet_players_disconnected(
                        getenv("RIVET_LOBBY_TOKEN"),
                        this->clients[i].rivet_player_token);
#endif
                    rr_server_client_free(this->clients + i);
                    char log[100] = {"ip: `"};
                    strcat(log, this->clients[i].ip_address);
                    strcat(log, "`");
                    // rr_discord_webhook_log("player status", "client
                    // disconnected", log, 0xff4444);
                    return 0;
                }
            }
        RR_UNREACHABLE("cloudn't remove client");
    }

    case LWS_CALLBACK_RECEIVE:
    {
        if (size == 0)
            break;
        struct rr_server_client *client = NULL;
        uint64_t i = 0;
        for (; i < RR_MAX_CLIENT_COUNT; i++)
        {
            if (!rr_bitset_get(this->clients_in_use, i))
                continue;
            if (this->clients[i].file_descriptor == lws_get_socket_fd(socket))
            {
                client = &this->clients[i];
                break;
            }
        }
        if (client == NULL)
        {
            puts("null client????");
            return 0;
        }

        rr_decrypt(packet, size, client->serverbound_encryption_key);
        client->serverbound_encryption_key =
            rr_get_hash(rr_get_hash(client->serverbound_encryption_key));

        struct proto_bug encoder;
        proto_bug_init(&encoder, packet);

        if (!client->received_first_packet)
        {
            client->received_first_packet = 1;
            if (size < 16)
            {
                fputs("skid gaming1", stderr);
                lws_close_reason(
                    socket, LWS_CLOSE_STATUS_MESSAGE_TOO_LARGE /* troll */,
                    (uint8_t *)"script kiddie1", sizeof "script kiddie");
                return 1;
            }

            proto_bug_read_uint64(&encoder, "useless bytes");
            uint64_t received_verification =
                proto_bug_read_uint64(&encoder, "verification");
            if (received_verification != client->requested_verification)
            {
                fputs("skid gaming2", stderr);
                lws_close_reason(socket, LWS_CLOSE_STATUS_MESSAGE_TOO_LARGE,
                                 (uint8_t *)"script kiddie2",
                                 sizeof "script kiddie");
                return 1;
            }

#ifdef RIVET_BUILD
            uint64_t encountered_size =
                proto_bug_read_varuint(&encoder, "rivet token size");
            if (16 + encountered_size >= size)
            {
                printf("%lu %lu\n", size, encountered_size);
                fputs("skid gaming3", stderr);
                lws_close_reason(socket, LWS_CLOSE_STATUS_MESSAGE_TOO_LARGE,
                                 (uint8_t *)"script kiddie3",
                                 sizeof "script kiddie");
                return 1;
            }
            this->clients[i].rivet_player_token = malloc(encountered_size + 1);
            this->clients[i].rivet_player_token[encountered_size] =
                0; // don't forget the null terminator lol
            proto_bug_read_string(&encoder, this->clients[i].rivet_player_token,
                                  encountered_size, "rivet token");
            if (!rr_rivet_players_connected(
                    getenv("RIVET_LOBBY_TOKEN"),
                    this->clients[i].rivet_player_token))
            {
                fputs("skid gaming4", stderr);
                lws_close_reason(socket, LWS_CLOSE_STATUS_MESSAGE_TOO_LARGE,
                                 (uint8_t *)"script kiddie4",
                                 sizeof "script kiddie");
                return 1;
            }
#endif

            puts("socket verified");
            client->verified = 1;

            return 0;
        }
        switch (proto_bug_read_uint8(&encoder, "header"))
        {
        case 0:
        {
            if (size < 3)
            {
                puts("unsafe input packet with length < 3");
                return 0;
            }
            proto_bug_read_uint8(&encoder, "movement type");
            uint64_t movementFlags =
                proto_bug_read_uint8(&encoder, "movement kb flags");
            float x = 0;
            float y = 0;

            if (movementFlags & 1)
                y--;
            if (movementFlags & 2)
                x--;
            if (movementFlags & 4)
                y++;
            if (movementFlags & 8)
                x++;
            if (client->player_info == NULL)
                break;
            if (client->player_info->flower_id == 0)
                break;
            if (x != 0 && y != 0)
            {
                // 1 / sqrt(2)
                x *= 0.70710678118;
                y *= 0.70710678118;
            }
            client->player_accel_x = x;
            client->player_accel_y = y;
            client->player_info->input = movementFlags >> 4;
            break;
        }
        case 1:
        {
            // if (size < 1)
            // {
            //     puts("someone sent a spawn packet with size < 1");
            //     return 0;
            // }
            // rr_server_client_create_flower(client);
            // ctor player
            break;
        }
        case 2:
        {
            if (size < 2)
            {
                puts("someone sent a petal switch packet with size < 2");
                return 0;
            }
            if (client->player_info->flower_id == RR_NULL_ENTITY)
                return 0;
            uint8_t pos = proto_bug_read_uint8(&encoder, "petal switch");
            struct rr_component_player_info_petal_slot *slot =
                &client->player_info->slots[pos];
            struct rr_component_player_info_petal_slot *s_slot =
                &client->player_info->secondary_slots[pos];
            for (uint32_t i = 0; i < slot->count; ++i)
            {
                EntityIdx id = slot->petals[i].simulation_id;
                if (id != RR_NULL_ENTITY &&
                    rr_simulation_has_entity(&this->simulation, id))
                {
                    struct rr_component_physical *physical =
                        rr_simulation_get_physical(&this->simulation, id);
                    struct rr_component_health *health =
                        rr_simulation_get_health(&this->simulation, id);

                    rr_component_health_set_health(health, 0);
                    rr_component_physical_set_server_animation_tick(physical, 6);

                    slot->petals[i].simulation_id = RR_NULL_ENTITY;
                }
            }
            uint8_t temp = slot->id;
            slot->id = s_slot->id;
            s_slot->id = temp;
            temp = slot->rarity;
            slot->rarity = s_slot->rarity;
            s_slot->rarity = temp;

            slot->count = RR_PETAL_DATA[slot->id].count[slot->rarity];
            for (uint32_t i = 0; i < slot->count; ++i)
                slot->petals[i].cooldown_ticks =
                    RR_PETAL_DATA[slot->id].cooldown;
            break;
        }
        case 3:
        {
#ifndef RIVET_BUILD
            if (size < 2)
                return 0;
            puts("cheat used");
            uint8_t cheat_type = proto_bug_read_uint8(&encoder, "cheat type");
            if (cheat_type == 1)
            {
                puts("incr");
                // increment
                struct rr_component_arena *arena =
                    rr_simulation_get_arena(&this->simulation, 1);
                rr_component_arena_set_wave_tick(arena, 0);
                rr_component_arena_set_wave(arena, arena->wave + 1);
                rr_simulation_for_each_mob(&this->simulation, &this->simulation,
                                           delete_entity_function);
                rr_simulation_for_each_drop(&this->simulation,
                                            &this->simulation,
                                            delete_entity_function);
                rr_simulation_for_each_petal(&this->simulation,
                                             &this->simulation,
                                             delete_entity_function);
            }
            if (cheat_type == 2)
            {
                puts("decr");
                // decrement
                struct rr_component_arena *arena =
                    rr_simulation_get_arena(&this->simulation, 1);
                rr_component_arena_set_wave_tick(arena, 0);
                rr_component_arena_set_wave(arena, arena->wave - 1);
                rr_simulation_for_each_mob(&this->simulation, &this->simulation,
                                           delete_entity_function);
                rr_simulation_for_each_drop(&this->simulation,
                                            &this->simulation,
                                            delete_entity_function);
                rr_simulation_for_each_petal(&this->simulation,
                                             &this->simulation,
                                             delete_entity_function);
            }
            if (cheat_type == 3)
            {
            }
            break;
#endif
        }
        case 69:
        {
            client->ready ^= 1;
            break;
        }
        case 70:
        {
            uint64_t local_size = size - 1;
            if (local_size % 3 != 1)
                return 0;
            uint8_t pos = proto_bug_read_uint8(&encoder, "pos");
            while (pos)
            {
                if (pos > 20)
                    return 0;
                client->loadout[pos - 1].id =
                    proto_bug_read_uint8(&encoder, "id");
                client->loadout[pos - 1].rarity =
                    proto_bug_read_uint8(&encoder, "rar");
                pos = proto_bug_read_uint8(&encoder, "pos");
            }
            break;
        }
        }
    }
    default:
        break;
    }
    return 0;
}

void rr_server_init(struct rr_server *this)
{
    printf("server size: %lu\n", sizeof *this);
    memset(this, 0, sizeof *this);
    rr_static_data_init();
    rr_simulation_init(&this->simulation);
}

void rr_server_free(struct rr_server *this)
{
    lws_context_destroy(this->server);
}

static void rr_simulation_tick_entity_resetter_function(EntityIdx entity,
                                                        void *captures)
{
    struct rr_simulation *this = captures;
#define XX(COMPONENT, ID)                                                      \
    if (rr_simulation_has_##COMPONENT(this, entity))                           \
        rr_simulation_get_##COMPONENT(this, entity)->protocol_state = 0;
    RR_FOR_EACH_COMPONENT
#undef XX
    if (rr_simulation_has_physical(this, entity))
        rr_simulation_get_physical(this, entity)->ticked_animation = 0;
    if (rr_simulation_has_drop(this, entity))
        memset(
            &rr_simulation_get_drop(this, entity)->picked_up_this_tick, 0,
            sizeof rr_simulation_get_drop(this, entity)->picked_up_this_tick);
}

void rr_server_tick(struct rr_server *this)
{
    if (this->simulation_active)
        rr_simulation_tick(&this->simulation);

    uint8_t client_count = 0;
    for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
        if (rr_bitset_get(this->clients_in_use, i))
        {
            rr_server_client_tick(this->clients + i);
            ++client_count;
        }

    if (this->simulation_active)
    {
        if (!client_count)
        {
            this->simulation_active = 0;
#ifdef RIVET_BUILD
            exit(123123);
#endif
            free(this->simulation.grid);
            rr_simulation_init(&this->simulation);
        }
        else
            rr_simulation_for_each_entity(
                &this->simulation, &this->simulation,
                rr_simulation_tick_entity_resetter_function);
    }
    else
    {
        uint8_t all_ready = 1;
        for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
            if (rr_bitset_get(this->clients_in_use, i))
                all_ready &= this->clients[i].ready;

        if (client_count && all_ready)
        {
            if (--this->ticks_until_simulation_create == 0)
            {
                this->simulation_active = 1;
                rr_simulation_init(&this->simulation);
#ifdef RIVET_BUILD
                // players cannot join in the middle of a game (simulation)
                char *lobby_token = getenv("RIVET_LOBBY_TOKEN");
                rr_rivet_lobbies_set_closed(lobby_token, 1);
#endif
                for (uint64_t i = 0; i < RR_MAX_CLIENT_COUNT; i++)
                    if (rr_bitset_get(this->clients_in_use, i))
                    {
                        rr_server_client_create_player_info(this->clients + i);
                        rr_server_client_create_flower(this->clients + i);
                    }
            }
        }
        else
            this->ticks_until_simulation_create =
#ifdef RIVET_BUILD
                125
#else
                2
#endif
                ;
    }
}

void rr_server_run(struct rr_server *this)
{
    struct lws_context_creation_info info;
    memset(&info, 0, sizeof(info));

    struct lws_protocols protocols[2] = {
        {"g", rr_server_lws_callback_function, 0, 0}, {NULL, NULL, 0, 0}};
    info.port = 1234;
    info.protocols = &protocols[0];
    info.gid = -1;
    info.uid = -1;
    info.user = this;
    info.pt_serv_buf_size = MESSAGE_BUFFER_SIZE;

    this->server = lws_create_context(&info);
    assert(this->server);
    this->ticks_until_simulation_create =
#ifdef RIVET_BUILD
        125
#else
        24
#endif
        ;
    while (1)
    {
        struct timeval start;
        struct timeval end;

        gettimeofday(
            &start,
            NULL); // gettimeofday actually starts from unix timestamp 0 (goofy)
        lws_service(this->server, -1);
        rr_server_tick(this);
        gettimeofday(&end, NULL);

        uint64_t elapsed_time = (end.tv_sec - start.tv_sec) * 1000000 +
                                (end.tv_usec - start.tv_usec);
        if (elapsed_time > 1000)
            fprintf(stderr, "tick took %lu microseconds\n", elapsed_time);
        int64_t to_sleep = 40000 - elapsed_time;
        if (to_sleep > 0)
            usleep(to_sleep);
    }
}
