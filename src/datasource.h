#ifndef LUMINATE_DATASOURCE_H
#define LUMINATE_DATASOURCE_H

#include "filter.h"

namespace luminate{

    class DataSeries{
        public:
            float* data();
            int numPoints();
            DataSeries(float data[], int num_points);
            ~DataSeries();
        private:
            float* data;
            int num_points;
    };

    template <typename T>
    class DataSource{
        public:
            T* getData(){
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
            T* data;
            bool has_new_data = true;
            virtual bool fetch() = 0;
    };

    class TextureDataSource : public DataSource<TexData>{
        public:
            TextureDataSource(TexData texture, FilterKernel filter);
        protected:
            TexData tex_data;
            FilterKernel filter;
            bool fetch() override;
    };

    class HistogramDataSource : public DataSource<DataSeries>{
        public:
            HistogramDataSource(TextureDataSource* tex_data_source, int bins);
        protected:
            TextureDataSource* tex_data_source;
            bool fetch() override;
    };

}
#endif