#ifndef LUMINATE_FILTER_H
#define LUMINATE_FILTER_H

#include <texture.h>

namespace luminate{

    /**
     * A square matrix of floats to be used as an image processing kernel. 
     */
    typedef struct{
        float* weights;
        int radius;
    } FilterKernel;

    /**
     * A 3x3 gaussian blur.
     */
    static const FilterKernel GAUSS_BLUR_3 = {new float[9]{1.0f/16.0f, 2.0f/16.0f, 1.0f/16.0f,
                                                           2.0f/16.0f, 4.0f/16.0f, 2.0f/16.0f,
                                                           1.0f/16.0f, 2.0f/16.0f, 1.0f/16.0f}, 1};
    /**
     * A simple 3x3 edge detection kernel.
     */
    static const FilterKernel SIMPLE_EDGE_DETECT = {new float[9]{-1, -1, -1,
                                                                 -1,  8, -1,
                                                                 -1, -1, -1}, 1};
    /**
     * Kernel for Sobel edge detection: x-axis left.
     */
    static const FilterKernel SOBEL_EDGE_X1 = {new float[9]{ 1,  0, -1,
                                                             2,  0, -2,
                                                             1,  0, -1}, 1};
    /**
     * Kernel for Sobel edge detection: x-axis right.
     */
    static const FilterKernel SOBEL_EDGE_X2 = {new float[9]{-1,  0,  1,
                                                            -2,  0,  2,
                                                            -1,  0,  1}, 1}; 
    /**
     * Kernel for Sobel edge detection: y-axis up.
     */                                                           
    static const FilterKernel SOBEL_EDGE_Y1 = {new float[9]{ 1,  2,  1,
                                                             0,  0,  0,
                                                            -1, -2, -1}, 1};
    /**
     * Kernel for Sobel edge detection: y-axis down.
     */    
    static const FilterKernel SOBEL_EDGE_Y2 = {new float[9]{-1, -2, -1,
                                                             0,  0,  0,
                                                             1,  2,  1}, 1};
    /**
     * A 3x3 kernel which causes flow effect: essentially a gaussian blur which is not fully normalised, so
     * it causes an increase in average pixel brightness.
     */
    static const FilterKernel FLOW_3 = {new float[9]{1.0f/6.0f, 2.0f/6.0f, 1.0f/6.0f,
                                                     2.0f/6.0f, 4.0f/6.0f, 2.0f/6.0f,
                                                     1.0f/6.0f, 2.0f/6.0f, 1.0f/6.0f}, 1};

    /**
     * Apply a kernel to a texture and return a processed copy of the texture. Effect of the filter is
     * modulated by a strength mask of the same width and height as the texture, and an intensity cutoff.
     * 
     * @param texture Texture to be processed.
     * @param kernel Filter kernel defining the operation to be performed.
     * @param strength_mask Defines the strength of the effect of each pixel when processing.
     * @param cutoff Pixels will not be allowed to be set to a higher intensity than this.
     * @return A processed copy of the original texture.
     */
    TexData apply_filter(TexData texture, FilterKernel kernel, float* strength_mask, float cutoff);

    /**
     * Apply a kernel to a texture and return a processed copy of the texture. 
     * 
     * @param texture Texture to be processed.
     * @param kernel Filter kernel defining the operation to be performed.
     * @return A processed copy of the original texture.
     */
    TexData apply_filter(TexData texture, FilterKernel kernel);

    /**
     * Perform nearest neighbour scaling and return a scaled copy of a texture.
     */
    TexData nearest_neighbour_scale(TexData texture, int width, int height);

    /**
     * Perform Sobel edge detection on a texture.
     */
    TexData sobel_edge_detect(TexData texture);

    /**
     * Return a grayscale copy of a texture.
     */
    TexData convert_grayscale(TexData texture);

    /**
     * Return a binary posterized copy of a texture.
     * @param texture Texture to be processed.
     * @param threshold Pixels with higher intensity than this will be white, other pixels will be black.
     */
    TexData onebit_posterize(TexData texture, float threshold);

    /**
     * Get a binary image indicating whether a structuring element hits or misses at each pixel.
     * @param binary_texture A binary texture to be processed.
     * @param struct_elem A structuring element.
     * @return A binary texture of the same size as the original. Pixels will be white if the
     *         structuring element hits at this position, otherwise black.
     */
    TexData binary_hit_and_miss(TexData binary_texture, FilterKernel struct_elem);

    /**
     * Erode a binary image with a 3x3 square.
     */
    TexData binary_erosion(TexData binary_texture);

    /**
     * Dilate a binary image with a 3x3 square.
     */
    TexData binary_dilation(TexData binary_texture);

    /**
     * Thin edges to lines of single-pixel width.
     */
    TexData binary_thinning(TexData binary_texture);

    /**
     * Return a copy of a texture with the values of each pixel inverted.
     */
    TexData invert(TexData texture);

    /**
     * Get the luminance of a pixel.
     * @param rgb_pixel An array of three floats representing a single pixel.
     * @return The luminance of the pixel (0.2989*R + 0.5870*G + 0.1140*B).
     */
    float pixel_luminance(float* rgb_pixel);
}

#endif