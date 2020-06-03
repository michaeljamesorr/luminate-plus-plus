#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <functional>

#include <widget.h>

namespace luminate{

    class KeyHandler{
        public:
            KeyHandler(void* params) : params(params) {};
            virtual void key_handler(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
        private:
            void* params;
    };

    class MouseHandler{
        public:
            MouseHandler(void* params) : params(params) {};
            virtual void mouse_handler(GLFWwindow* window, int button, int action, int mods) = 0;
        private:
            void* params;
    };


    class Window {
        public:
            Window(int width, int height, const char* title);
            void initialise();
            void addWidget(Widget* widget);
            void addKeyHandler(KeyHandler* key_handler);
            void addMouseHandler(MouseHandler* mouse_handler);
            void notifyKeyHandlers(GLFWwindow* window, int key, int scancode, int action, int mods);
            void notifyMouseHandlers(GLFWwindow* window, int button, int action, int mods);
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
            std::vector<KeyHandler*> key_handlers;
            std::vector<MouseHandler*> mouse_handlers;
            GLFWwindow * glfw_window;
            GLuint shader_program_id;
            void draw();
            void update();
    };

}
#endif