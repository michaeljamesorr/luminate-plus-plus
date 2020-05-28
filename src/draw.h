#ifndef LUMINATE_DRAW_H
#define LUMINATE_DRAW_H

#include <texture.h>
#include <glm/vec3.hpp>

namespace luminate{
    void setRGBPixel(TexData texture, int x, int y, glm::vec3 colour);

    void drawRGBLine(TexData texture, int x0, int y0, int x1, int y1, glm::vec3 colour);
}

#endif