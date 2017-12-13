#ifndef IDLE_SIGNAL_H
#define IDLE_SIGNAL_H

#include "signal.h"

class IdleSignal: public Signal {
public:
	IdleSignal(uint8_t nbRows, uint8_t nbColumns);

	virtual void refresh() override;
	virtual uint32_t getColor(uint16_t index) override;
};

#endif