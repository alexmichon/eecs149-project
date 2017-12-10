#include "left_signal.h"
#include <Adafruit_NeoPixel.h>
#include "../../utils/math_utils.h"

uint32_t LEFT_COLOR = Adafruit_NeoPixel::Color(255,255,0);
uint32_t OFF_COLOR = Adafruit_NeoPixel::Color(0,0,0);

LeftSignal::LeftSignal(int nbRows, int nbColumns): Signal(nbRows, nbColumns) {
	mCounter = 0;
}

void LeftSignal::refresh() {
	mCounter++;
}

uint32_t LeftSignal::getColor(int index) {
	int row = getRow(index);
	int column = getColumn(index);

	if (mod(column, mNbColumns) < mNbColumns / 2) {
		return OFF_COLOR;
	}

	if (row + column > (mNbRows + mNbColumns) / 2) {
		return OFF_COLOR;
	}
}