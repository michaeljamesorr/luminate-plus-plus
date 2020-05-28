#include <stdio.h>
#include <iostream>
#include <window.h>
#include <filter.h>
#include <texture.h>

using namespace luminate;

int main() {
    TexData texture1 = TexData::loadImage("textures/rangitoto.jpg");
    TexData scaled_tex = nearest_neighbour_scale(texture1, 480,360);
    TexData gray_tex = convert_grayscale(scaled_tex);
    TexData edge_tex = sobel_edge_detect(gray_tex);
    TexData onebit_tex = onebit_posterize(edge_tex, 0.95f);
    onebit_tex = invert(onebit_tex);
    float* canvas = new float[480*360*3]{0};
    canvas[3000] = 1.0f;
    std::shared_ptr<float> canvas_ptr(canvas);
    TexData canvas_tex(canvas_ptr, 480, 360, 3);
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