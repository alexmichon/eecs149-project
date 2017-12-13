#ifndef TRANSFORM_THREAD_H
#define TRANSFORM_THREAD_H

#include <QThread>
#include "led_grid_layout.h"
#include "../src/audio/audio.h"

class TransformThread: public QThread {
    Q_OBJECT

public:
    TransformThread(LedGridLayout *grid);

public slots:
    void newBuffer(unsigned char *buffer, int buffer_size, long rate);

signals:
    void update(RGB*, int, int);

private:
    void run();

    LedGridLayout *_grid;
};

#endif // TRANSFORM_THREAD_H
