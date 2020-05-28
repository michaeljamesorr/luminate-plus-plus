#include <draw.h>
#include <cassert>

using namespace luminate;

void luminate::setRGBPixel(TexData texture, int x, int y, glm::vec3 colour){
    assert(texture.getDepth()==3);

    int width = texture.getWidth();
    int height = texture.getHeight();
    int depth = 3;

    float* data = texture.getData().get();

    int pixel_idx = y*width*depth + x*depth;

    data[pixel_idx] = colour.x;
    data[pixel_idx+1] = colour.y;
    data[pixel_idx+2] = colour.z;
}