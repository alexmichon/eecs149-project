#ifndef IDLE_SIGNAL_H
#define IDLE_SIGNAL_H

#include "signal.h"

class IdleSignal: public Signal {
public:
	IdleSignal(int nbRows, int nbColumns);

	virtual void refresh() override;
	virtual uint32_t getColor(int index) override;
};

#endif