#ifndef SIGNAL_GENERATOR_H
#define SIGNAL_GENERATOR_H

#include <qtimer.h>
#include <QColor>
#include "led_grid_layout.h"


#define DEFAULT_TIMER 10

class SignalGenerator : public QObject {
    Q_OBJECT

public:
    SignalGenerator(LedGridLayout *ledGridLayout);

    virtual void start();
    virtual void stop();

    virtual void setRefreshRate(int msec);

public slots:
    virtual void generate() = 0;

protected:
    LedGridLayout * const mLedGridLayouts;

    QTimer *mTimer;
};

#endif // SIGNAL_GENERATOR_H
