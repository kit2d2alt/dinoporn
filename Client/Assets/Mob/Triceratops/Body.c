#include <Client/Assets/Render.h>

#include <Client/Renderer/Renderer.h>

void rr_triceratops_body_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffa49b8a);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -77.37249800000001, -0.011020000000002028);
    rr_renderer_bezier_curve_to(renderer, -77.37249800000001,
                                -65.94679000000001, -42.735468000000004,
                                -119.3983, -0.008522000000013463, -119.3983);
    rr_renderer_bezier_curve_to(renderer, 20.509681999999987, -119.3983,
                                40.18751499999998, -106.82003,
                                54.696074999999986, -84.430576);
    rr_renderer_bezier_curve_to(renderer, 69.20463499999998, -62.041111,
                                77.35545299999998, -31.674486,
                                77.35545299999998, -0.011020000000002028);
    rr_renderer_bezier_curve_to(renderer, 77.35545299999998, 65.924756,
                                42.718428999999986, 119.37628,
                                -0.008523000000010938, 119.37628);
    rr_renderer_bezier_curve_to(renderer, -42.735467000000014, 119.37628,
                                -77.372499, 65.924757, -77.372499,
                                -0.011020000000002028);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -87.799199, 0.0003700000000037562);
    rr_renderer_bezier_curve_to(renderer, -87.799199, -74.82816, -48.490674,
                                -135.48866999999998, -0.0011489999999980682,
                                -135.48866999999998);
    rr_renderer_bezier_curve_to(
        renderer, 23.284343000000003, -135.48866999999998, 45.616121,
        -121.21397399999998, 62.081441000000005, -95.80485499999998);
    rr_renderer_bezier_curve_to(renderer, 78.546773, -70.39572899999997,
                                87.796895, -35.93356299999998, 87.796895,
                                0.00036500000003059085);
    rr_renderer_bezier_curve_to(renderer, 87.796895, 74.82888500000003,
                                48.488378000000004, 135.48937500000005,
                                -0.0011449999999939564, 135.48937500000005);
    rr_renderer_bezier_curve_to(
        renderer, -48.49066499999999, 135.48937500000005, -87.799195,
        74.82888300000005, -87.799195, 0.0003650000000448017);
    rr_renderer_move_to(renderer, -67.87079299999999, 0.0003650000000448017);
    rr_renderer_bezier_curve_to(
        renderer, -67.87079299999999, 63.822737000000046, -37.48451899999999,
        115.56100500000005, -0.0011489999999980682, 115.56100500000005);
    rr_renderer_bezier_curve_to(renderer, 37.482227, 115.56100500000005,
                                67.868501, 63.82273900000005, 67.868501,
                                0.0003650000000448017);
    rr_renderer_bezier_curve_to(renderer, 67.868501, -63.82201499999996,
                                37.482225, -115.56027499999996,
                                -0.0011489999999980682, -115.56027499999996);
    rr_renderer_bezier_curve_to(renderer, -37.484519, -115.56027499999996,
                                -67.87079299999999, -63.822014999999965,
                                -67.87079299999999, 0.0003650000000448017);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff898276);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -8.944885, -50.678929999999994);
    rr_renderer_bezier_curve_to(renderer, -8.944885, -55.61905449999999,
                                -4.940124299999999, -59.62381499999999, 0,
                                -59.62381499999999);
    rr_renderer_bezier_curve_to(renderer, 2.3723297, -59.62381499999999,
                                4.647499, -58.68140929999999, 6.3249893,
                                -57.003918999999996);
    rr_renderer_bezier_curve_to(renderer, 8.0024795, -55.326428799999995,
                                8.9448853, -53.0512594, 8.9448853, -50.6789297);
    rr_renderer_line_to(renderer, 8.9448853, 90.80139030000001);
    rr_renderer_bezier_curve_to(renderer, 8.9448853, 95.7415148,
                                4.940124599999999, 99.74627530000001,
                                2.9999999995311555e-7, 99.74627530000001);
    rr_renderer_bezier_curve_to(renderer, -4.9401242, 99.74627530000001,
                                -8.9448847, 95.7415146, -8.9448847,
                                90.80139030000001);
    rr_renderer_fill(renderer);
}