#include <stdio.h>
#include <iostream>
#include <window.h>
#include <filter.h>
#include <texture.h>
#include <draw.h>

#include<glm/gtx/string_cast.hpp>

using namespace luminate;

int main() {

    int scale_x = 480;
    int scale_y = 360;

    TexData texture1 = TexData::loadImage("textures/beach.jpg");
    TexData scaled_tex = nearest_neighbour_scale(texture1, scale_x, scale_y);
    TexData gray_tex = convert_grayscale(scaled_tex);
    TexData edge_tex = sobel_edge_detect(gray_tex);
    TexData onebit_tex = onebit_posterize(edge_tex, 0.95f);
    // onebit_tex = binary_erosion(onebit_tex);
    // onebit_tex = binary_dilation(onebit_tex);
    onebit_tex = invert(onebit_tex);
    
    float* canvas = new float[scale_x*scale_y*3]{0};
    std::shared_ptr<float> canvas_ptr(canvas);
    TexData canvas_tex(canvas_ptr, scale_x, scale_y, 3);

    int num_points = 50;
    glm::ivec2* points = GetRandomIntPoints(num_points*2, 0, scale_x-1, 0, scale_y-1);
    glm::vec3* colours = GetRandomHues(num_points, 0.7f, 0.8f);
    for(int i = 0; i < num_points; i++){
        setRGBPixel(canvas_tex, points[i].x, points[i].y, ConvertHSVtoRGB(colours[i]));
    }

    // int num_lines = 10;
    // glm::ivec2* points = GetRandomIntPoints(num_lines*2, 0, scale_x-1, 0, scale_y-1);
    // glm::vec3* colours = GetRandomHues(num_lines, 0.8f, 0.9f);
    // for(int i = 0; i < num_lines; i++){
    //     std::cout << glm::to_string(colours[i]) << std::endl;
    //     drawRGBLine(canvas_tex, points[2*i].x, points[2*i].y,
    //                 points[2*i+1].x, points[2*i+1].y, ConvertHSVtoRGB(colours[i]));
    // }

    TextureDataSource tex_data_source(canvas_tex, luminate::FLOW_3, &(*onebit_tex.getData()), 0.8f);
    std::shared_ptr<float> data_ptr(GetRandomFloats(200));
    DataSeries data_series(data_ptr, 50, 4);
    DataSeries histogram = getPixelHistogram(scaled_tex, 20);
    // TexData filtered_tex = apply_filter(scaled_tex, luminate::FLOW_3, &(*gray_tex.getData()), 1.0f);
    Window window = Window(1024, 768, "Test Window");
    window.initialise();
    // TexData texture2 = LoadGLTexture("textures/rangitoto.jpg", GL_REPEAT, GL_LINEAR);
    HistogramDataSource hist_data_source(&tex_data_source, 20);
    glm::vec3* hist_colours = new glm::vec3[4]{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                                               glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f)};
    window.addWidget(new LineWidget(0, 568, 1024, 200,
                     glm::vec3(1.0f), 1.0f, &hist_data_source, colours));
    window.addWidget(new TextureWidget(0, 0, 1024, 568,
                     glm::vec3(0.0f), 1.0f, &tex_data_source));
    window.addWidget(new TextureWidget(0, 0, 1024, 568,
                     glm::vec3(0.0f), 0.5f, onebit_tex));
    window.run();
    return 0;
}