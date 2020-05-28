#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <widget.h>

namespace luminate{
    class Window {
        public:
            Window(int width, int height, const char* title);
            void initialise();
            void addWidget(Widget* widget);
            void run();
            void closeWindow();
            int getWidth(){ return width;}
            int getHeight(){ return height;}
            const char* getTitle(){ return title;}
        private:
            int width;
            int height;
            const char* title;
            bool stay_open;
            std::vector<Widget*> widgets;
            GLFWwindow * glfw_window;
            GLuint shader_program_id;
            void draw();
            void update();
    };
}
#endif