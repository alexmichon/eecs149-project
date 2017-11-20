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
    led_grid_layout.cpp \
    ../src/audio/audio.cpp \
    audio_thread.cpp \
    transform_thread.cpp \
    #my_audioinput.cpp
    signal_generator.cpp \
    mainwindow2.cpp \
    direction_generator.cpp \
    brake_generator.cpp

HEADERS  += mainwindow.h \
    led_widget.h \
    led_strip_layout.h \
    led_grid_layout.h \
    ui_mainwindow.h \
    ../src/audio/audio.h \
    audio_thread.h \
    transform_thread.h \
    #my_audioinput.h
    signal_generator.h \
    right_generator.h \
    mainwindow2.h \
    ui_mainwindow2.h \
    left_generator.h \
    direction_generator.h \
    brake_generator.h

FORMS    += mainwindow.ui

unix|win32: LIBS += -lmpg123
unix|win32: LIBS += -lao
unix|win32: LIBS += -lfftw3
