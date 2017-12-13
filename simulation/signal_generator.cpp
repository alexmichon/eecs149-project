#include "signal_generator.h"

SignalGenerator::SignalGenerator(LedGridLayout *ledGridLayout) :
    mLedGridLayouts(ledGridLayout),
    mTimer(new QTimer())
{
    mTimer->setInterval(DEFAULT_TIMER);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(generate()));
}

void SignalGenerator::setRefreshRate(int msec) {
    mTimer->setInterval(msec);
}


void SignalGenerator::start() {
    qDebug("Starting signal");
    mLedGridLayouts->enable(true);
    mTimer->start();
}

void SignalGenerator::stop() {
    qDebug("Stopping signal");
    mLedGridLayouts->enable(false);
    mLedGridLayouts->refresh();
    mTimer->stop();
}
