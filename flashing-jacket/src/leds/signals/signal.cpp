#include "signal.h"

Signal::Signal(uint8_t nbRows, uint8_t nbColumns):
	mNbRows(nbRows),
	mNbColumns(nbColumns) {

}

uint8_t Signal::getRow(uint16_t index) {
	return index / mNbColumns;
}

uint8_t Signal::getColumn(uint16_t index) {
	return index - getRow(index) * mNbColumns;
}