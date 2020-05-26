#ifndef LUMINATE_WIDGET_H
#define LUMINATE WIDGET_H

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include <utility.h>

namespace luminate{

    class Widget{
        public:
            void draw();
            Widget(int x_pos, int y_pos, int width, int height, glm::vec3 tint, float opacity){
                this->x_pos = x_pos;
                this->y_pos = y_pos;
                this->width = width;
                this->height = height;
                this->tint = tint;
                this->opacity = opacity;
            };
            int x(){return x_pos;}
            int y(){return y_pos;}
            int w(){return width;}
            int h(){return height;}
            virtual void drawSetup(){};
        protected:
            virtual void drawImpl(){};
            virtual void update(){};
            int x_pos;
            int y_pos;
            int width;
            int height;
            glm::vec3 tint;
            float opacity;
    };

    class BlockWidget : public Widget {
        public:
            BlockWidget(int x_pos, int y_pos, int width, int height, glm::vec3 tint, float opacity);
            void drawSetup() override;
        protected:
            GLuint vertex_array;
            GLuint vertex_buffer;
            void drawImpl() override;
            void update() override;

    };

    class TextureWidget : public Widget {
        public:
            TextureWidget(int x_pos, int y_pos, int width, int height,
                          glm::vec3 tint, float opacity, TexData tex_data);
            void drawSetup() override;
        protected:
            void drawImpl() override;
            void update() override;
    };

}

#endif