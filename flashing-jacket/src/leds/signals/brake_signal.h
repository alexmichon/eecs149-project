#ifndef BRAKE_SIGNAL_H
#define BRAKE_SIGNAL_H

#include "signal.h"

class BrakeSignal: public Signal {
public:
	BrakeSignal(uint8_t nbRow, uint8_t nbColumns);

	virtual void refresh() override;
	virtual uint32_t getColor(uint16_t index) override;

};

#endif