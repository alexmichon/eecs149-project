#include "led_strip_simu.h"

LedStripSimu::LedStripSimu(uint16_t n, uint16_t offset, uint8_t p, neoPixelType t) :
	LedStrip(n, offset, p, t) {
}


void LedStripSimu::begin2() {

}

void LedStripSimu::show2() {
	char str[16];
	for (int i = 0; i < numLEDs; i++) {
		uint32_t color = getPixelColor(i);
		sprintf(str, "%d\t%d\t%d\t%d", i+mOffset, (color >> 24) & 0xFF, (color >> 16) & 0xFF, (color >> 8) & 0xFF);
		Serial.println(str);;
	}
	Serial.flush();
}