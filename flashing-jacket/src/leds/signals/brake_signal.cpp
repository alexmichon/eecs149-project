#include "brake_signal.h"
#include <Adafruit_NeoPixel.h>


uint32_t BRAKE_COLOR = Adafruit_NeoPixel::Color(255,0,0);

BrakeSignal::BrakeSignal(int nbRows, int nbColumns) : Signal(nbRows, nbColumns) {

}

uint32_t BrakeSignal::getColor(int index) {
	return BRAKE_COLOR;
}

void BrakeSignal::refresh() {
	
}