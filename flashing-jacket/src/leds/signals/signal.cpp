#include "signal.h"

Signal::Signal(uint8_t nbRows, uint8_t nbColumns):
	mNbRows(nbRows),
	mNbColumns(nbColumns) {

}

uint8_t Signal::getRow(uint16_t index) {
	return index / mNbColumns;
}

uint8_t Signal::getColumn(uint16_t index) {
	uint8_t row = getRow(index);
	uint8_t column = index - getRow(index) * mNbColumns;
	if ((row % 2) == 0) {
		column = mNbColumns - column -1;
	}
	return column;
}