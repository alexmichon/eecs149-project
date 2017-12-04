#include "led_strip_layout.h"

LedStripLayout::LedStripLayout(QWidget *parent, int nLeds) : QVBoxLayout(parent), _nLeds(nLeds)
{
    for (int i = 0; i < nLeds; i++) {
        addWidget(new LedWidget(parent), i);
    }
}


int LedStripLayout::getLedCount() {
    return _nLeds;
}

LedWidget * LedStripLayout::getLed(int column) {
    return (LedWidget*) itemAt(column)->widget();
}


void LedStripLayout::refresh() {
    for (int i = 0; i < _nLeds; i++) {
        getLed(i)->repaint();
    }
}


void LedStripLayout::enable(bool enabled) {
    for (int i = 0; i < _nLeds; i++) {
        getLed(i)->setState(enabled);
    }
}

void LedStripLayout::setAmplitude(int amplitude, RGB color) {
    int max = amplitude;
    if (max > _nLeds) {
        max = _nLeds;
    }

    for (int i = 0; i < max; i++) {
        getLed(i)->setOnColor(QColor(color.r, color.g, color.b));
    }

    for (int i = max; i < _nLeds; i++) {
        getLed(i)->setOnColor(QColor(255, 255, 255));
    }
}
