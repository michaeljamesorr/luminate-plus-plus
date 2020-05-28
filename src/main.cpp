#include <stdio.h>
#include <iostream>
#include <window.h>
#include <filter.h>
#include <texture.h>

using namespace luminate;

int main() {
    TexData texture1 = TexData::loadImage("textures/skytower.jpg");
    TexData scaled_tex = nearest_neighbour_scale(texture1, 240,180);
    TexData gray_tex = convert_grayscale(scaled_tex);
    TexData filtered_tex = apply_filter(scaled_tex, luminate::FLOW_3, &(*gray_tex.getData()), 1.0f);
    Window window = Window(1024, 768, "Test Window");
    window.initialise();
    // TexData texture2 = LoadGLTexture("textures/rangitoto.jpg", GL_REPEAT, GL_LINEAR);
    window.addWidget(new TextureWidget(0, 0, 1024, 768,
                     glm::vec3(0.0f), 1.0f, filtered_tex));
    // window.addWidget(new luminate::TextureWidget(0, 0, 1024, 768,
    //                  glm::vec3(0.0f), 0.8f, texture2));
    window.run();
    return 0;
}