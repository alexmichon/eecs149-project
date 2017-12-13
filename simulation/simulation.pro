#-------------------------------------------------
#
# Project created by QtCreator 2017-10-28T13:02:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += serialport

TARGET = simulation
TEMPLATE = app


SOURCES += main.cpp\
        #mainwindow.cpp \
    led_widget.cpp \
    led_strip_layout.cpp \
    led_grid_layout.cpp \
    #../src/audio/audio.cpp \
    #audio_thread.cpp \
    #transform_thread.cpp \
    #my_audioinput.cpp
    signal_generator.cpp \
    direction_generator.cpp \
    brake_generator.cpp \
    music_led_converter.cpp \
    arduino_serial.cpp \
    mainwindow.cpp

HEADERS  += \#mainwindow.h \
    led_widget.h \
    led_strip_layout.h \
    led_grid_layout.h \
    ui_mainwindow.h \
    #../src/audio/audio.h \
    #audio_thread.h \
    #transform_thread.h \
    #my_audioinput.h
    signal_generator.h \
    right_generator.h \
    left_generator.h \
    direction_generator.h \
    brake_generator.h \
    music_led_converter.h \
    arduino_serial.h \
    mainwindow.h

FORMS    += mainwindow.ui \
    mainwindow.ui

#unix|win32: LIBS += -lmpg123
#unix|win32: LIBS += -lao
#unix|win32: LIBS += -lfftw3
