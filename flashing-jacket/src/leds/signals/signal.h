#ifndef SIGNAL_H
#define SIGNAL_H

#include <stdint.h>

class Signal {
public:
	Signal(int nbRows, int nbColumns);

	virtual void refresh() = 0;
	virtual uint32_t getColor(int index) = 0;

protected:
	int getRow(int index);
	int getColumn(int index);

	const int mNbRows;
	const int mNbColumns;

};

#endif