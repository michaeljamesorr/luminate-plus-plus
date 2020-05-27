#ifndef LUMINATE_UTILITY_H
#define LUMINATE_UTILITY_H

#include <GL/glew.h>

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

GLuint GetShaderProgram(int index);

typedef struct{
    float* data;
    int width;
    int height;
    int nrChannels;
} TexData;

TexData LoadImage(const char* tex_file_path);

void FreeTexData(TexData tex_data);

GLuint LoadGLTexture(TexData texture, GLenum wrapping, GLenum filtering);

void BindBlankTexture();

#endif