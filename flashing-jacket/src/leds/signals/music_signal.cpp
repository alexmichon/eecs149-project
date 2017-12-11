#include "music_signal.h"
#include <Adafruit_NeoPixel.h>

static uint32_t ON_COLOR = Adafruit_NeoPixel::Color(255, 0, 0);
static uint32_t OFF_COLOR = Adafruit_NeoPixel::Color(0, 0, 0);

MusicSignal::MusicSignal(int nbRows, int nbColumns, Microphone * microphone): Signal(nbRows, nbColumns), mMicrophone(microphone) {
	mLastHeights = (int*) malloc(nbRows * sizeof(int));
}

void MusicSignal::refresh() {
	if (mMicrophone->available()) {
		mMicrophone->read(mLastHeights);
	}
}

uint32_t MusicSignal::getColor(int index) {
	if (mLastHeights[getRow(index)] >= getColumn(index)) {
		return ON_COLOR;
	}
	return OFF_COLOR;
}