#ifndef LEFT_SIGNAL_H
#define LEFT_SIGNAL_H

#include "signal.h"

class LeftSignal: public Signal {
public:
	LeftSignal(int nbRows, int nbColumns);

	virtual void refresh();
	virtual uint32_t getColor(int index) override;

private:
	int mCounter;
};

#endif