# include "brake_generator.h"


#define RED {255, 0, 0}


BrakeGenerator::BrakeGenerator(LedGridLayout *ledGridLayout) :
    SignalGenerator(ledGridLayout) {
    setRefreshRate(200);
}


void BrakeGenerator::generate() {
    int nbStrips = mLedGridLayouts->getStripCount();
    int nbLedPerStrips = mLedGridLayouts->getStrip(0)->getLedCount();

    int nbLeds = nbStrips * nbLedPerStrips;

    RGB *leds = (RGB *) malloc(nbLeds * sizeof(RGB));

    for (int i = 0; i < nbStrips; i++) {
        for (int j = 0; j < nbLedPerStrips; j++) {
            leds[i*nbLedPerStrips + j] = RED;
        }
    }

    mLedGridLayouts->setColors(leds, nbStrips, nbLedPerStrips);
    mLedGridLayouts->refresh();
}
