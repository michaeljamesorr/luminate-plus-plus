#include <stdio.h>
#include <iostream>
#include <window.h>
#include <filter.h>
#include <texture.h>
#include <draw.h>

using namespace luminate;

int main() {

    int scale_x = 480;
    int scale_y = 360;

    TexData texture1 = TexData::loadImage("textures/rangitoto.jpg");
    TexData scaled_tex = nearest_neighbour_scale(texture1, scale_x, scale_y);
    TexData gray_tex = convert_grayscale(scaled_tex);
    TexData edge_tex = sobel_edge_detect(gray_tex);
    TexData onebit_tex = onebit_posterize(edge_tex, 0.95f);
    onebit_tex = invert(onebit_tex);
    
    float* canvas = new float[scale_x*scale_y*3]{0};
    std::shared_ptr<float> canvas_ptr(canvas);
    TexData canvas_tex(canvas_ptr, scale_x, scale_y, 3);

    int num_random_points = 100;
    glm::ivec2* points = GetRandomIntPoints(num_random_points, 0, scale_x-1, 0, scale_y-1);
    glm::vec3* colours = GetRandomColours(num_random_points);
    for(int i = 0; i < num_random_points; i++){
        setRGBPixel(canvas_tex, points[i].x, points[i].y, colours[i]);
    }

    TextureDataSource tex_data_source(canvas_tex, luminate::FLOW_3, &(*onebit_tex.getData()), 1.0f);
    // TexData filtered_tex = apply_filter(scaled_tex, luminate::FLOW_3, &(*gray_tex.getData()), 1.0f);
    Window window = Window(1024, 768, "Test Window");
    window.initialise();
    // TexData texture2 = LoadGLTexture("textures/rangitoto.jpg", GL_REPEAT, GL_LINEAR);
    window.addWidget(new TextureWidget(0, 0, 1024, 768,
                     glm::vec3(0.0f), 1.0f, &tex_data_source));
    window.addWidget(new TextureWidget(0, 0, 1024, 768,
                     glm::vec3(0.0f), 0.5f, onebit_tex));
    window.run();
    return 0;
}