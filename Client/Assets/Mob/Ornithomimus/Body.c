#include <Client/Assets/Render.h>

#include <Client/Renderer/Renderer.h>

void rr_ornithomimus_body_draw(struct rr_renderer *renderer)
{
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -55.415188, 43.688320000000004);
    rr_renderer_bezier_curve_to(renderer, -55.415188, -11.420962999999993,
                                -30.607392, -56.09585, -0.005425000000002456,
                                -56.09585);
    rr_renderer_bezier_curve_to(renderer, 14.690154999999997, -56.09585,
                                28.783851, -45.582910999999996,
                                39.175200999999994, -26.869753);
    rr_renderer_bezier_curve_to(renderer, 49.566542999999996, -8.156588,
                                55.40434199999999, 17.223907, 55.40434199999999,
                                43.688322);
    rr_renderer_bezier_curve_to(renderer, 55.40434199999999, 98.797605,
                                30.596541999999992, 143.47250200000002,
                                -0.005425000000009561, 143.47250200000002);
    rr_renderer_bezier_curve_to(
        renderer, -30.607392000000008, 143.47250200000002, -55.41518800000001,
        98.79760600000003, -55.41518800000001, 43.688322000000014);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -62.88302, 43.69783000000001);
    rr_renderer_bezier_curve_to(renderer, -62.88302, -18.844024999999988,
                                -34.729398, -69.54422999999998,
                                -0.00014600000000086766, -69.54422999999998);
    rr_renderer_bezier_curve_to(renderer, 16.677428, -69.54422999999998,
                                32.671934, -57.61340599999998, 44.464751,
                                -36.37640599999998);
    rr_renderer_bezier_curve_to(renderer, 56.257582, -15.139390999999982,
                                62.88272, 13.66416700000002, 62.88272,
                                43.69782800000002);
    rr_renderer_bezier_curve_to(renderer, 62.88272, 106.23968300000001,
                                34.72911, 156.93987800000002,
                                -0.00014600000000086766, 156.93987800000002);
    rr_renderer_bezier_curve_to(renderer, -34.729396, 156.93987800000002,
                                -62.88302, 106.23968300000001, -62.88302,
                                43.697828000000015);
    rr_renderer_move_to(renderer, -48.609865, 43.697828000000015);
    rr_renderer_bezier_curve_to(renderer, -48.609865, 98.35683800000001,
                                -26.846552, 142.666718, -0.000144999999996287,
                                142.666718);
    rr_renderer_bezier_curve_to(renderer, 26.846260000000004, 142.666718,
                                48.60957500000001, 98.356843, 48.60957500000001,
                                43.697828);
    rr_renderer_bezier_curve_to(renderer, 48.60957500000001, -10.961182,
                                26.846262000000007, -55.271072000000004,
                                -0.000144999999996287, -55.271072000000004);
    rr_renderer_bezier_curve_to(renderer, -26.846549999999997,
                                -55.271072000000004, -48.609865, -10.961182,
                                -48.609865, 43.697828);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffa7a7a7);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -38.547134, -118.336502);
    rr_renderer_bezier_curve_to(renderer, -38.547134, -139.657095, -21.263382,
                                -156.940852, 0.057212999999997294, -156.940852);
    rr_renderer_bezier_curve_to(renderer, 10.295722999999997, -156.940852,
                                20.114890999999997, -152.87361900000002,
                                27.354613999999998, -145.6339);
    rr_renderer_bezier_curve_to(renderer, 34.594329599999995, -138.3941806,
                                38.661559999999994, -128.575013,
                                38.661559999999994, -118.33650200000001);
    rr_renderer_line_to(renderer, 38.661559999999994, -25.184967000000015);
    rr_renderer_bezier_curve_to(
        renderer, 38.661559999999994, -3.8643650000000136, 21.377807999999995,
        13.419387999999984, 0.057212999999997294, 13.419387999999984);
    rr_renderer_bezier_curve_to(
        renderer, -21.263382000000004, 13.419387999999984, -38.547134,
        -3.864364000000016, -38.547134, -25.184967000000015);
    rr_renderer_fill(renderer);
    rr_renderer_set_fill(renderer, 0xffb8b8b8);
    rr_renderer_begin_path(renderer);
    rr_renderer_move_to(renderer, -27.687065000000004, -116.27569);
    rr_renderer_bezier_curve_to(renderer, -27.687065000000004, -131.598513,
                                -15.265457000000003, -144.020119,
                                0.057364999999997224, -144.020119);
    rr_renderer_bezier_curve_to(renderer, 7.4156489999999975, -144.020119,
                                14.472548999999997, -141.097052, 19.675644,
                                -135.89396499999998);
    rr_renderer_bezier_curve_to(renderer, 24.878731, -130.6908743,
                                27.801795999999996, -123.63397049999998,
                                27.801795999999996, -116.27568999999998);
    rr_renderer_line_to(renderer, 27.801795999999996, -1.4043139999999852);
    rr_renderer_bezier_curve_to(
        renderer, 27.801795999999996, 13.918516000000015, 15.380187999999995,
        26.340116000000016, 0.0573659999999947, 26.340116000000016);
    rr_renderer_bezier_curve_to(
        renderer, -15.265457000000005, 26.340116000000016, -27.687064000000007,
        13.918516000000016, -27.687064000000007, -1.4043139999999852);
    rr_renderer_fill(renderer);
}