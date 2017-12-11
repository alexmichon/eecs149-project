#include "gesture_classifier.h"

GestureClassifier::GestureClassifier() {
	mCurrentState = IDLE;
}

GestureClassifier::State GestureClassifier::getState() {
	return GestureClassifier::State::IDLE;
}