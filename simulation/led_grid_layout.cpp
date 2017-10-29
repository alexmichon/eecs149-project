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
