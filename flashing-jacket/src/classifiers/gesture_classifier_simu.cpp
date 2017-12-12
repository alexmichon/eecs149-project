#include "gesture_classifier_simu.h"
#include <Arduino.h>


#define PERIOD 3000

GestureClassifierSimu::GestureClassifierSimu(): GestureClassifier() {
}


bool GestureClassifierSimu::getState() {
	return true;
}