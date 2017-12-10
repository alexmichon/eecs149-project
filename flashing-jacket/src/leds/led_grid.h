#ifndef LED_GRID_H
#define LED_GRID_H

#include "led_strip.h"
#include "signals/signal.h"

class LedGrid {
public:
	LedGrid(LedStrip **strips, int nbStrips);

	virtual void begin();

	virtual void setSignal(Signal *signal);

	virtual void turnOff();
	virtual void refresh();

protected:
	LedStrip ** mStrips;
	const int mNbStrips;

	Signal *mSignal;
};

#endif