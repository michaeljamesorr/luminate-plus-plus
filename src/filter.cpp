#include <filter.h>


float* luminate::apply_filter(TexData texture, FilterKernel kernel){

    int tex_x_len = texture.width;
    int tex_y_len = texture.height;
    int tex_depth = texture.nrChannels;
    int kern_radius = kernel.radius;
    int kern_i_len = (2*kern_radius)+1;

    float* tex_data = texture.data;
    float* kern_weights = kernel.weights;

    float* result = new float[tex_x_len*tex_y_len*tex_depth];

    float acc[tex_depth];

    for(int x = 0; x < tex_x_len; x++){
        for(int y = 0; y < tex_y_len; y++){
            for(int k = 0; k < tex_depth; k++){
                acc[k] = 0.0f;
            }
            for(int i = -kern_radius; i < kern_radius+1; i++){
                for(int j = -kern_radius; j < kern_radius+1; j++){
                    if(x + i >= 0 && x + i < tex_x_len && y + j >= 0 && y + j < tex_y_len){
                        for(int k = 0; k < tex_depth; k++){
                            float curr_pixel = tex_data[(y+j)*tex_x_len*tex_depth + (x+i)*tex_depth + k];
                            float curr_weight = kern_weights[(kern_radius+j)*kern_i_len + kern_radius+i];
                            acc[k] += curr_pixel*curr_weight;
                        }
                    }
                }
            }
            for(int k = 0; k < tex_depth; k++){
                result[(y)*tex_x_len*tex_depth + (x)*tex_depth + k] = acc[k];
            }
        }
    }
    return result;
};