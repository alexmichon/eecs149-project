#include "led_strip_simu.h"

LedStripSimu::LedStripSimu(uint16_t n, uint16_t offset, uint8_t p, neoPixelType t) :
	LedStrip(n, offset, p, t) {
	mString = (char *) malloc(13 * numPixels() * sizeof(char));
}


void LedStripSimu::begin2() {

}

void LedStripSimu::show2() {
	sprintf(mString, "");
	for (int i = 0; i < numLEDs; i++) {
		char tmp[14];
		uint32_t color = getPixelColor(i);
		sprintf(tmp, "%d\t%lu\t", i+mOffset, color & 0x00FFFFFF);
		strcat(mString, tmp);
	}
	Serial.println(mString);
	Serial.flush();
}