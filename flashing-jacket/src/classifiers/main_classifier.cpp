#include "main_classifier.h"

MainClassifier::MainClassifier() {
	mCurrentState = BIKE;
}


MainClassifier::State MainClassifier::getState() {
	return mCurrentState;
}

