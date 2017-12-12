#ifndef SIGNAL_H
#define SIGNAL_H

#include <stdint.h>

class Signal {
public:
	Signal(uint8_t nbRows, uint8_t nbColumns);

	virtual void refresh() = 0;
	virtual uint32_t getColor(uint16_t index) = 0;

	const uint8_t mNbRows;
	const uint8_t mNbColumns;

protected:
	uint8_t getRow(uint16_t index);
	uint8_t getColumn(uint16_t index);

};

#endif