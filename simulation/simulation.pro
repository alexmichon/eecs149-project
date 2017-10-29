#-------------------------------------------------
#
# Project created by QtCreator 2017-10-28T13:02:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simulation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    led_widget.cpp \
    led_strip_layout.cpp \
    led_grid_layout.cpp

HEADERS  += mainwindow.h \
    led_widget.h \
    led_strip_layout.h \
    led_grid_layout.h

FORMS    += mainwindow.ui
