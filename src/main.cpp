#include <stdio.h>
#include <iostream>
#include <window.h>
#include <filter.h>
#include <texture.h>
#include <draw.h>

#include<glm/gtx/string_cast.hpp>

using namespace luminate;

int main() {

    int scale_x = 480;
    int scale_y = 360;

    TexData texture1 = TexData::loadImage("textures/rangitoto.jpg");
    TexData scaled_tex = nearest_neighbour_scale(texture1, scale_x, scale_y);
    TexData gray_tex = convert_grayscale(scaled_tex);
    TexData edge_tex = sobel_edge_detect(gray_tex);
    TexData onebit_tex = onebit_posterize(edge_tex, 0.95f);
    // gray_tex *= 0.3;
    // onebit_tex += gray_tex;
    // onebit_tex.clampValues();
    onebit_tex = invert(onebit_tex);
    
    float* canvas = new float[scale_x*scale_y*3]{0};
    std::shared_ptr<float> canvas_ptr(canvas);
    TexData canvas_tex(canvas_ptr, scale_x, scale_y, 3);

    int num_points = 50;
    glm::ivec2* points = GetRandomIntPoints(num_points*2, 0, scale_x-1, 0, scale_y-1);
    glm::vec3* colours = GetRandomHues(num_points, 0.7f, 0.8f);
    for(int i = 0; i < num_points; i++){
        setRGBPixel(canvas_tex, points[i].x, points[i].y, ConvertHSVtoRGB(colours[i]));
    }

    TextureDataSource tex_data_source(canvas_tex, luminate::FLOW_3, &(*onebit_tex.getData()), 0.8f);
    std::shared_ptr<float> data_ptr(GetRandomFloats(200));
    DataSeries data_series(data_ptr, 50, 4);
    DataSeries histogram = getPixelHistogram(scaled_tex, 20);

    HistogramDataSource hist_data_source(&tex_data_source, 20);
    glm::vec3* hist_colours = new glm::vec3[4]{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                                               glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f)};

    Window window = Window(1024, 882, "Percolate");
    window.initialise();
    
    window.addWidget(new LineWidget(0, 682, 1024, 200,
                     glm::vec3(1.0f), 1.0f, &hist_data_source, hist_colours));
    window.addWidget(new TextureWidget(0, 0, 1024, 682,
                     glm::vec3(0.0f), 1.0f, &tex_data_source));
    window.addWidget(new TextureWidget(0, 0, 1024, 682,
                     glm::vec3(0.0f), 0.5f, onebit_tex));

    class CanvasResetHandler : public KeyHandler{
        public:
            CanvasResetHandler(void* params) : KeyHandler(params){};
            void key_handler(GLFWwindow* window, int key, int scancode, int action, int mods) override{
                std::cout << key << "," << scancode << "," << action << "," << mods << std::endl;
            };
    };

    window.addKeyHandler(new CanvasResetHandler((void*)&tex_data_source));

    class CanvasClickHandler : public MouseHandler{
        public:
            CanvasClickHandler(void* params) : MouseHandler(params){};
            void mouse_handler(GLFWwindow* window, int button, int action, int mods) override{
                std::cout << button << "," << action << "," << mods << std::endl;
            };
    };

    window.addMouseHandler(new CanvasClickHandler((void*)&tex_data_source));

    window.run();
    return 0;
}