#ifndef LUMINATE_DRAW_H
#define LUMINATE_DRAW_H

#include <texture.h>
#include <glm/vec3.hpp>

namespace luminate{

    /**
     * Modify a texture by setting one pixel to a given colour.
     */
    void setRGBPixel(TexData texture, int x, int y, glm::vec3 colour);

    /**
     * Modify a texture by drawing a line of a given colour between two points.
     */
    void drawRGBLine(TexData texture, int x0, int y0, int x1, int y1, glm::vec3 colour);
}

#endif