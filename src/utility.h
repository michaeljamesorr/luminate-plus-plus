#ifndef LUMINATE_UTILITY_H
#define LUMINATE_UTILITY_H

#include <GL/glew.h>

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

GLuint GetShaderProgram(int index);

typedef struct{
    GLuint tex_id;
    int width;
    int height;
    int nrChannels;
} TexData;

TexData LoadGLTexture(const char * tex_file_path, GLenum wrapping, GLenum filtering);

void BindBlankTexture();

#endif