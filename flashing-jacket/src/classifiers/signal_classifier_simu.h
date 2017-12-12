#ifndef SIGNAL_CLASSIFIER_SIMU_H
#define SIGNAL_CLASSIFIER_SIMU_H

#include "signal_classifier.h"
#include <stdint.h>

class SignalClassifierSimu: public SignalClassifier {
public:
	SignalClassifierSimu();

	virtual State classify(float *forearmData) override;

protected:
	State nextState(State state);

	State mCurrentState;
	uint32_t mTimer;
};

#endif