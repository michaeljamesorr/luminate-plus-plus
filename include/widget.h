#ifndef LUMINATE_WIDGET_H
#define LUMINATE WIDGET_H

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include <utility.h>
#include <texture.h>
#include <datasource.h>

namespace luminate{

    /**
     * A graphical element which can be displayed in a Window. This is an abstract class which should be
     * extended to implement drawing and updating.
     */
    class Widget{
        public:
            /**
             * Draw the widget. To be called on each frame.
             */
            void draw();
            Widget(int x_pos, int y_pos, int width, int height, glm::vec3 tint, float opacity);
            Widget(int x_pos, int y_pos, int width, int height, glm::vec3 tint, float opacity, int data);
            int x(){return x_pos;}
            int y(){return y_pos;}
            int w(){return width;}
            int h(){return height;}
            /**
             * Prepare the widget for drawing.
             */
            virtual void drawSetup(){};
            /**
             * Update the widget.
             */
            virtual void update(){};
            /**
             * Set whether the widget should be drawn.
             */
            void setVisible(bool visible){this->visible = visible;};
        protected:
            /**
             * Override this method to implement drawing for a Widget subclass.
             */
            virtual void drawImpl() = 0;
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

    /**
     * A widget drawn as a solid coloured rectangle.
     */
    class BlockWidget : public Widget {
        public:
            BlockWidget(int x_pos, int y_pos, int width, int height, glm::vec3 tint, float opacity);
            void drawSetup() override;
            void update() override;
        protected:
            void drawImpl() override;

    };

    /**
     * A widget displaying a texture drawn on a rectangle.
     */
    class TextureWidget : public Widget {
        public:
            TextureWidget(int x_pos, int y_pos, int width, int height,
                          glm::vec3 tint, float opacity, TexData tex_data);
            TextureWidget(int x_pos, int y_pos, int width, int height,
                          glm::vec3 tint, float opacity, TextureDataSource* tex_data_source);
            void drawSetup() override;
            void update() override;
            TextureDataSource* getDataSource(){return tex_data_source;};
        protected:
            TextureDataSource* tex_data_source;
            GLuint tex_id;
            TexData tex_data;
            void drawImpl() override;
    };

    /**
     * A widget which renders a DataSeries as a number of line plots.
     */
    class LineWidget : public Widget {
        public:
            LineWidget(int x_pos, int y_pos, int width, int height,
                       glm::vec3 tint, float opacity, DataSeries data_series, glm::vec3* colours);
            LineWidget(int x_pos, int y_pos, int width, int height,
                       glm::vec3 tint, float opacity, DataSource<DataSeries>* series_data_source, glm::vec3* colours);
            void drawSetup() override;
            void update() override;
        protected:
            DataSeries data_series;
            DataSource<DataSeries>* series_data_source;
            void drawImpl() override;
            glm::vec3* colours;
    };

}

#endif