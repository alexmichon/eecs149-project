#ifndef MODE_CLASSIFIER_H
#define MODE_CLASSIFIER_H

#include "gnb_classifier.h"
#include "lda.h"

class ModeClassifier: GnbClassifier, LDA {
public:

	typedef enum {
		BIKE,
		MUSIC
	} State;

	ModeClassifier();

	virtual State classify(float *torsoData, float *armData, float *forearmData);

protected:

	virtual uint8_t getNbClasses() override;
	virtual uint8_t getNbDims() override;
	virtual uint8_t getNbFeatures() override;

	virtual float getClassPrior(uint8_t cls) override;
	virtual float getMean(uint8_t cls, uint8_t dim) override;
	virtual float getStdev(uint8_t cls, uint8_t dim) override;

	virtual float getXbar(uint8_t feature) override;
	virtual float getScaling(uint8_t feature, uint8_t cls) override;

};

#endif