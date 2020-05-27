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

    float* apply_filter(TexData texture, FilterKernel kernel);

}

#endif