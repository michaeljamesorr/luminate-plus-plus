#ifndef LUMINATE_UTILITY_H
#define LUMINATE_UTILITY_H

#include <GL/glew.h>
#include <stb/stb_image.h>

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

GLuint GetShaderProgram(int index);

typedef struct{
    GLuint tex_id;
    int width;
    int height;
    int nrChannels;
} TexData;

TexData LoadGLTexture(const char * tex_file_path, GLenum wrapping, GLenum filtering){
    TexData tex_data;
    unsigned char* data = stbi_load(tex_file_path, &tex_data.width,
                                    &tex_data.height, &tex_data.nrChannels, 0);

    glGenTextures(1, &tex_data.tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_data.tex_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_data.width, 
                 tex_data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

#endif