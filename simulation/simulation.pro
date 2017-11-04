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

HEADERS  += mainwindow.h \
    led_widget.h \
    led_strip_layout.h \
    led_grid_layout.h \
    ui_mainwindow.h \
    ../src/audio/audio.h \
    audio_thread.h \
    transform_thread.h \
    #my_audioinput.h

FORMS    += mainwindow.ui

unix|win32: LIBS += -lmpg123
unix|win32: LIBS += -lao
unix|win32: LIBS += -lfftw3
