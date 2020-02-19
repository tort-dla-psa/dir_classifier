#pragma once
#include <QObject>
#include <QByteArray>

class class_computer:public QObject{
    Q_OBJECT
public:
    explicit class_computer(QObject *parent = 0);
signals:
    void computed(QByteArray data);
public slots:
    void compute(QByteArray data);
};
