#pragma once

#include <Shared/Component/Common.h>
#include <Shared/Bitset.h>
#include <Shared/Entity.h>
#include <Shared/StaticData.h>
#include <Shared/Vector.h>
#include <Shared/Utilities.h>

struct rr_simulation;
struct proto_bug;
RR_CLIENT_ONLY(struct rr_renderer;)

struct rr_component_player_info_petal
{
    EntityIdx simulation_id;
    int32_t cooldown_ticks;
};

struct rr_component_player_info_petal_slot
{
    uint8_t rarity;
    uint32_t count;
    struct rr_petal_data const *data;
    struct rr_component_player_info_petal petals[10];
};
// check if there's rr_component_player_info_set function before setting a field
struct rr_component_player_info
{
                   EntityIdx parent_id;
                   EntityIdx flower_id; // will be 0 if nonexistant
                   uint8_t input;
                   float global_rotation;
                   float camera_x;
    RR_CLIENT_ONLY(float lerp_camera_x;)
                   float camera_y;
    RR_CLIENT_ONLY(float lerp_camera_y;)
                   float camera_fov;
    RR_CLIENT_ONLY(float lerp_camera_fov;)
                   uint64_t protocol_state;
                   uint32_t slot_count;
                   uint32_t rotation_count;
    RR_SERVER_ONLY(uint8_t entities_in_view[RR_BITSET_ROUND(RR_MAX_ENTITY_COUNT)];)
                   struct rr_component_player_info_petal_slot slots[10];
    
};

void rr_component_player_info_init(struct rr_component_player_info *, struct rr_simulation *);
void rr_component_player_info_free(struct rr_component_player_info *, struct rr_simulation *);

RR_SERVER_ONLY(void rr_component_player_info_write(struct rr_component_player_info *, struct proto_bug *, int);)
RR_CLIENT_ONLY(void rr_component_player_info_read(struct rr_component_player_info *, struct proto_bug *);)

RR_DECLARE_PUBLIC_FIELD(player_info, float, camera_x);
RR_DECLARE_PUBLIC_FIELD(player_info, float, camera_y);
RR_DECLARE_PUBLIC_FIELD(player_info, float, camera_fov);
RR_DECLARE_PUBLIC_FIELD(player_info, EntityIdx, flower_id);