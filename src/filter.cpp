#include <filter.h>
#include <texture.h>
#include <cassert>
#include <math.h>

using namespace luminate;

float pixel_luminance(float* rgb_pixel){
    return 0.2989 * rgb_pixel[0] + 0.5870* rgb_pixel[1] + 0.1140 * rgb_pixel[2];
}

float pixel_intensity(float* rgb_pixel){
    return (rgb_pixel[0] + rgb_pixel[1] + rgb_pixel[2])/3;
}

void clip_intensity(float* rgb_pixel, float max_intensity){
    float intensity = pixel_intensity(rgb_pixel);
    if(intensity > max_intensity){
        float ratio = max_intensity / intensity;
        for(int k = 0; k < 3; k++){
            rgb_pixel[k] = rgb_pixel[k]*ratio;
        }
    }
}

TexData luminate::invert(TexData texture){
    int width = texture.getWidth();
    int height = texture.getHeight();
    int depth = texture.getDepth();
    int size = width*height*depth;

    float* data = texture.getData().get();

    float* result = new float[size];

    for(int i = 0; i < size; i++){
        result[i] = 1.0f - data[i];
    }

    std::shared_ptr<float> result_ptr(result);
    TexData out_tex = {result_ptr, width, height, depth};
    return out_tex;
}

TexData combine(TexData tex1, TexData tex2){
    assert(tex1.getWidth()==tex2.getWidth()
        && tex1.getHeight()==tex2.getHeight()
        && tex1.getDepth()==tex2.getDepth());

    int width = tex1.getWidth();
    int height = tex1.getHeight();
    int depth = tex1.getDepth();
    int size = width*height*depth;

    float* data1 = tex1.getData().get();
    float* data2 = tex2.getData().get();

    float* result = new float[size];

    for(int i = 0; i < size; i++){
        float sq1 = data1[i]*data1[i];
        float sq2 = data2[i]*data2[i];
        float sum = sq1 + sq2;
        result[i] = sqrt(sum);
    }

    std::shared_ptr<float> result_ptr(result);
    TexData out_tex = {result_ptr, width, height, depth};
    return out_tex;
}

TexData luminate::apply_filter(TexData texture, FilterKernel kernel){
    return luminate::apply_filter(texture, kernel, NULL, 1.0f);
}

TexData luminate::apply_filter(TexData texture, FilterKernel kernel, float* strength_mask, float cutoff){

    int tex_x_len = texture.getWidth();
    int tex_y_len = texture.getHeight();
    int tex_depth = texture.getDepth();
    int kern_radius = kernel.radius;
    int kern_i_len = (2*kern_radius)+1;

    float* tex_data = &(*texture.getData());
    float* kern_weights = kernel.weights;

    float* result = new float[tex_x_len*tex_y_len*tex_depth];

    float acc[tex_depth];

    for(int y = 0; y < tex_y_len; y++){
        for(int x = 0; x < tex_x_len; x++){
            float* src_pixel = &tex_data[(y)*tex_x_len*tex_depth + (x)*tex_depth];
            float intensity;
            if(tex_depth == 3){
                intensity = pixel_intensity(src_pixel);
            }else{
                intensity = *src_pixel;
            }
            if(intensity < cutoff){
                for(int k = 0; k < tex_depth; k++){
                    acc[k] = 0.0f;
                }
                for(int i = -kern_radius; i < kern_radius+1; i++){
                    for(int j = -kern_radius; j < kern_radius+1; j++){
                        if(x + i >= 0 && x + i < tex_x_len && y + j >= 0 && y + j < tex_y_len){
                            for(int k = 0; k < tex_depth; k++){
                                float strength = 1.0f;
                                if(strength_mask){
                                    strength = strength_mask[(y+j)*tex_x_len + (x+i)];
                                }
                                float curr_pixel = tex_data[(y+j)*tex_x_len*tex_depth + (x+i)*tex_depth + k];
                                float curr_weight = kern_weights[(kern_radius+j)*kern_i_len + kern_radius+i];
                                acc[k] += curr_pixel*curr_weight*strength;
                            }
                        }
                    }
                }
                clip_intensity(acc, cutoff);
                for(int k = 0; k < tex_depth; k++){
                    result[(y)*tex_x_len*tex_depth + (x)*tex_depth + k] = acc[k];
                }
            }else{
                for(int k = 0; k < tex_depth; k++){
                    result[(y)*tex_x_len*tex_depth + (x)*tex_depth + k] = src_pixel[k];
                }
            }
        }
    }

    std::shared_ptr<float> result_ptr(result);
    TexData out_tex = {result_ptr, tex_x_len, tex_y_len, tex_depth};
    return out_tex;
};

TexData luminate::nearest_neighbour_scale(TexData texture, int width, int height){
    int src_width = texture.getWidth();
    int src_height = texture.getHeight();
    int depth = texture.getDepth();

    float x_scale = ((float)src_width)/((float)width);
    float y_scale = ((float)src_height)/((float)height);

    float* src_data = &(*texture.getData());
    float* result = new float[width*height*depth];

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            int i =  (int)((((float)x) + 0.5) * x_scale);
            int j =  (int)((((float)y) + 0.5) * y_scale);

            for(int k = 0; k < depth; k++){
                result[y*width*depth + x*depth + k] = src_data[j*src_width*depth + i*depth + k];
            }
        }
    }

    std::shared_ptr<float> result_ptr(result);
    TexData out_tex = {result_ptr, width, height, depth};
    return out_tex;
};

TexData luminate::sobel_edge_detect(TexData texture){
    TexData G_x1 = apply_filter(texture, SOBEL_EDGE_X1);
    TexData G_x2 = apply_filter(texture, SOBEL_EDGE_X2);
    TexData G_y1 = apply_filter(texture, SOBEL_EDGE_Y1);
    TexData G_y2 = apply_filter(texture, SOBEL_EDGE_Y2);

    TexData G_x = combine(G_x1, G_x2);
    TexData G_y = combine(G_y1, G_y2);
    return combine(G_x, G_y);
};

TexData luminate::convert_grayscale(TexData texture){
    int width = texture.getWidth();
    int height = texture.getHeight();
    int depth = texture.getDepth();

    float* src_data = texture.getData().get();
    float* result = new float[width*height];

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            result[y*width + x] = pixel_luminance(&src_data[y*width*depth + x*depth]);
        }
    }

    std::shared_ptr<float> result_ptr(result);
    TexData out_tex = {result_ptr, width, height, 1};
    return out_tex;
};

TexData luminate::onebit_posterize(TexData texture, float threshold){
    int width = texture.getWidth();
    int height = texture.getHeight();
    int depth = texture.getDepth();

    float* src_data = texture.getData().get();
    float* result = new float[width*height];

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            if(pixel_intensity(&src_data[y*width*depth + x*depth]) > threshold){
                result[y*width + x] = 1.0f;
            }else{
                result[y*width + x] = 0.0f;
            }
        }
    }

    std::shared_ptr<float> result_ptr(result);
    TexData out_tex = {result_ptr, width, height, 1};
    return out_tex;
};