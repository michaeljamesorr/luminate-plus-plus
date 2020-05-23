#include <stdlib.h>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <utility.h>
#include <window.h>

using namespace luminate;

Window::Window(int width, int height, const char* title){
    this->stay_open = false;
    this->width = width;
    this->height = height;
    this->title = title;
};

void Window::addWidget(Widget* widget){
    this->widgets.push_back(widget);
};

void Window::openWindow(){
    glewExperimental = true;
    if( !glfwInit() ){
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    GLFWwindow* glfw_window;
    glfw_window = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);
    if( glfw_window == NULL ){
        fprintf( stderr, "Failed to open GLFW window.\n" );
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(glfw_window);
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return;
    }

    std::vector<Widget*>::iterator it;
    for(it = this->widgets.begin(); it != this->widgets.end(); it++){
        (*it)->drawSetup();
    }

    glfwSetInputMode(glfw_window, GLFW_STICKY_KEYS, GL_TRUE);

    GLuint program_ID = LoadShaders("shaders/SimpleVertexShader.glsl", "shaders/SimpleFragmentShader.glsl");

    do{
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glUseProgram(program_ID);

        this->draw();

        // Swap buffers
        glfwSwapBuffers(glfw_window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(glfw_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
        glfwWindowShouldClose(glfw_window) == 0 );
};

void Window::draw(){
    std::vector<Widget*>::iterator it;
    for(it = this->widgets.begin(); it != this->widgets.end(); it++){
        (*it)->draw();
    }
};

void Window::closeWindow(){
    this->stay_open = false;
};