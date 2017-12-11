#include "direction_signal.h"
#include <Adafruit_NeoPixel.h>
#include "../../utils/math_utils.h"

static uint32_t DIRECTION_COLOR = Adafruit_NeoPixel::Color(255,255,0);
static uint32_t OFF_COLOR = Adafruit_NeoPixel::Color(0,0,0);

DirectionSignal::DirectionSignal(int nbRows, int nbColumns, int direction): Signal(nbRows, nbColumns), mDirection(direction) {
	mCounter = 0;
}

void DirectionSignal::refresh() {
	mCounter = mod(mCounter + mDirection, mNbRows);
}

uint32_t DirectionSignal::getColor(int index) {
	int row = getRow(index);
	int column = getColumn(index);

	row = mod(row - mCounter, mNbRows);

	if (mDirection * (column + row - ((mNbRows + mNbColumns) / 2) + 1) > 0) {
		return OFF_COLOR;
	}

	if (mDirection * (column - row) < 0) {
		return OFF_COLOR;
	}

	return DIRECTION_COLOR;
}