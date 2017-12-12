#include "main_classifier_simu.h"
#include <Arduino.h>

MainClassifierSimu::MainClassifierSimu(): MainClassifier() {

}

MainClassifierSimu::State MainClassifierSimu::classify(float *torsoData, float *armData, float *forearmData) {
	String msg;
	if (Serial.available() > 0) { 
	    msg = Serial.readString();
	    if (msg == "bike") {
	        mCurrentState = BIKE;
	    }
	    else if (msg == "music") {
	        mCurrentState = MUSIC;
	    }
	}

	return mCurrentState;
}