#include <iostream>

#include <widget.h>
#include <utility.h>

using namespace luminate;

void set_colour(glm::vec3 tint, float opacity){
    GLuint programId = GetShaderProgram(0);
    glUseProgram(programId);
    GLuint tint_loc = glGetUniformLocation(programId, "tint");
    GLuint opacity_loc = glGetUniformLocation(programId, "opacity");
    glUniform3fv(tint_loc, 1, &tint[0]);
    glUniform1f(opacity_loc, opacity);
}

void setup_quad(GLuint * vertex_array, GLuint * vertex_buffer, GLfloat* vertices){
    glGenVertexArrays(1, vertex_array);
    glBindVertexArray(*vertex_array);

    glGenBuffers(1, vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, *vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, 4*3*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindVertexArray(0);
}

GLfloat* get_screenspace_quad_vertices(int x_pos, int y_pos, int width, int height){
    GLfloat* screen_space_vertices = new GLfloat[12] {
        (float)x_pos, (float)y_pos + (float)height, 0.0f, // BOTTOM LEFT
        (float)x_pos, (float)y_pos, 0.0f, // TOP LEFT
        (float)x_pos + (float)width, (float)y_pos + (float)height, 0.0f, // BOTTOM RIGHT
        (float)x_pos + (float)width, (float)y_pos, 0.0f, // TOP RIGHT
    };
    return screen_space_vertices;
}

void Widget::draw(){
    if(this->visible){
        set_colour(this->tint, this->opacity);
        this->drawImpl();
    }
    
};

/* BlockWidget Methods */

BlockWidget::BlockWidget(int x_pos, int y_pos, int width, int height, glm::vec3 tint, float opacity) 
    : Widget(x_pos, y_pos, width, height, tint, opacity){
};

void BlockWidget::drawSetup(){
    GLfloat* screenspace_vertices = get_screenspace_quad_vertices(this->x_pos, this->y_pos,
                                                                  this->width, this->height);
    setup_quad(&(this->vertex_array), &(this->vertex_buffer), screenspace_vertices);
};

void BlockWidget::drawImpl(){
    glBindVertexArray(this->vertex_array);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
};

void BlockWidget::update(){};

/* TextureWidget Methods */

TextureWidget::TextureWidget(int x_pos, int y_pos, int width, int height,
                             glm::vec3 tint, float opacity, TexData tex_data) 
    : Widget(x_pos, y_pos, width, height, tint, opacity){
        this->tex_data = tex_data;
};

void TextureWidget::drawSetup(){
    GLfloat* screenspace_vertices = get_screenspace_quad_vertices(this->x_pos, this->y_pos,
                                                                  this->width, this->height);
    setup_quad(&(this->vertex_array), &(this->vertex_buffer), screenspace_vertices);
}

void TextureWidget::drawImpl(){
    glBindVertexArray(this->vertex_array);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void TextureWidget::update(){

}