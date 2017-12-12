#include "transform_thread.h"
#include "../src/audio/audio.h"

TransformThread::TransformThread(LedGridLayout *grid) {
    _grid = grid;
    connect(this, SIGNAL(update(RGB*, int, int)), grid, SLOT(setColors(RGB*, int, int)));
}

void TransformThread::run() {
    exec();
}

void TransformThread::newBuffer(unsigned char *buffer, int buffer_size, long rate) {
    //qDebug("Received new buffer");

    RGB leds[DEFAULT_NB_STRIPS * DEFAULT_NB_LEDS];

    audio_to_rgb(buffer, buffer_size, rate, leds, DEFAULT_NB_STRIPS, DEFAULT_NB_LEDS);
    emit update(leds, DEFAULT_NB_STRIPS, DEFAULT_NB_LEDS);
}
