#include "signal_classifier_simu.h"
#include <Arduino.h>


#define PERIOD 3000

SignalClassifierSimu::SignalClassifierSimu(): SignalClassifier() {
	mCurrentState = IDLE;
	mTimer = millis();
}


SignalClassifier::State SignalClassifierSimu::classify(float *imuData, float *armData, float *forearmData) {
	if (millis() - mTimer > PERIOD) {
		mCurrentState = nextState(mCurrentState);
		mTimer = millis();
	}

	return mCurrentState;
}

SignalClassifier::State SignalClassifierSimu::nextState(State state) {
	switch(state) {
		case IDLE:
			return STOP;
		case STOP:
			return LEFT;
		case LEFT:
			return RIGHT;
		case RIGHT:
			return IDLE;
		default:
			return IDLE;
	}
}