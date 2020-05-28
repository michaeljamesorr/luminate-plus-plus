#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <texture.h>

using namespace luminate;

TexData::TexData(std::shared_ptr<float> data, int width, int height, int depth){
	this->data = data;
	this->width = width;
	this->height = height;
	this->depth = depth;
};

TexData::TexData(int width, int height, int depth){
	std::shared_ptr<float> data_ptr(new float[width*height*depth]{0});
	this->data = data_ptr;
	this->width = width;
	this->height = height;
	this->depth = depth;
};

TexData TexData::loadImage(const char* tex_file_path){
	int width;
	int height;
	int depth;

	stbi_ldr_to_hdr_gamma(1.0f);
	float* stb_data = stbi_loadf(tex_file_path, &width,
                                    &height, &depth, 0);

	float* data_ptr = new float[width*height*depth];
	memcpy(data_ptr, stb_data, width*height*depth*sizeof(float));
	stbi_image_free(stb_data);

	std::shared_ptr<float> data(data_ptr);
	return TexData(data, width, height, depth);
};

void TexData::bindToGL(GLuint tex_id, GLenum wrapping, GLenum filtering){
	glBindTexture(GL_TEXTURE_2D, tex_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);

	GLenum format;
	if(this->depth == 1){
		format = GL_RED;
		GLint swizzleMask[] = {GL_RED, GL_RED, GL_RED, GL_ONE};
		glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
	}else{
		format = GL_RGB;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, format, this->width, 
				this->height, 0, format, GL_FLOAT, &(*this->data));
};