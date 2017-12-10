#include "signal.h"

Signal::Signal(int nbRows, int nbColumns):
	mNbRows(nbRows),
	mNbColumns(nbColumns) {

}

int Signal::getRow(int index) {
	return index / mNbColumns;
}

int Signal::getColumn(int index) {
	return index - getRow(index) * mNbColumns;
}