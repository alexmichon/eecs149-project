#ifndef AUDIO_THREAD_H
#define AUDIO_THREAD_H

#include <QThread>
#include "led_grid_layout.h"
#include "transform_thread.h"

class AudioThread: public QThread {
    Q_OBJECT

public:
    AudioThread(LedGridLayout *grid, char *filename);
    void cancel();

private:
    void run();

    char _filename[256];

signals:
    void newBuffer(unsigned char *, int, long);

private:
    bool _canceled;
};

#endif // AUDIO_THREAD_H

