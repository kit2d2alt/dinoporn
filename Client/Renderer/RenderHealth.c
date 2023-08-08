#include <Client/Renderer/ComponentRender.h>

#include <Client/Game.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Simulation.h>
#include <Shared/StaticData.h>

void rr_component_health_render(EntityIdx entity, struct rr_game *game)
{
    struct rr_simulation *simulation = game->simulation;
    struct rr_renderer *renderer = game->renderer;
    struct rr_component_physical *physical =
        rr_simulation_get_physical(simulation, entity);
    struct rr_component_health *health =
        rr_simulation_get_health(simulation, entity);
    if (health->hidden || rr_simulation_has_petal(simulation, entity))
        return;
    if (rr_simulation_has_flower(simulation, entity))
    {
        struct rr_component_relations *relations =
            rr_simulation_get_relations(simulation, entity);

        if (relations->owner == game->player_info->parent_id)
            if (health->lerp_health / health->max_health > 0.99)
                return;
    }

    if (health->health == 0)
    {
        rr_renderer_set_global_alpha(
            renderer, (physical->lerp_server_animation_tick) * 0.2);
        rr_renderer_scale(
            renderer, 1 + (6 - physical->lerp_server_animation_tick) * 0.15);
    }
    float length = 40;

    if (rr_simulation_has_mob(simulation, entity))
    {
        struct rr_component_mob *mob =
            rr_simulation_get_mob(simulation, entity);
        length += mob->rarity * 5;
        // mob rarity
        rr_renderer_draw_translated_image(
            renderer, &game->rarity_name_cache[mob->rarity],
            length - game->rarity_name_cache[mob->rarity].width / 2 + 2,
            14 - 2);

        // mob name
        rr_renderer_draw_translated_image(
            renderer, &game->mob_name_cache[mob->id],
            -length + game->mob_name_cache[mob->id].width / 2 - 2, -12 - 2);
    }
    else if (rr_simulation_has_flower(simulation, entity))
    {
        struct rr_component_player_info *player_info =
            rr_simulation_get_player_info(
                simulation,
                rr_simulation_get_relations(simulation, entity)->owner);
        rr_renderer_set_fill(renderer, 0xffffffff);
        rr_renderer_set_stroke(renderer, 0xff000000);
        rr_renderer_set_text_size(renderer, 12);
        rr_renderer_set_text_align(renderer, 0);
        rr_renderer_set_text_baseline(renderer, 0);
        rr_renderer_stroke_text(
            renderer, &game->squad_members[player_info->client_id].name[0],
            -length, -18);
        rr_renderer_fill_text(
            renderer, &game->squad_members[player_info->client_id].name[0],
            -length, -18);
    }
    // the health bar
    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_set_stroke(renderer, 0xff222222);
    rr_renderer_set_line_width(renderer, 10);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -length, 0);
    rr_renderer_line_to(renderer, length, 0);
    rr_renderer_stroke(renderer);

    rr_renderer_set_stroke(renderer, 0xff75dd34);
    rr_renderer_set_line_width(renderer, 7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -length, 0);
    rr_renderer_line_to(
        renderer,
        -length + 2 * length * health->lerp_health / health->max_health, 0);
    rr_renderer_stroke(renderer);
}
