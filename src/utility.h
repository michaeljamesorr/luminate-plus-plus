#ifndef LUMINATE_UTILITY_H
#define LUMINATE_UTILITY_H

#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

GLuint GetShaderProgram(int index);

GLuint GetGLTexID();

void BindBlankTexture();

glm::ivec2* GetRandomIntPoints(int num_points, int min_x, int max_x, int min_y, int max_y);

glm::vec3* GetRandomColours(int num_colours);

#endif