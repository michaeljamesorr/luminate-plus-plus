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

    TexData original_tex = TexData::loadImage("textures/skytower.jpg");
    TexData scaled_tex = nearest_neighbour_scale(original_tex, scale_x, scale_y);
    TexData gray_tex = convert_grayscale(scaled_tex);
    TexData edge_tex = sobel_edge_detect(gray_tex);
    TexData onebit_tex = onebit_posterize(edge_tex, 0.90f);
    onebit_tex = invert(onebit_tex);
    
    float* canvas = new float[scale_x*scale_y*3]{0};
    std::shared_ptr<float> canvas_ptr(canvas);
    TexData canvas_tex(canvas_ptr, scale_x, scale_y, 3);

    TextureDataSource tex_data_source(canvas_tex, luminate::FLOW_3, &(*onebit_tex.getData()), 0.8f);
    std::shared_ptr<float> data_ptr(GetRandomFloats(200));
    DataSeries data_series(data_ptr, 50, 4);
    DataSeries histogram = getPixelHistogram(scaled_tex, 20);

    HistogramDataSource hist_data_source(&tex_data_source, 20);
    glm::vec3* hist_colours = new glm::vec3[4]{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                                               glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f)};

    Window window = Window(1024, 882, "Percolate");
    window.initialise();

    TextureWidget* canvas_widget = new TextureWidget(0, 0, 1024, 682, 
                                                     glm::vec3(0.0f), 1.0f, &tex_data_source);
    window.addWidget(canvas_widget);
    
    window.addWidget(new LineWidget(0, 682, 1024, 200,
                     glm::vec3(1.0f), 1.0f, &hist_data_source, hist_colours));

    TextureWidget* mask_widget = new TextureWidget(0, 0, 1024, 682,
                                                   glm::vec3(0.0f), 0.5f, onebit_tex);
    window.addWidget(mask_widget);

    TextureWidget* edge_widget = new TextureWidget(0, 0, 1024, 682,
                                                   glm::vec3(0.0f), 1.0f, edge_tex);
    window.addWidget(edge_widget);
    edge_widget->setVisible(false);

    TextureWidget* original_widget = new TextureWidget(0, 0, 1024, 682,
                                                   glm::vec3(0.0f), 1.0f, original_tex);
    window.addWidget(original_widget);
    original_widget->setVisible(false);

    typedef struct {
        TextureDataSource* tex_data_source;
        TextureWidget* mask_widget;
        TextureWidget* edge_widget;
        TextureWidget* original_widget;
    } WidgetContainer;

    WidgetContainer widgets;
    widgets.tex_data_source = &tex_data_source;
    widgets.mask_widget = mask_widget;
    widgets.edge_widget = edge_widget;
    widgets.original_widget = original_widget;

    class CanvasKeyHandler : public KeyHandler{
        public:
            CanvasKeyHandler(void* params) : KeyHandler(params){};
            void key_handler(GLFWwindow* window, int key, int scancode, int action, int mods) override{
                if(key == GLFW_KEY_SPACE && action == GLFW_PRESS){
                    WidgetContainer* widgets = (WidgetContainer*)(this->params);
                    TextureDataSource* tex_data_source = widgets->tex_data_source;
                    TexData canvas = tex_data_source->getData();
                    canvas.clear();
                }else if(key == GLFW_KEY_ENTER && action == GLFW_PRESS){
                    WidgetContainer* widgets = (WidgetContainer*)(this->params);
                    TextureDataSource* tex_data_source = widgets->tex_data_source;
                    TexData canvas = tex_data_source->getData();
                    int num_points = 50;
                    glm::ivec2* points = GetRandomIntPoints(num_points*2, 0, canvas.getWidth()-1, 0, canvas.getHeight()-1);
                    glm::vec3* colours = GetRandomHues(num_points, 0.7f, 0.8f);
                    for(int i = 0; i < num_points; i++){
                        setRGBPixel(canvas, points[i].x, points[i].y, ConvertHSVtoRGB(colours[i]));
                    }
                }else if(key == GLFW_KEY_1 && action == GLFW_PRESS){
                    WidgetContainer* widgets = (WidgetContainer*)(this->params);
                    widgets->original_widget->setVisible(true);
                    widgets->edge_widget->setVisible(false);
                }else if(key == GLFW_KEY_2 && action == GLFW_PRESS){
                    WidgetContainer* widgets = (WidgetContainer*)(this->params);
                    widgets->original_widget->setVisible(false);
                    widgets->edge_widget->setVisible(true);
                }else if(key == GLFW_KEY_3 && action == GLFW_PRESS){
                    WidgetContainer* widgets = (WidgetContainer*)(this->params);
                    widgets->original_widget->setVisible(false);
                    widgets->edge_widget->setVisible(false);
                }

            };
    };

    window.addKeyHandler(new CanvasKeyHandler((void*)&widgets));

    class CanvasClickHandler : public MouseHandler{
        public:
            CanvasClickHandler(void* params) : MouseHandler(params){};
            void mouse_handler(GLFWwindow* window, int button, int action, int mods) override{

                if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
                    double xpos, ypos;
                    glfwGetCursorPos(window, &xpos, &ypos);
                    
                    TextureWidget* canvas_widget = (TextureWidget*)(this->params);
                    int x0 = canvas_widget->x();
                    int x1 = x0 + canvas_widget->w();
                    int y0 = canvas_widget->y();
                    int y1 = y0 + canvas_widget->h();

                    if(xpos > x0 && xpos < x1 && ypos > y0 && ypos < y1){
                        TexData canvas = canvas_widget->getDataSource()->getData();
                        double widget_x = xpos - x0;
                        double widget_y = ypos - y0;

                        int tex_x, tex_y;
                        tex_x = (int)((widget_x/canvas_widget->w())*canvas.getWidth());
                        tex_y = (int)((widget_y/canvas_widget->h())*canvas.getHeight());

                        glm::vec3* colour = GetRandomHues(1, 0.7f, 0.8f);
                        setRGBPixel(canvas, tex_x, tex_y, ConvertHSVtoRGB(*colour));
                    }
                }
            };
    };

    window.addMouseHandler(new CanvasClickHandler((void*)canvas_widget));

    window.run();
    return 0;
}