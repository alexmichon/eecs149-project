#include "music_signal.h"
#include <Adafruit_NeoPixel.h>

static uint32_t ON_COLOR = Adafruit_NeoPixel::Color(255, 0, 0);
static uint32_t OFF_COLOR = Adafruit_NeoPixel::Color(0, 0, 0);

MusicSignal::MusicSignal(uint8_t nbRows, uint8_t nbColumns, Microphone * microphone): Signal(nbRows, nbColumns), mMicrophone(microphone) {
	mLastHeights = (uint8_t*) malloc(nbRows * sizeof(uint8_t));
}

void MusicSignal::refresh() {
	if (mMicrophone->available()) {
		mMicrophone->read(mLastHeights);
	}
}

uint32_t MusicSignal::getColor(uint16_t index) {
	if (mLastHeights[getRow(index)] >= getColumn(index)) {
		return ON_COLOR;
	}
	return OFF_COLOR;
}