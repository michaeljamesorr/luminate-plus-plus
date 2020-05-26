#include <stdio.h>
#include <iostream>
#include <window.h>

int main() {
    luminate::Window window = luminate::Window(1024, 768, "Test Window");
    window.initialise();
    window.addWidget(new luminate::BlockWidget(0, 0, 100, 100, glm::vec3(0.0f, 0.0f, 1.0f), 1.0f));
    window.addWidget(new luminate::BlockWidget(50, 50, 100, 100, glm::vec3(0.0f, 1.0f, 0.0f), 0.5f));
    TexData texture = LoadGLTexture("textures/test2.jpg", GL_REPEAT, GL_LINEAR);
    std::cout << texture.tex_id << std::endl;
    window.addWidget(new luminate::TextureWidget(200, 200, 200, 200,
                     glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, texture));
    window.run();
    return 0;
}