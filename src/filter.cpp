#include <filter.h>

float pixel_luminance(float* rgb_pixel){
    return 0.2989 * rgb_pixel[0] + 0.5870* rgb_pixel[1] + 0.1140 * rgb_pixel[2];
}

float pixel_intensity(float* rgb_pixel){
    return (rgb_pixel[0] + rgb_pixel[1] + rgb_pixel[2])/3;
}

TexData luminate::apply_filter(TexData texture, FilterKernel kernel){
    return luminate::apply_filter(texture, kernel, NULL, 1.0f);
}

TexData luminate::apply_filter(TexData texture, FilterKernel kernel, float* strength_mask, float cutoff){

    int tex_x_len = texture.width;
    int tex_y_len = texture.height;
    int tex_depth = texture.nrChannels;
    int kern_radius = kernel.radius;
    int kern_i_len = (2*kern_radius)+1;

    float* tex_data = texture.data;
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

    TexData out_tex = {result, tex_x_len, tex_y_len, tex_depth};
    return out_tex;
};

TexData luminate::nearest_neighbour_scale(TexData texture, int width, int height){
    int src_width = texture.width;
    int src_height = texture.height;
    int depth = texture.nrChannels;

    float x_scale = ((float)src_width)/((float)width);
    float y_scale = ((float)src_height)/((float)height);

    float* src_data = texture.data;
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

    TexData out_tex = {result, width, height, depth};
    return out_tex;
};

TexData luminate::sobel_edge_detect(TexData texture){

};

TexData luminate::convert_grayscale(TexData texture){
    int width = texture.width;
    int height = texture.height;
    int depth = texture.nrChannels;

    float* src_data = texture.data;
    float* result = new float[width*height];

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            result[y*width + x] = pixel_luminance(&src_data[y*width*depth + x*depth]);
        }
    }

    TexData out_tex = {result, width, height, 1};
    return out_tex;
};

TexData luminate::onebit_posterize(TexData texture, float threshold){

};