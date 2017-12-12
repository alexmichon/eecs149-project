#ifndef MAIN_CLASSIFIER_H
#define MAIN_CLASSIFIER_H

#include "main_parameters.h"
#include "gnb_classifier.h"
#include "lda.h"

class MainClassifier: public GnbClassifier, public LDA {
public:
	typedef enum {
		BIKE,
		MUSIC
	} State;

	MainClassifier();

	virtual State classify(float *imuData, float *armData, float *forearmData);

protected:

	virtual int getNbClasses() override;
	virtual int getNbDims() override;
	virtual int getNbFeatures() override;

	virtual float getClassPrior(int cls) override;
	virtual float getMean(int cls, int dim) override;
	virtual float getStdev(int cls, int dim) override;

	virtual float getXbar(int feature) override;
	virtual float getScaling(int feature, int cls) override;

	State mCurrentState;
	float fullPoint[18];
	float reducedPoint[MAIN_DIMENSIONS];
};

#endif