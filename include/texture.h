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
            void clampValues();
            void clear();
            int getWidth(){return this->width;};
            int getHeight(){return this->height;};
            int getDepth(){return this->depth;};
            std::shared_ptr<float> getData(){return this->data;};
            TexData& operator+=(const TexData& rhs);
            TexData& operator*=(const TexData& rhs);
            TexData& operator+=(const float rhs);
            TexData& operator*=(const float rhs);
            friend TexData operator+(TexData lhs, const TexData& rhs){
                lhs += rhs;
                return lhs;
            };
            friend TexData operator*(TexData lhs, const TexData& rhs){
                lhs *= rhs;
                return lhs;
            };
            friend TexData operator+(TexData lhs, const float rhs){
                lhs += rhs;
                return lhs;
            };
            friend TexData operator*(TexData lhs, const float rhs){
                lhs *= rhs;
                return lhs;
            };
        private:
            std::shared_ptr<float> data;
            int width;
            int height;
            int depth;
    };
}

#endif