#include "class_computer.h"
#include <QDateTime>
#include <QDataStream>
#include <QVector>
#include <QtAlgorithms>
#include <random>

class_computer::class_computer(QObject *parent)
    :QObject(parent)
{}

bool sort_func(float f, float f2){
    return f > f2;
}

void class_computer::compute(QByteArray data){
    const int classes = 16;
    QByteArray result;
    QDataStream data_str(&result, QIODevice::WriteOnly);

    unsigned int ms = static_cast<unsigned>(QDateTime::currentMSecsSinceEpoch());
    std::mt19937 gen(ms);
    float max = 1.0;
    std::uniform_real_distribution<> perc_gen(0, max);
    QVector<float> q;
    for(size_t i=0; i<classes; i++){
        auto perc = perc_gen(gen);
        max = max - perc;
        q.push_back(perc);
        perc_gen = std::uniform_real_distribution<>(0, max);
    }
    qSort(q.begin(), q.end(), sort_func);
    data_str << q;
    emit computed(result);
}
