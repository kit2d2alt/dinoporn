#include <Client/Assets/Render.h>

#include <Client/Renderer/Renderer.h>

void rr_t_rex_body_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xff9a7c55);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -61.56788, 26.706199999999995);
    rr_renderer_bezier_curve_to(renderer, -61.56788, -25.759330000000006,
                                -34.00524300000001, -68.29104000000001,
                                -0.00500600000000162, -68.29104000000001);
    rr_renderer_bezier_curve_to(
        renderer, 16.322485999999998, -68.29104000000001, 31.981237999999998,
        -58.28243400000001, 43.526519, -40.46699000000001);
    rr_renderer_bezier_curve_to(renderer, 55.071792, -22.65156000000001,
                                61.557861, 1.5113729999999919, 61.557861,
                                26.706199999999995);
    rr_renderer_bezier_curve_to(renderer, 61.557861, 79.17173,
                                33.99522400000001, 121.70344999999999,
                                -0.00500499999999704, 121.70344999999999);
    rr_renderer_bezier_curve_to(
        renderer, -34.005241999999996, 121.70344999999999, -61.567879,
        79.17172699999999, -61.567879, 26.706199999999995);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -69.864994, 26.71526);
    rr_renderer_bezier_curve_to(renderer, -69.864994, -32.82629,
                                -38.584987999999996, -81.09425,
                                0.0008660000000020318, -81.09425);
    rr_renderer_bezier_curve_to(renderer, 18.530438000000004, -81.09425,
                                36.30109, -69.735775, 49.403476000000005,
                                -49.517575);
    rr_renderer_bezier_curve_to(renderer, 62.50586200000001, -29.299375,
                                69.866718, -1.8775910000000025, 69.866718,
                                26.715258999999996);
    rr_renderer_bezier_curve_to(renderer, 69.866718, 86.256809,
                                38.586704000000005, 134.52478399999998,
                                0.0008680000000111932, 134.52478399999998);
    rr_renderer_bezier_curve_to(
        renderer, -38.58498199999999, 134.52478399999998, -69.86499199999999,
        86.25680899999998, -69.86499199999999, 26.71525899999999);
    rr_renderer_move_to(renderer, -54.006841499999986, 26.71525899999999);
    rr_renderer_bezier_curve_to(
        renderer, -54.006841499999986, 77.49859899999998, -29.826772499999986,
        118.66662899999999, 0.0008645000000129244, 118.66662899999999);
    rr_renderer_bezier_curve_to(
        renderer, 29.828494500000012, 118.66662899999999, 54.00856250000001,
        77.49859899999998, 54.00856250000001, 26.71525899999999);
    rr_renderer_bezier_curve_to(renderer, 54.00856250000001, -24.06806600000001,
                                29.82849350000001, -65.23609600000002,
                                0.0008645000000129244, -65.23609600000002);
    rr_renderer_bezier_curve_to(
        renderer, -29.826772499999986, -65.23609600000002, -54.006841499999986,
        -24.068066000000016, -54.006841499999986, 26.71525899999999);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -49.863182, -84.69298);
    rr_renderer_bezier_curve_to(renderer, -49.863182, -112.21361,
                                -27.553299000000003, -134.523493,
                                -0.032668999999998505, -134.523493);
    rr_renderer_bezier_curve_to(renderer, 13.183205000000001, -134.523493,
                                25.857796, -129.2735044, 35.202835,
                                -119.928473);
    rr_renderer_bezier_curve_to(renderer, 44.547867, -110.583437, 49.7978515,
                                -97.90885399999999, 49.7978515, -84.69298);
    rr_renderer_line_to(renderer, 49.7978515, -52.46538);
    rr_renderer_bezier_curve_to(renderer, 49.7978515, -24.944750000000003,
                                27.4879685, -2.634875000000001,
                                -0.03266849999999977, -2.634875000000001);
    rr_renderer_bezier_curve_to(renderer, -27.5532985, -2.634875000000001,
                                -49.8631815, -24.944750000000003, -49.8631815,
                                -52.46538);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff9a7c55);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -35.84611, -83.83829);
    rr_renderer_bezier_curve_to(renderer, -35.84611, -103.617,
                                -19.812300000000004, -119.65081,
                                -0.033590000000003783, -119.65081);
    rr_renderer_bezier_curve_to(renderer, 9.464486999999997, -119.65081,
                                18.573541999999996, -115.8777158,
                                25.289689999999997, -109.161567);
    rr_renderer_bezier_curve_to(renderer, 32.005846, -102.44541500000001,
                                35.778932999999995, -93.33636,
                                35.778932999999995, -83.83829);
    rr_renderer_line_to(renderer, 35.778932999999995, -23.574710000000003);
    rr_renderer_bezier_curve_to(
        renderer, 35.778932999999995, -3.795993000000003, 19.745126999999997,
        12.237804999999994, -0.033590000000003783, 12.237804999999994);
    rr_renderer_bezier_curve_to(
        renderer, -19.812300000000004, 12.237804999999994, -35.84611,
        -3.7959930000000064, -35.84611, -23.574710000000003);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -6.6456699999999955, -60.64478);
    rr_renderer_bezier_curve_to(renderer, -6.6456699999999955, -64.3063782,
                                -3.6773548999999957, -67.274701,
                                -0.015748999999995128, -67.274701);
    rr_renderer_bezier_curve_to(renderer, 1.742612800000005, -67.274701,
                                3.428960800000005, -66.57619179999999,
                                4.672315600000005, -65.332837);
    rr_renderer_bezier_curve_to(renderer, 5.915662800000005, -64.0894898,
                                6.614172000000004, -62.403141899999994,
                                6.614172000000004, -60.64478);
    rr_renderer_line_to(renderer, 6.614172000000004, -6.314069999999994);
    rr_renderer_bezier_curve_to(renderer, 6.614172000000004, -2.652464199999994,
                                3.6458569000000045, 0.31585860000000654,
                                -0.015748999999996016, 0.31585860000000654);
    rr_renderer_bezier_curve_to(
        renderer, -3.677354799999996, 0.31585860000000654, -6.645669999999996,
        -2.6524641999999936, -6.645669999999996, -6.314069999999994);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xff826948);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -6.6456699999999955, -7.964570000000009);
    rr_renderer_bezier_curve_to(
        renderer, -6.6456699999999955, -11.62617580000001, -3.6773548999999957,
        -14.594498600000009, -0.015748999999995128, -14.594498600000009);
    rr_renderer_bezier_curve_to(
        renderer, 1.742612800000005, -14.594498600000009, 3.428960800000005,
        -13.895981750000008, 4.672315600000005, -12.652634600000008);
    rr_renderer_bezier_curve_to(
        renderer, 5.915662800000005, -11.409287400000007, 6.614172000000004,
        -9.722931800000008, 6.614172000000004, -7.964570000000008);
    rr_renderer_line_to(renderer, 6.614172000000004, 97.01181);
    rr_renderer_bezier_curve_to(renderer, 6.614172000000004, 100.6734006,
                                3.6458569000000045, 103.6417233,
                                -0.015748999999996016, 103.6417233);
    rr_renderer_bezier_curve_to(renderer, -3.677354799999996, 103.6417233,
                                -6.645669999999996, 100.6734005,
                                -6.645669999999996, 97.01181);
    rr_renderer_fill(renderer);
}