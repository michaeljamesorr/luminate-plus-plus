#include <stdio.h>
#include <window.h>

int main() {
    luminate::Window window = luminate::Window(1024, 768, "Test Window");
    window.addWidget(new luminate::BlockWidget(0, 0, 1024, 768, glm::vec3(0.0f, 0.0f, 1.0f)));
    window.openWindow();
    return 0;
}