#pragma once

#include <QObject>
#include <QDir>
#include <QImage>

class data_getter:public QObject{
    Q_OBJECT

    QFileInfoList images;
    QFileInfoList::iterator iter;
    bool iterator_set = false;
public:
    explicit data_getter(QObject *parent = 0);
signals:
    void set_pause(quint64 msec);
    void next_picture(QImage img);
public slots:
    void load_img();
    void set_dir(QDir dir);
};
