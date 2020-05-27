#ifndef LUMINATE_DATASOURCE_H
#define LUMINATE_DATASOURCE_H

#include "filter.h"

namespace luminate{

    class DataSeries{
        public:
            float* data();
            int width();
            int height();
            DataSeries(float data[], int width, int height);
            ~DataSeries();
        private:
            float* data;
            int width;
            int height;
    };

    class DataSource{
        public:
            DataSeries* getData(){
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
            DataSeries* data;
            bool has_new_data = true;
            virtual bool fetch() = 0;
    };

    class TextureDataSource : public DataSource{
        public:
            TextureDataSource(TexData texture, FilterKernel filter);
        protected:
            bool fetch() override;
    };

    class HistogramDataSource : public DataSource{
        public:
            HistogramDataSource(TextureDataSource* tex_data_source, int bins);
        protected:
            TextureDataSource* tex_data_source;
            bool fetch() override;
    };

}
#endif