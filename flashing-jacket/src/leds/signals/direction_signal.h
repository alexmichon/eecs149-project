#ifndef DIRECTION_SIGNAL_H
#define DIRECTION_SIGNAL_H

#include "signal.h"

class DirectionSignal: public Signal {
public:
	DirectionSignal(int nbRows, int nbColumns, int direction);

	virtual void refresh() override;
	virtual uint32_t getColor(int index) override;

private:
	const int mDirection;
	int mCounter;
};

class LeftSignal: public DirectionSignal {
public:
	LeftSignal(int nbRows, int nbColumns): DirectionSignal(nbRows, nbColumns, 1) {}
};

class RightSignal: public DirectionSignal {
public:
	RightSignal(int nbRows, int nbColumns): DirectionSignal(nbRows, nbColumns, -1) {}
};

#endif