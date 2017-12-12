#ifndef GNB_CLASSIFIER_H
#define GNB_CLASSIFIER_H

#include <float.h>
#include <math.h>

class GnbClassifier {

public:
	GnbClassifier();

	int predict(const float *point);

protected:

	virtual int getNbClasses() = 0;
	virtual int getNbDims() = 0;

	virtual float getClassPrior(int cls) = 0;
	virtual float getMean(int cls, int dim) = 0;
	virtual float getStdev(int cls, int dim) = 0;
	
	float logLikelihood(const int cls, const float *point);

};

#endif
