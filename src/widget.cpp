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

void Widget::draw(){
    set_colour(this->tint, this->opacity);
    this->drawImpl();
};

/* BlockWidget Methods */

BlockWidget::BlockWidget(int x_pos, int y_pos, int width, int height, glm::vec3 tint, float opacity) 
    : Widget(x_pos, y_pos, width, height, tint, opacity){
};

void BlockWidget::drawSetup(){
    glGenVertexArrays(1, &(this->vertex_array));
    glBindVertexArray(this->vertex_array);

    GLfloat screen_space_vertices[] = {
        (float)this->x_pos, (float)this->y_pos + (float)this->height, 0.0f, // BOTTOM LEFT
        (float)this->x_pos, (float)this->y_pos, 0.0f, // TOP LEFT
        (float)this->x_pos + (float)this->width, (float)this->y_pos + (float)this->height, 0.0f, // BOTTOM RIGHT
        (float)this->x_pos + (float)this->width, (float)this->y_pos, 0.0f, // TOP RIGHT
    };

    glGenBuffers(1, &(this->vertex_buffer));
    glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screen_space_vertices), screen_space_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindVertexArray(0);
};

void BlockWidget::drawImpl(){
    glBindVertexArray(this->vertex_array);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
};

void BlockWidget::update(){};

/* TextureWidget Methods */

