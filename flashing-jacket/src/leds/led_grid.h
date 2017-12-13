#ifndef LED_GRID_H
#define LED_GRID_H

#include "led_strip.h"
#include "signals/signal.h"

class LedGrid {
public:
	LedGrid(LedStrip **strips, uint8_t nbStrips);

	virtual void begin();

	virtual void setSignal(Signal *signal);

	virtual void turnOff();
	virtual void refresh();

protected:
	LedStrip ** mStrips;
	const uint8_t mNbStrips;

	Signal *mSignal;
};

#endif