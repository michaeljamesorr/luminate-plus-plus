#include <draw.h>
#include <cassert>
#include <math.h>

using namespace luminate;

void luminate::setRGBPixel(TexData texture, int x, int y, glm::vec3 colour){
    // make sure the texture has three channels to work on
    assert(texture.getDepth()==3);

    int width = texture.getWidth();
    int height = texture.getHeight();
    int depth = 3;

    // find pixel position in data array
    float* data = texture.getData().get();

    int pixel_idx = y*width*depth + x*depth;

    // set pixel elements equal to colour elements
    data[pixel_idx] = colour.x;
    data[pixel_idx+1] = colour.y;
    data[pixel_idx+2] = colour.z;
}

/* Used to draw a line which is longer in the x axis i.e. <= 45 degree gradient */
void plot_line_low(TexData texture, int x0, int y0, int x1, int y1, glm::vec3 colour){
    // Bresenham line algorithm https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
    int width = texture.getWidth();
    int height = texture.getHeight();
    int depth = 3;
    float* data = texture.getData().get();
    
    int dx = x1 - x0;
    int dy = y1 - y0;

    int yi = 1;
    if(dy < 0){
        yi = -1;
        dy = -dy;
    }
    int D = 2*dy - dx;
    int y = y0;

    for(int x = x0; x < x1+1; x++){
        int pixel_idx = y*width*depth + x*depth;
        data[pixel_idx] = colour.x;
        data[pixel_idx+1] = colour.y;
        data[pixel_idx+2] = colour.z;
        if(D > 0){
            y = y + yi;
            D = D - 2*dx;
        }
        D = D + 2*dy;
    }
}

/* Used to draw a line which is longer in the y axis i.e. >= 45 degree gradient */
void plot_line_high(TexData texture, int x0, int y0, int x1, int y1, glm::vec3 colour){
    // Bresenham line algorithm https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
    int width = texture.getWidth();
    int height = texture.getHeight();
    int depth = 3;
    float* data = texture.getData().get();
    
    int dx = x1 - x0;
    int dy = y1 - y0;

    int xi = 1;
    if(dx < 0){
        xi = -1;
        dx = -dx;
    }
    int D = 2*dx - dx;
    int x = x0;

    for(int y = y0; y < y1+1; y++){
        int pixel_idx = y*width*depth + x*depth;
        data[pixel_idx] = colour.x;
        data[pixel_idx+1] = colour.y;
        data[pixel_idx+2] = colour.z;
        if(D > 0){
            x = x + xi;
            D = D - 2*dy;
        }
        D = D + 2*dx;
    }
}

void luminate::drawRGBLine(TexData texture, int x0, int y0, int x1, int y1, glm::vec3 colour){
    assert(texture.getDepth()==3);

    int width = texture.getWidth();
    int height = texture.getHeight();
    int depth = 3;

    // check input values make sense
    assert(x0 >= 0 && y0 >= 0 && x1 >= 0 && y1 >= 0);
    assert(x0 < width and y0 < height and x1 < width and y1 < height);

    // determine if gradient of line is low or high (abs value)
    if(abs(y1-y0) < abs(x1 - x0)){
        // always start at lower x-coordinate
        if (x0 > x1){
            plot_line_low(texture, x1, y1, x0, y0, colour);
        }else{
            plot_line_low(texture, x0, y0, x1, y1, colour);
        }
    }else{
        if(y0 > y1){
            // always start at lower y-coordinate
            plot_line_high(texture, x1, y1, x0, y0, colour);
        }else{
            plot_line_high(texture, x0, y0, x1, y1, colour);
        }
    }
}