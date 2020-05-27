#ifndef LUMINATE_FILTER_H
#define LUMINATE_FILTER_H

#include "utility.h"

namespace luminate{

    typedef struct{
        float* weights;
        int radius;
    } FilterKernel;

    static const FilterKernel GAUSS_BLUR_3 = {new float[9]{1.0f/16.0f, 2.0f/16.0f, 1.0f/16.0f,
                                                           2.0f/16.0f, 4.0f/16.0f, 2.0f/16.0f,
                                                           1.0f/16.0f, 2.0f/16.0f, 1.0f/16.0f}, 1};
    static const FilterKernel SIMPLE_EDGE_DETECT = {new float[9]{-1, -1, -1,
                                                                 -1,  8, -1,
                                                                 -1, -1, -1}, 1};
    static const FilterKernel FLOW_3 = {new float[9]{1.0f/6.0f, 2.0f/6.0f, 1.0f/6.0f,
                                                     2.0f/6.0f, 4.0f/6.0f, 2.0f/6.0f,
                                                     1.0f/6.0f, 2.0f/6.0f, 1.0f/6.0f}, 1};

    TexData apply_filter(TexData texture, FilterKernel kernel, float* strength_mask, float cutoff);
    TexData apply_filter(TexData texture, FilterKernel kernel);

    TexData nearest_neighbour_scale(TexData texture, int width, int height);

    TexData sobel_edge_detect(TexData texture);

    TexData convert_grayscale(TexData texture);

    TexData onebit_posterize(TexData texture, float threshold);

}

#endif