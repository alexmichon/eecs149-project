#include "brake_signal.h"
#include <Adafruit_NeoPixel.h>


static uint32_t BRAKE_COLOR = Adafruit_NeoPixel::Color(255,0,0);

BrakeSignal::BrakeSignal(uint8_t nbRows, uint8_t nbColumns) : Signal(nbRows, nbColumns) {

}

void BrakeSignal::refresh() {
	
}

uint32_t BrakeSignal::getColor(uint16_t index) {
	return BRAKE_COLOR;
}