#ifndef GESTURE_CLASSIFIER_H
#define GESTURE_CLASSIFIER_H

#include "gesture_parameters.h"
#include "gnb_classifier.h"
#include "lda.h"
#include "window.h"

class GestureClassifier: public GnbClassifier, public LDA {
public:

	GestureClassifier();

	virtual bool classify(float *forearmData);

protected:

	virtual uint8_t getNbClasses() override;
	virtual uint8_t getNbDims() override;
	virtual uint8_t getNbFeatures() override;

	virtual float getClassPrior(uint8_t cls) override;
	virtual float getMean(uint8_t cls, uint8_t dim) override;
	virtual float getStdev(uint8_t cls, uint8_t dim) override;

	virtual float getXbar(uint8_t feature) override;
	virtual float getScaling(uint8_t feature, uint8_t cls) override;

	float newPoint[18];
	float reducedPoint[GESTURE_DIMENSIONS];

	Window mWindow;
};

#endif