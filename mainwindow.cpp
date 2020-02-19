#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPen>
#include <QColor>
#include <QDataStream>
#include <QSharedPointer>
#include <QVector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->plot = ui->widget;
    this->img_lbl = ui->label;
    connect(ui->actionopen_dir, &QAction::triggered, this, &MainWindow::open_dir_dialog);

    //top1
    plot->addGraph();
    plot->graph(0)->setPen(QPen(QColor(40, 120, 225)));
    auto bg = this->palette().color(QWidget::backgroundRole());
    plot->setBackground(bg);

    //time ticker on bottom
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    plot->xAxis->setTicker(timeTicker);
    plot->axisRect()->setupFullAxesBox();
    plot->yAxis->setRange(0, 1.0);

    read_dir_tmr = new QTimer(this);
    read_dir_wrkr = new data_getter();
    connect(read_dir_tmr, &QTimer::timeout, read_dir_wrkr, &data_getter::load_img);
    connect(this, &MainWindow::directory_selected, read_dir_wrkr, &data_getter::set_dir);
    connect(read_dir_wrkr, &data_getter::next_picture, this, &MainWindow::preprocess_img);
    read_dir_tmr->start(1000);

    proc_img_wrkr = new class_computer();
    proc_img_thr = new QThread();
    proc_img_wrkr->moveToThread(proc_img_thr);
    connect(proc_img_wrkr, &class_computer::computed, this, &MainWindow::postprocess);
    connect(this, &MainWindow::data_to_process, proc_img_wrkr, &class_computer::compute);
    proc_img_thr->start();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::preprocess_img(QImage img){
    QByteArray data;
    QDataStream str(&data, QIODevice::WriteOnly);
    str << img;
    this->img_lbl->setPixmap(QPixmap::fromImage(img));
    emit data_to_process(data);
}

void MainWindow::postprocess(QByteArray data){
    this->ui->listWidget->clear();
    size_t count = data.size()/sizeof(float);
    QDataStream str(&data, QIODevice::ReadOnly);
    QVector<float> q;
    str >> q;
    for(auto &val:q){
        this->ui->listWidget->addItem(QString::number(val));
    }

    auto elapsed = this->time.elapsed()/1000.;
    plot->graph(0)->addData(elapsed, q.front());
    plot->xAxis->setRange(elapsed, 8, Qt::AlignRight);
    plot->replot();
}

void MainWindow::open_dir_dialog(){
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    if(dialog.exec()){
        auto dir_path = dialog.selectedFiles().at(0);
        QDir dir(dir_path);
        this->time = QTime::currentTime();
        emit directory_selected(dir);
    }
}
