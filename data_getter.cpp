#include "data_getter.h"
#include <QThread>
#include <QImageReader>

data_getter::data_getter(QObject *parent)
    :QObject(parent)
{}

void data_getter::load_img(){
    if(!iterator_set){
        return;
    }
    QImageReader image_reader(iter->absoluteFilePath());
    auto img = image_reader.read();
    emit next_picture(img);
    iter++;
    if(iter == images.end()){
        iter = images.begin();
    }
}

void data_getter::set_dir(QDir dir){
    auto filter = QStringList() << "*.jpg" << "*.JPG" << "*.png" << "*.PNG";
    this->images =  dir.entryInfoList(filter, QDir::Files);
    this->iter = images.begin();
    iterator_set = true;
}
