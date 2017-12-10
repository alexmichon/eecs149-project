#ifndef BRAKE_SIGNAL_H
#define BRAKE_SIGNAL_H

#include "signal.h"

class BrakeSignal: public Signal {
public:
	BrakeSignal(int nbRow, int nbColumns);

	virtual void refresh() override;
	virtual uint32_t getColor(int index) override;

};

#endif