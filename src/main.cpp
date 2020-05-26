#include <stdio.h>
#include <iostream>
#include <window.h>

int main() {
    luminate::Window window = luminate::Window(1024, 768, "Test Window");
    window.initialise();
    TexData texture1 = LoadGLTexture("textures/skytower.jpg", GL_REPEAT, GL_LINEAR);
    // TexData texture2 = LoadGLTexture("textures/rangitoto.jpg", GL_REPEAT, GL_LINEAR);
    window.addWidget(new luminate::TextureWidget(0, 0, 1024, 768,
                     glm::vec3(0.0f), 1.0f, texture1));
    // window.addWidget(new luminate::TextureWidget(0, 0, 1024, 768,
    //                  glm::vec3(0.0f), 0.8f, texture2));
    window.run();
    return 0;
}