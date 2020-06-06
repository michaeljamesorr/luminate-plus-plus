#ifndef LUMINATE_FILTER_H
#define LUMINATE_FILTER_H

#include <texture.h>

namespace luminate{

    /**
     * A square matrix of floats to be used as an image processing kernel. 
     */
    typedef struct{
        float* weights;
        int radius;
    } FilterKernel;

    /**
     * A 3x3 gaussian blur.
     */
    static const FilterKernel GAUSS_BLUR_3 = {new float[9]{1.0f/16.0f, 2.0f/16.0f, 1.0f/16.0f,
                                                           2.0f/16.0f, 4.0f/16.0f, 2.0f/16.0f,
                                                           1.0f/16.0f, 2.0f/16.0f, 1.0f/16.0f}, 1};
    /**
     * 
     */
    static const FilterKernel SIMPLE_EDGE_DETECT = {new float[9]{-1, -1, -1,
                                                                 -1,  8, -1,
                                                                 -1, -1, -1}, 1};
    static const FilterKernel SOBEL_EDGE_X1 = {new float[9]{ 1,  0, -1,
                                                             2,  0, -2,
                                                             1,  0, -1}, 1};
    static const FilterKernel SOBEL_EDGE_X2 = {new float[9]{-1,  0,  1,
                                                            -2,  0,  2,
                                                            -1,  0,  1}, 1};                                                            
    static const FilterKernel SOBEL_EDGE_Y1 = {new float[9]{ 1,  2,  1,
                                                             0,  0,  0,
                                                            -1, -2, -1}, 1};
    static const FilterKernel SOBEL_EDGE_Y2 = {new float[9]{-1, -2, -1,
                                                             0,  0,  0,
                                                             1,  2,  1}, 1};
    


    static const FilterKernel FLOW_3 = {new float[9]{1.0f/6.0f, 2.0f/6.0f, 1.0f/6.0f,
                                                     2.0f/6.0f, 4.0f/6.0f, 2.0f/6.0f,
                                                     1.0f/6.0f, 2.0f/6.0f, 1.0f/6.0f}, 1};

    TexData apply_filter(TexData texture, FilterKernel kernel, float* strength_mask, float cutoff);
    TexData apply_filter(TexData texture, FilterKernel kernel);

    TexData nearest_neighbour_scale(TexData texture, int width, int height);

    TexData sobel_edge_detect(TexData texture);

    TexData convert_grayscale(TexData texture);

    TexData onebit_posterize(TexData texture, float threshold);

    TexData binary_hit_and_miss(TexData binary_texture, FilterKernel struct_elem);

    TexData binary_erosion(TexData binary_texture);

    TexData binary_dilation(TexData binary_texture);

    TexData binary_thinning(TexData binary_texture);

    TexData invert(TexData texture);

    float pixel_luminance(float* rgb_pixel);
}

#endif