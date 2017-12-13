#include "led_strip_simu.h"

LedStripSimu::LedStripSimu(uint16_t n, uint16_t offset, uint8_t p, neoPixelType t) :
	LedStrip(n, offset, p, t) {
}


void LedStripSimu::begin2() {

}

void LedStripSimu::show2() {
	for (int i = 0; i < numLEDs; i++) {
		uint32_t color = getPixelColor(i);
		Serial.print(i + mOffset);
		Serial.print("\t");
		Serial.print(color & 0x00FFFFFF);
		Serial.print("\t");
	}
	Serial.println();
}