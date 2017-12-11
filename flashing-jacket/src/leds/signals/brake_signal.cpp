#include "brake_signal.h"
#include <Adafruit_NeoPixel.h>


static uint32_t BRAKE_COLOR = Adafruit_NeoPixel::Color(255,0,0);

BrakeSignal::BrakeSignal(int nbRows, int nbColumns) : Signal(nbRows, nbColumns) {

}

void BrakeSignal::refresh() {
	
}

uint32_t BrakeSignal::getColor(int index) {
	return BRAKE_COLOR;
}