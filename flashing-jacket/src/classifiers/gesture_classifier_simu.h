#ifndef GESTURE_CLASSIFIER_SIMU_H
#define GESTURE_CLASSIFIER_SIMU_H

#include "gesture_classifier.h"

class GestureClassifierSimu: public GestureClassifier {
public:
	GestureClassifierSimu();

	virtual bool classify(float *forearmData) override;
};

#endif