#pragma once

#include <QMainWindow>
#include <QThread>
#include <QTimer>
#include <QTime>
#include <QDir>
#include "qcustomplot-source/qcustomplot.h"
#include "data_getter.h"
#include "class_computer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    QThread* proc_img_thr;
    QTimer* read_dir_tmr;
    data_getter* read_dir_wrkr;
    class_computer* proc_img_wrkr;
    QLabel* img_lbl;
    QTime time;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void data_to_process(QByteArray data);
    void directory_selected(QDir dir);
public slots:
    void preprocess_img(QImage img);
    void postprocess(QByteArray data);
    void open_dir_dialog();
private:
    Ui::MainWindow *ui;
    QCustomPlot* plot;
};
