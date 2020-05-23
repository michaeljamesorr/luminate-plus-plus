#include <widget.h>

using namespace luminate;

void Widget::draw(){
    this->drawImpl();
};


BlockWidget::BlockWidget(int x_pos, int y_pos, int width, int height, glm::vec3 colour) 
    : Widget(x_pos, y_pos, width, height){
        this->colour = colour;
};

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f
};

void BlockWidget::drawSetup(){
    glGenVertexArrays(1, &(this->vertex_array));
    glBindVertexArray(this->vertex_array);

    glGenBuffers(1, &(this->vertex_buffer));
    glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
};

void BlockWidget::drawImpl(){
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(0);
};

void BlockWidget::update(){

};