#include "direction_generator.h"


static int mod(int, int);

DirectionGenerator::DirectionGenerator(LedGridLayout *ledGridLayout, int direction) :
    SignalGenerator(ledGridLayout),
    mDirection(direction),
    mCount(0) {
    setRefreshRate(200);
}


void DirectionGenerator::generate() {
    qDebug("Generating direction signal...");
    int nbStrips = mLedGridLayouts->getStripCount();
    int nbLedPerStrips = mLedGridLayouts->getStrip(0)->getLedCount();

    int nbLeds = nbStrips * nbLedPerStrips;

    RGB *leds = (RGB *) malloc(nbLeds * sizeof(RGB));

    int middle = nbLedPerStrips / 2;

    for (int i = 0; i < nbStrips; i++) {
        for (int j = 0; j < nbLedPerStrips; j++) {
            int index = i * nbLedPerStrips + j;
            leds[index] = {0, 0, 0};
            for (int m = 0; m < 4; m++) {
                if ((i == mod((mCount + mDirection * m), nbStrips)) && (j == middle)) {
                    leds[index] = {255, 255, 255};
                }
            }

            for (int n = 1; n < 4; n++) {
                if ((i == mod((mCount + mDirection * n), nbStrips)) && ((j == middle + 3 - n) || (j == middle + n - 3))) {
                    leds[index] = {255, 255, 255};
                }
            }
        }
    }

    mCount = mod(mCount + mDirection, nbStrips);

    mLedGridLayouts->setColors(leds, nbStrips, nbLedPerStrips);
    mLedGridLayouts->refresh();
}


static int mod(int n, int p) {
    return ((n % p) + p) % p;
}
