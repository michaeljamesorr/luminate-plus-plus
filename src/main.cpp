#include <stdio.h>
#include <iostream>
#include <window.h>
#include <filter.h>

int main() {
    TexData texture1 = LoadImage("textures/skytower.jpg");
    TexData scaled_tex = luminate::nearest_neighbour_scale(texture1, 240,180);
    TexData gray_tex = luminate::convert_grayscale(scaled_tex);
    TexData filtered_tex = luminate::apply_filter(scaled_tex, luminate::FLOW_3, gray_tex.data, 1.0f);
    luminate::Window window = luminate::Window(1024, 768, "Test Window");
    window.initialise();
    // TexData texture2 = LoadGLTexture("textures/rangitoto.jpg", GL_REPEAT, GL_LINEAR);
    window.addWidget(new luminate::TextureWidget(0, 0, 1024, 768,
                     glm::vec3(0.0f), 1.0f, filtered_tex));
    // window.addWidget(new luminate::TextureWidget(0, 0, 1024, 768,
    //                  glm::vec3(0.0f), 0.8f, texture2));
    window.run();
    return 0;
}