#ifndef LED_STRIP_H
#define LED_STRIP_H

#include <Adafruit_NeoPixel.h>
//#ifdef __AVR__
//#include <avr/power.h>
//#endif

class LedStrip: public Adafruit_NeoPixel {
public:
	LedStrip(uint16_t n, uint16_t offset=0, uint8_t p=6, neoPixelType t=NEO_GRB + NEO_KHZ800);

	virtual void begin2();
	virtual void show2();

	virtual uint16_t getOffset();

protected:
	uint16_t mOffset;
};

#endif