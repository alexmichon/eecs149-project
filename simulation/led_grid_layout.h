#ifndef LED_GRID_LAYOUT_H
#define LED_GRID_LAYOUT_H

#include <QHBoxLayout>
#include "led_strip_layout.h"
#include "../src/audio/audio.h"

#define DEFAULT_NB_STRIPS 5

class LedGridLayout: public QHBoxLayout
{
    Q_OBJECT

public:
    explicit LedGridLayout(QWidget *parent = 0, int nStrips = DEFAULT_NB_STRIPS, int columnLeds = DEFAULT_NB_LEDS);

    int getStripCount();
    LedStripLayout * getStrip(int index);
    LedWidget * getLed(int strip, int led);

public slots:
    void setColors(RGB*, int, int);

private:
    int _nStrips;

};

#endif // LED_GRID_LAYOUT_H

