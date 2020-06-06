#ifndef LUMINATE_DATASOURCE_H
#define LUMINATE_DATASOURCE_H

#include <texture.h>
#include <filter.h>

namespace luminate{

    /**
     * Represents N equal-length series of data points.
     */
    class DataSeries{
        public:
            std::shared_ptr<float> getData(){return data;};
            int numPoints(){return num_points;};
            int numLines(){return num_lines;};
            DataSeries(std::shared_ptr<float> data, int num_points, int num_lines)
            :data(data), num_points(num_points), num_lines(num_lines){};
        private:
            std::shared_ptr<float> data;
            int num_points;
            int num_lines;
    };

    /**
     * Provides access to dynamically changing data.
     */
    template <typename T>
    class DataSource{
        public:
            DataSource(T data): data(data){};
            T getData(){
                this->has_new_data = false;
                return this->data;
            };
            void update(){
                this->has_new_data = fetch();
            };
            bool hasNewData(){
                return this->has_new_data;
            }
        protected:
            T data;
            bool has_new_data = true;
            virtual bool fetch() = 0;
    };

    /**
     * Provides access to a dynamically changing texture.
     */
    class TextureDataSource : public DataSource<TexData>{
        public:
            TextureDataSource(TexData texture, FilterKernel filter);
            TextureDataSource(TexData texture, FilterKernel filter, float* strength_mask, float cutoff);
        protected:
            FilterKernel filter;
            float* strength_mask;
            float cutoff;
            bool fetch() override;
    };

    /**
     * Provides access to a dynamically changing DataSeries representing a histogram of the luminance
     * of pixels from a TextureDataSource.
     */
    class HistogramDataSource : public DataSource<DataSeries>{
        public:
            HistogramDataSource(TextureDataSource* tex_data_source, int bins);
        protected:
            TextureDataSource* tex_data_source;
            bool fetch() override;
            int bins;
    };

    /**
     * Get a 4-channel histogram of the luminance of pixels in a texture.
     */
    DataSeries getPixelHistogram(TexData texture, int bins);

}
#endif