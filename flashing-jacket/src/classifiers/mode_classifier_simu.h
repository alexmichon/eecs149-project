#ifndef MODE_CLASSIFIER_SIMU_H
#define MODE_CLASSIFIER_SIMU_H

#include "mode_classifier.h"

class ModeClassifierSimu: public ModeClassifier {
public:
	ModeClassifierSimu();

	virtual bool classify(float *forearmData) override;
};

#endif