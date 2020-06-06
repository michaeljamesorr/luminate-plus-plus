#ifndef LUMINATE_TEXTURE_H
#define LUMINATE_TEXTURE_H

#include <memory>
#include <GL/glew.h>

namespace luminate{

    /**
     * Represents a texture and associated data.
     */
    class TexData{
        public:
            /**
             * Constructor producing a blank texture with specified dimension.
             */
            TexData(int width, int height, int depth);
            /**
             * Constructor producing a texture of specified dimensions with the provided data array.
             */
            TexData(std::shared_ptr<float> data, int width, int height, int depth);
            /**
             * Load a texture from an image file.
             */
            static TexData loadImage(const char* tex_file_path);
            /**
             * Bind this texture in OpenGL using the specified GL handle.
             */
            void bindToGL(GLuint tex_id, GLenum wrapping, GLenum filtering);
            /**
             * Clamp all values in the texture to between 0.0 and 1.0.
             */
            void clampValues();
            /**
             * Clear all data, leaving a blank texture.
             */
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