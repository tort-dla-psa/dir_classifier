#-------------------------------------------------
#
# Project created by QtCreator 2020-02-19T13:56:46
#
#-------------------------------------------------

QT       += core gui widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dir_app
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot-source/qcustomplot.cpp \
    data_getter.cpp \
    class_computer.cpp

HEADERS  += mainwindow.h \
    qcustomplot-source/qcustomplot.h \
    data_getter.h \
    class_computer.h

FORMS    += mainwindow.ui
