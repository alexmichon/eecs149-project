#ifndef MAIN_CLASSIFIER_SIMU_H
#define MAIN_CLASSIFIER_SIMU_H

#include "main_classifier.h"

class MainClassifierSimu: public MainClassifier {
public:
	MainClassifierSimu();

	virtual State classify(float *torsoData, float *armData, float *forearmData) override;

private:
	
};

#endif