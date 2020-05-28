#include <datasource.h>
#include <filter.h>

#include <iostream>

using namespace luminate;

TextureDataSource::TextureDataSource(TexData texture, FilterKernel filter, float* strength_mask, float cutoff)
                 :DataSource(texture){
    this->filter = filter;
    this->strength_mask = strength_mask;
    this->cutoff = cutoff;
}

TextureDataSource::TextureDataSource(TexData texture, FilterKernel filter)
                                    :TextureDataSource(texture, filter, NULL, 1.0f){};

bool TextureDataSource::fetch(){
    TexData filtered = apply_filter(this->data, this->filter, this->strength_mask, this->cutoff);
    this->data = filtered;
    return true;
};