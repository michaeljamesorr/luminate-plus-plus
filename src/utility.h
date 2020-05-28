#ifndef LUMINATE_UTILITY_H
#define LUMINATE_UTILITY_H

#include <GL/glew.h>

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

GLuint GetShaderProgram(int index);

GLuint GetGLTexID();

void BindBlankTexture();

#endif