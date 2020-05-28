#include <iostream>

#include <utility.h>
#include <texture.h>
#include <widget.h>

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

    GLuint tex_buffer;
    GLfloat tex_coords[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
    };

    glGenBuffers(1, vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, *vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, 4*5*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    glBindVertexArray(0);
}

GLfloat* get_screenspace_quad_vertices(int x_pos, int y_pos, int width, int height){
    GLfloat* screen_space_vertices = new GLfloat[20] {
        // positions                                                     // tex coords
        (float)x_pos, (float)y_pos + (float)height, 0.0f,                0.0f, 1.0f, // BOTTOM LEFT
        (float)x_pos, (float)y_pos, 0.0f,                                0.0f, 0.0f, // TOP LEFT
        (float)x_pos + (float)width, (float)y_pos + (float)height, 0.0f, 1.0f, 1.0f, // BOTTOM RIGHT
        (float)x_pos + (float)width, (float)y_pos, 0.0f,                 1.0f, 0.0f, // TOP RIGHT
    };
    return screen_space_vertices;
}

Widget::Widget(int x_pos, int y_pos, int width, int height, glm::vec3 tint, float opacity){
                this->x_pos = x_pos;
                this->y_pos = y_pos;
                this->width = width;
                this->height = height;
                this->tint = tint;
                this->opacity = opacity;
};

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
    BindBlankTexture();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
};

void BlockWidget::update(){};

/* TextureWidget Methods */

TextureWidget::TextureWidget(int x_pos, int y_pos, int width, int height,
                             glm::vec3 tint, float opacity, TexData tex_data) 
    : Widget(x_pos, y_pos, width, height, tint, opacity), tex_data(tex_data), tex_data_source(NULL){
        this->tex_id = GetGLTexID();
        this->tex_data.bindToGL(tex_id, GL_REPEAT, GL_NEAREST);
};

TextureWidget::TextureWidget(int x_pos, int y_pos, int width, int height,
                             glm::vec3 tint, float opacity, TextureDataSource* tex_data_source) 
    : Widget(x_pos, y_pos, width, height, tint, opacity), tex_data(tex_data_source->getData()){
        this->tex_id = GetGLTexID();
        this->tex_data.bindToGL(tex_id, GL_REPEAT, GL_NEAREST);
        this->tex_data_source = tex_data_source;
};

void TextureWidget::drawSetup(){
    GLfloat* screenspace_vertices = get_screenspace_quad_vertices(this->x_pos, this->y_pos,
                                                                  this->width, this->height);
    setup_quad(&(this->vertex_array), &(this->vertex_buffer), screenspace_vertices);
}

void TextureWidget::drawImpl(){
    glBindVertexArray(this->vertex_array);
    glBindTexture(GL_TEXTURE_2D, this->tex_id);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void TextureWidget::update(){
    if(tex_data_source){
        tex_data_source->update();
        if(tex_data_source->hasNewData()){
            TexData filtered = tex_data_source->getData();
            this->tex_data = filtered;
            this->tex_data.bindToGL(this->tex_id, GL_REPEAT, GL_NEAREST);
        }
    }
}