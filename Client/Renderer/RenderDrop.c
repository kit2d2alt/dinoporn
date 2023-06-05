#include <Client/Renderer/ComponentRender.h>

#include <math.h>

#include <Client/Simulation.h>
#include <Client/Renderer/Renderer.h>
#include <Client/Renderer/RenderFunctions.h>

void rr_component_drop_render(EntityIdx entity, struct rr_simulation *simulation, struct rr_renderer *renderer)
{
    struct rr_component_physical *physical = rr_simulation_get_physical(simulation, entity);
    struct rr_component_drop *drop = rr_simulation_get_drop(simulation, entity);
    rr_renderer_translate(renderer, physical->lerp_x, physical->lerp_y);
    rr_renderer_rotate(renderer, physical->lerp_angle + physical->lerp_radius * 0.25);
    rr_renderer_scale(renderer, physical->lerp_radius * 0.04);
    rr_renderer_scale(renderer, 1 + sinf(physical->animation * 3) * 0.1);
    if (physical->lerp_damage_animation_tick > 0)
        rr_renderer_scale(renderer, 1 - (5 - physical->lerp_damage_animation_tick) * 0.2);
    rr_renderer_set_fill(renderer, RR_RARITY_COLORS[drop->rarity]);
    renderer->state.filter.amount = 0.2;
    rr_renderer_set_stroke(renderer, RR_RARITY_COLORS[drop->rarity]);
    rr_renderer_set_line_width(renderer, 5);
    rr_renderer_set_line_cap(renderer, 1);
    rr_renderer_set_line_join(renderer, 1);
    rr_renderer_begin_path(renderer);
    rr_renderer_fill_rect(renderer, -25, -25, 50, 50);
    rr_renderer_stroke_rect(renderer, -25, -25, 50, 50);
    renderer->state.filter.amount = 0;
    rr_renderer_render_static_petal(renderer, drop->id, drop->rarity);
}