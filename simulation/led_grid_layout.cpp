#include "led_grid_layout.h"

LedGridLayout::LedGridLayout(QWidget *parent, int nStrips, int nLeds) : QHBoxLayout(parent), _nStrips(nStrips) {
    for (int i = 0; i < nStrips; i++) {
        addLayout(new LedStripLayout(parent, nLeds));
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
/*
void LedGridLayout::setColors(RGB *leds, int leds_strips, int leds_rows) {
    for (int i = 0; i < leds_strips; i++) {
        LedStripLayout *stripLayout = getStrip(i);
        for (int j = 0; j < leds_rows; j++) {
            LedWidget *widget = stripLayout->getLed(j);
            widget->setOnColor(QColor(leds[i*leds_rows+j].r, leds[i*leds_rows+j].g, leds[i*leds_rows+j].b));
        }
    }
}

void LedGridLayout::setAmplitudes(int len, int *amplitudes) {
    RGB color = {255, 0, 0};
    for (int i = 0; i < len; i++) {
        LedStripLayout *stripLayout = getStrip(i);
        if (stripLayout == NULL) { continue; }

        stripLayout->setAmplitude(amplitudes[i], color);
    }

    refresh();
}
*/
void LedGridLayout::refresh() {
    for (int i = 0; i < _nStrips; i++) {
        getStrip(i)->refresh();
    }
}


void LedGridLayout::enable(bool enabled) {
    for (int i = 0; i < _nStrips; i++) {
        getStrip(i)->enable(enabled);
    }
}

/*
void LedGridLayout::setStripAmplitude(int strip, int amplitude, RGB color) {
    LedStripLayout *stripLayout = getStrip(strip);
    if (stripLayout != NULL) {
        stripLayout->setAmplitude(amplitude, color);
    }
}
*/

void LedGridLayout::setColor(int index, QColor *color) {
    int stripIndex = index / getStrip(0)->getLedCount();
    int ledIndex = index - stripIndex * getStrip(0)->getLedCount() ;

    LedStripLayout *strip = getStrip(stripIndex);
    if (strip != NULL) {
        strip->setColor(ledIndex, color);
    }
}
