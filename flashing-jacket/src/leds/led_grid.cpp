#include "led_grid.h"

LedGrid::LedGrid(LedStrip **strips, uint8_t nbStrips):
	mStrips(strips),
	mNbStrips(nbStrips) {
	mSignal = NULL;
}


void LedGrid::begin() {
	for (uint8_t i = 0; i < mNbStrips; i++) {
		mStrips[i]->begin2();
	}
}


void LedGrid::refresh() {
	if (mSignal == NULL) {
		Serial.println("Signal NULL");
		return;
	}

	mSignal->refresh();

	for (uint8_t i = 0; i < mNbStrips; i++) {
		LedStrip *strip = mStrips[i];
		for (uint16_t j = 0; j < strip->numPixels(); j++) {
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