#include <stdio.h>
#include <iostream>
#include <window.h>
#include <filter.h>

int main() {
    luminate::Window window = luminate::Window(1024, 768, "Test Window");
    window.initialise();
    TexData texture1 = LoadImage("textures/skytower.jpg");
    float* filtered_tex = luminate::apply_filter(texture1, luminate::SIMPLE_EDGE_DETECT);
    FreeTexData(texture1);
    texture1.data = filtered_tex;
    // TexData texture2 = LoadGLTexture("textures/rangitoto.jpg", GL_REPEAT, GL_LINEAR);
    window.addWidget(new luminate::TextureWidget(0, 0, 1024, 768,
                     glm::vec3(0.0f), 1.0f, texture1));
    // window.addWidget(new luminate::TextureWidget(0, 0, 1024, 768,
    //                  glm::vec3(0.0f), 0.8f, texture2));
    window.run();
    return 0;
}