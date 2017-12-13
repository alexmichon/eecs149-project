#include "led_strip.h"

LedStrip::LedStrip(uint16_t n, uint16_t offset, uint8_t p, neoPixelType t) :
	Adafruit_NeoPixel(n, p, t),
	mOffset(offset) {

}

void LedStrip::begin2() {
	Adafruit_NeoPixel::begin();
}

void LedStrip::show2() {
	Adafruit_NeoPixel::show();
}

uint16_t LedStrip::getOffset() {
	return mOffset;
}