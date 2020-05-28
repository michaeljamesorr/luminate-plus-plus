#ifndef LUMINATE_WIDGET_H
#define LUMINATE WIDGET_H

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include <utility.h>
#include <texture.h>

namespace luminate{

    class Widget{
        public:
            void draw();
            Widget(int x_pos, int y_pos, int width, int height, glm::vec3 tint, float opacity);
            Widget(int x_pos, int y_pos, int width, int height, glm::vec3 tint, float opacity, int data);
            int x(){return x_pos;}
            int y(){return y_pos;}
            int w(){return width;}
            int h(){return height;}
            virtual void drawSetup(){};
            void setVisible(bool visible){this->visible = visible;};
        protected:
            virtual void drawImpl(){};
            virtual void update(){};
            int x_pos;
            int y_pos;
            int width;
            int height;
            glm::vec3 tint;
            float opacity;
            GLuint vertex_array;
            GLuint vertex_buffer;
            bool visible = true;
    };

    class BlockWidget : public Widget {
        public:
            BlockWidget(int x_pos, int y_pos, int width, int height, glm::vec3 tint, float opacity);
            void drawSetup() override;
        protected:
            void drawImpl() override;
            void update() override;

    };

    class TextureWidget : public Widget {
        public:
            TextureWidget(int x_pos, int y_pos, int width, int height,
                          glm::vec3 tint, float opacity, TexData tex_data);
            void drawSetup() override;
        protected:
            GLuint tex_id;
            TexData tex_data;
            void drawImpl() override;
            void update() override;
    };

    class LineWidget : public Widget {
        public:
            LineWidget(int x_pos, int y_pos, int width, int height,
                       glm::vec3 tint, float opacity, float* data_points, int num_points);
            void drawSetup() override;
        protected:
            float* data_points;
            int num_points;
            void drawImpl() override;
            void update() override;
    };

}

#endif