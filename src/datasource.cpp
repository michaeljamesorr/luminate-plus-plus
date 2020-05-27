#include "datasource.h"

using namespace luminate;

TextureDataSource::TextureDataSource(TexData texture, FilterKernel filter){
    this->tex_data = texture;
    this->filter = filter;
};