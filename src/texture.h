#ifndef LUMINATE_TEXTURE_H
#define LUMINATE_TEXTURE_H

#include <memory>
#include <GL/glew.h>

namespace luminate{
    class TexData{
        public:
            TexData(int width, int height, int depth);
            TexData(std::shared_ptr<float> data, int width, int height, int depth);
            static TexData loadImage(const char* tex_file_path);
            void bindToGL(GLuint tex_id, GLenum wrapping, GLenum filtering);
            int getWidth(){return this->width;};
            int getHeight(){return this->height;};
            int getDepth(){return this->depth;};
            std::shared_ptr<float> getData(){return this->data;};
        private:
            std::shared_ptr<float> data;
            int width;
            int height;
            int depth;
    };
}

#endif