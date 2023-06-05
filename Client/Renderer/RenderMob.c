#include <Client/Renderer/ComponentRender.h>

#include <math.h>

#include <Client/Simulation.h>
#include <Client/Renderer/Renderer.h>
#include <Shared/StaticData.h>

#include <Client/Renderer/RenderFunctions.h>

void rr_component_mob_render(EntityIdx entity, struct rr_simulation *simulation, struct rr_renderer *renderer)
{
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, entity);
    struct rr_component_mob *mob = rr_simulation_get_mob(simulation, entity);
    renderer->state.filter.color = 0xffff0000;
    renderer->state.filter.amount = physical->lerp_damage_animation_tick * 0.08;

    rr_renderer_translate(renderer, physical->lerp_x, physical->lerp_y);
    rr_renderer_rotate(renderer, physical->lerp_angle);
    rr_renderer_scale(renderer, RR_MOB_RARITY_SCALING[mob->rarity].radius);
    if (rr_simulation_get_health(simulation, entity)->health == 0)
    {
        rr_renderer_set_global_alpha(renderer, (physical->lerp_damage_animation_tick) * 0.2);
        rr_renderer_scale(renderer, 1 + (6 - physical->lerp_damage_animation_tick) * 0.15);
    }
    if (physical->animation > 2 * M_PI)
        physical->animation = fmod(physical->animation, 2 * M_PI);
    rr_renderer_render_mob(renderer, mob->id, sin(physical->animation));
}