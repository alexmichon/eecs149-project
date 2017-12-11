#include "gesture_classifier_simu.h"
#include <Arduino.h>


#define PERIOD 3000

GestureClassifierSimu::GestureClassifierSimu(): GestureClassifier() {
	mTimer = millis();
}


GestureClassifier::State GestureClassifierSimu::getState() {
	if (millis() - mTimer > PERIOD) {
		mCurrentState = nextState(mCurrentState);
		mTimer = millis();
	}

	return mCurrentState;
}

GestureClassifier::State GestureClassifierSimu::nextState(State state) {
	switch(state) {
		case IDLE:
			return BRAKE;
		case BRAKE:
			return LEFT;
		case LEFT:
			return RIGHT;
		case RIGHT:
			return IDLE;
		default:
			return IDLE;
	}
}