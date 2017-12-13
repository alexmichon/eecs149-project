#ifndef LED_STRIP_SIMU_H
#define LED_STRIP_SIMU_H

#include "led_strip.h"

class LedStripSimu: public LedStrip {
public:
	LedStripSimu(uint16_t n, uint16_t offset=0, uint8_t p=6, neoPixelType t=NEO_GRB + NEO_KHZ800);
	
	virtual void begin2() override;
	virtual void show2() override;
};

#endif