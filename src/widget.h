#ifndef LUMINATE_WIDGET_H
#define LUMINATE WIDGET_H

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include <utility.h>
#include <texture.h>
#include <datasource.h>

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
            virtual void update(){};
            void setVisible(bool visible){this->visible = visible;};
        protected:
            virtual void drawImpl(){};
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
            void update() override;
        protected:
            void drawImpl() override;

    };

    class TextureWidget : public Widget {
        public:
            TextureWidget(int x_pos, int y_pos, int width, int height,
                          glm::vec3 tint, float opacity, TexData tex_data);
            TextureWidget(int x_pos, int y_pos, int width, int height,
                          glm::vec3 tint, float opacity, TextureDataSource* tex_data_source);
            void drawSetup() override;
            void update() override;
        protected:
            TextureDataSource* tex_data_source;
            GLuint tex_id;
            TexData tex_data;
            void drawImpl() override;
    };

    class LineWidget : public Widget {
        public:
            LineWidget(int x_pos, int y_pos, int width, int height,
                       glm::vec3 tint, float opacity, DataSeries data_series);
            LineWidget(int x_pos, int y_pos, int width, int height,
                       glm::vec3 tint, float opacity, DataSource<DataSeries>* series_data_source);
            void drawSetup() override;
            void update() override;
        protected:
            DataSeries data_series;
            DataSource<DataSeries>* series_data_source;
            void drawImpl() override;
    };

}

#endif