#ifndef DIRECTION_SIGNAL_H
#define DIRECTION_SIGNAL_H

#include "signal.h"

class DirectionSignal: public Signal {
public:
	DirectionSignal(uint8_t nbRows, uint8_t nbColumns, int8_t direction);

	virtual void refresh() override;
	virtual uint32_t getColor(uint16_t index) override;
	const int8_t mDirection;

private:
	uint8_t mCounter;
};

class LeftSignal: public DirectionSignal {
public:
	LeftSignal(uint8_t nbRows, uint8_t nbColumns): DirectionSignal(nbRows, nbColumns, -1) {}
};

class RightSignal: public DirectionSignal {
public:
	RightSignal(uint8_t nbRows, uint8_t nbColumns): DirectionSignal(nbRows, nbColumns, 1) {}
};

#endif