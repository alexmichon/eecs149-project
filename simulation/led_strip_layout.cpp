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
