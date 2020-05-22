#ifndef LUMINATE_WIDGET_H
#define LUMINATE WIDGET_H
namespace luminate{

    class Widget{
        public:
            void draw();
            Widget(int x_pos, int y_pos, int width, int height){
                this->x_pos = x_pos;
                this->y_pos = y_pos;
                this->width = width;
                this->height = height;
            };
            int x(){return x_pos;}
            int y(){return y_pos;}
            int w(){return width;}
            int h(){return height;}
        protected:
            virtual void drawImpl() = 0;
            virtual void update() = 0;
            int x_pos;
            int y_pos;
            int width;
            int height;
    };

    class BlockWidget : public Widget {
        public:
            BlockWidget(int x_pos, int y_pos, int width, int height);
    };

    class TextureWidget : public Widget {
        public:
            TextureWidget(int x_pos, int y_pos, int width, int height, float* data);
    };

}

#endif