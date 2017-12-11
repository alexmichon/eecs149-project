#include "idle_signal.h"
#include <Adafruit_NeoPixel.h>


static uint32_t IDLE_COLOR = Adafruit_NeoPixel::Color(0,255,0);

IdleSignal::IdleSignal(int nbRows, int nbColumns): Signal(nbRows, nbColumns) {

}

void IdleSignal::refresh() {
}


uint32_t IdleSignal::getColor(int index) {
	return IDLE_COLOR;
}
