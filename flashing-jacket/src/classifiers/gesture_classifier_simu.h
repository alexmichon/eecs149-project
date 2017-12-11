#ifndef GESTURE_CLASSIFIER_SIMU_H
#define GESTURE_CLASSIFIER_SIMU_H

#include "gesture_classifier.h"
#include <stdint.h>

class GestureClassifierSimu: public GestureClassifier {
public:
	GestureClassifierSimu();

	virtual State getState();

protected:
	State nextState(State state);

	uint32_t mTimer;
};

#endif