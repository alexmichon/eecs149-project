#include "led_grid_layout.h"

LedGridLayout::LedGridLayout(QWidget *parent, int nStrips, int nLeds) : QHBoxLayout(parent), _nStrips(nStrips) {
    for (int i = 0; i < nStrips; i++) {
        addLayout(new LedStripLayout(parent, nLeds), i);
    }
}

int LedGridLayout::getStripCount() {
    return _nStrips;
}

LedStripLayout * LedGridLayout::getStrip(int index) {
    return (LedStripLayout *) itemAt(index)->layout();
}

LedWidget * LedGridLayout::getLed(int strip, int led) {
    return getStrip(strip)->getLed(led);
}

void LedGridLayout::setColors(RGB *leds, int leds_strips, int leds_rows) {
    //qDebug("Received update colors");
    for (int i = 0; i < leds_strips; i++) {
        LedStripLayout *stripLayout = getStrip(i);
        for (int j = 0; j < leds_rows; j++) {
            LedWidget *widget = stripLayout->getLed(j);
            widget->setOnColor(QColor(leds[i*leds_rows+j].r, leds[i*leds_rows+j].g, leds[i*leds_rows+j].b));
        }
    }
}
