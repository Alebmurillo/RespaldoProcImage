#-------------------------------------------------
#
# Project created by QtCreator 2013-03-14T21:14:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImProc_suite
TEMPLATE = app
LIBS += -L/usr/local/lib
SOURCES += main.cpp\
    imageimpro.cpp \
    openimprolib.cpp \
    openimprolib_opencvimpl.cpp \
    imageimpro_opencvimpl.cpp \
    controller.cpp \
    mainwindow.cpp \
    unittests.cpp \
    qcustomplot.cpp \
    videoimpro.cpp \
    videoimpro_opencvimpl.cpp \
    hogdetectorcpu.cpp \
    backgroundsegmentatoragmm.cpp \
    backgroundsegmentator.cpp



HEADERS  += \
    imageimpro.h \
    openimprolib.h \
    openimprolib_opencvimpl.h \
    imageimpro_opencvimpl.h \
    controller.h \
    mainwindow.h \
    includes.h \
 #   openimprolib_opencvgpuimpl.h \
    unittests.h \
    qcustomplot.h \
    videoimpro.h \
    videoimpro_opencvimpl.h \
    hogdetectorcpu.h \
    backgroundsegmentatoragmm.h \
    backgroundsegmentator.h

FORMS    += \
    mainwindow.ui

CONFIG += link_pkgconfig
PKGCONFIG += opencv
