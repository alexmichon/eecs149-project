#include "led_grid.h"

LedGrid::LedGrid(LedStrip **strips, int nbStrips):
	mStrips(strips),
	mNbStrips(nbStrips) {
	mSignal = NULL;
}


void LedGrid::begin() {
	for (int i = 0; i < mNbStrips; i++) {
		mStrips[i]->begin2();
	}
}


void LedGrid::refresh() {
	if (mSignal == NULL) {
		return;
	}

	mSignal->refresh();

	for (int i = 0; i < mNbStrips; i++) {
		LedStrip *strip = mStrips[i];
		for (int j = 0; j < strip->numPixels(); j++) {
			strip->setPixelColor(j, mSignal->getColor(j + strip->getOffset()));
		}
		strip->show2();
	}
}

void LedGrid::turnOff() {
	// TODO
};


void LedGrid::setSignal(Signal *signal) {
	mSignal = signal;
}