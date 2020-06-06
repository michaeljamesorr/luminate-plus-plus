#ifndef WINDOW_H
#define WINDOW_H

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <widget.h>

namespace luminate{

    /**
     * An abstract class which should be extended to define how key events will be handled.
     */
    class KeyHandler{
        public:
            KeyHandler(void* params) : params(params) {};
            virtual void key_handler(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
        protected:
            void* params;
    };

    /**
     * An abstract class which should be extended to define how mouse events will be handled.
     */
    class MouseHandler{
        public:
            MouseHandler(void* params) : params(params) {};
            virtual void mouse_handler(GLFWwindow* window, int button, int action, int mods) = 0;
        protected:
            void* params;
    };

    /**
     * Manages the lifecycle of a GUI window and the rendering of a number of Widgets.
     */
    class Window {
        public:
            /**
             * Construct a Window with given dimensions.
             */
            Window(int width, int height, const char* title);
            /**
             * Perform initial setup of the OS window context. Must be called before most other methods.
             */
            void initialise();
            /**
             * Register a Widget to be rendered in this window.
             */
            void addWidget(Widget* widget);
            /**
             * Register a KeyHandler to handle key events.
             */
            void addKeyHandler(KeyHandler* key_handler);
            /**
             * Register a MouseHandler to handle mouse events.
             */
            void addMouseHandler(MouseHandler* mouse_handler);
            /**
             * Pass key events to KeyHandlers.
             */
            void notifyKeyHandlers(GLFWwindow* window, int key, int scancode, int action, int mods);
            /**
             * Pass mouse events to MouseHandlers.
             */
            void notifyMouseHandlers(GLFWwindow* window, int button, int action, int mods);
            /**
             * Call this to begin the rendering loop and pass program control to the Window.
             */
            void run();
            /**
             * Signal that the Window should close.
             */
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