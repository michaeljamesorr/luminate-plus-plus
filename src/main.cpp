#include <stdio.h>
#include <window.h>

int main() {
    luminate::Window window = luminate::Window(1024, 768, "Test Window");
    window.openWindow();
    return 0;
}