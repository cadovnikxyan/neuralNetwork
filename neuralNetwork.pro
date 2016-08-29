#-------------------------------------------------
#
# Project created by QtCreator 2016-08-29T08:41:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = neuralNetwork
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    neuro.cpp

HEADERS  += mainwindow.h \
    neuro.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS="-std=gnu++11"
