#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <widget.h>

namespace luminate{
    class Window {
        public:
            Window(int width, int height, const char* title);
            void addWidget(Widget* widget);
            void openWindow();
            void closeWindow();
            int getWidth(){ return width;}
            int getHeight(){ return height;}
            const char* getTitle(){ return title;}
        private:
            int width;
            int height;
            const char* title;
            bool stay_open;
            std::vector<Widget*> widgets;
            void draw();
    };
}
#endif