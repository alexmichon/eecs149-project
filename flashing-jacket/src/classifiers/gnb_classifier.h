#ifndef GNB_CLASSIFIER_H
#define GNB_CLASSIFIER_H

#include <stdint.h>

class GnbClassifier {

public:
	GnbClassifier();

	uint8_t predict(const float *point);

protected:

	virtual uint8_t getNbClasses() = 0;
	virtual uint8_t getNbDims() = 0;

	virtual float getClassPrior(uint8_t cls) = 0;
	virtual float getMean(uint8_t cls, uint8_t dim) = 0;
	virtual float getStdev(uint8_t cls, uint8_t dim) = 0;
	
	float logLikelihood(const uint8_t cls, const float *point);

};

#endif
