#include <datasource.h>
#include <filter.h>

#include <iostream>

using namespace luminate;

/* TextureDataSource Methods */

TextureDataSource::TextureDataSource(TexData texture, FilterKernel filter, float* strength_mask, float cutoff)
                 :DataSource(texture){
    this->filter = filter;
    this->strength_mask = strength_mask;
    this->cutoff = cutoff;
}

TextureDataSource::TextureDataSource(TexData texture, FilterKernel filter)
                                    :TextureDataSource(texture, filter, NULL, 1.0f){};

bool TextureDataSource::fetch(){
    // Apply filter to the current TexData and get new processed copy
    TexData filtered = apply_filter(this->data, this->filter, this->strength_mask, this->cutoff);
    // Make new processed TexData available
    this->data = filtered;
    // We got new data
    return true;
};

/* HistogramDataSource Methods */

HistogramDataSource::HistogramDataSource(TextureDataSource* tex_data_source, int bins)
                    :DataSource(getPixelHistogram(tex_data_source->getData(), bins)),
                     tex_data_source(tex_data_source), bins(bins){};

bool HistogramDataSource::fetch(){
    // Get data from the TextureDataSource and convert it to a histogram
    DataSeries new_series = getPixelHistogram(this->tex_data_source->getData(), this->bins);
    // Make new histogram available
    this->data = new_series;
    // We got new data
    return true;
};


/* Other functions */

DataSeries luminate::getPixelHistogram(TexData texture, int bins){
    // Access texture parameters
    float* src_data = texture.getData().get();
    int width = texture.getWidth();
    int height = texture.getHeight();
    int depth = texture.getDepth();

    // Interval 0.0 to 1.0 divided into n bins of this size
    float bin_size = 1.0f/bins;

    // Create new array to hold histogram data - 4 channels
    float* hist_data = new float[bins*4]{0};
    // for each pixel...
    for(int i = 0; i < width*height; i++){
        int pixel_idx = i*3;
        // get bin indices for the r, g, b, and overall luminance values
        // bin index is floor(x/bin_size) - int cast rounds down
        int r = (int)(src_data[pixel_idx]/bin_size);
        int g = (int)(src_data[pixel_idx+1]/bin_size);
        int b = (int)(src_data[pixel_idx+2]/bin_size);
        int l = (int)(pixel_luminance(&src_data[pixel_idx])/bin_size);
        // add to tally for appropriate bins
        hist_data[r] += 1.0f;
        hist_data[bins + g] += 1.0f;
        hist_data[2*bins + b] += 1.0f;
        hist_data[3*bins + l] += 1.0f;
    }

    DataSeries out_series(std::shared_ptr<float>(hist_data), bins, 4);
    return out_series;
}