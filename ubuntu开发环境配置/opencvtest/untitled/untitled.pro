#-------------------------------------------------
#
# Project created by QtCreator 2018-12-17T14:29:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui
CONFIG += c++11
INCLUDEPATH += /usr/local/include/opencv4 \
               /usr/local/include/opencv4/opencv2
LIBS += /usr/local/lib/libopencv_core.so.4.0 \
        /usr/local/lib/libopencv_highgui.so.4.0\
        /usr/local/lib/libopencv_imgcodecs.so.4.0\
        /usr/local/lib/libopencv_videoio.so.4.0\
        /usr/local/lib/libopencv_imgproc.so.4.0

