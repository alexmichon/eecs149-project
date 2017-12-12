#include "gnb_classifier.h"

#include <float.h>
#include <math.h>

GnbClassifier::GnbClassifier() {
}

int GnbClassifier::predict(const float *point) {
	int cls = 0;
	float dist = -FLT_MAX;
	for (int i = 0; i < getNbClasses(); i++) {
		float new_distance = logLikelihood(i, point);
		if (new_distance > dist) {
			dist = new_distance;
			cls = i;
		}
	}

	return cls;
}

float GnbClassifier::logLikelihood(const int cls, const float *point) {
	float dist = log(getClassPrior(cls));
	for (int i = 0; i < getNbDims(); i++) {
		dist -= 0.5 * ( log(2 * M_PI * getStdev(cls, i)) );
		dist -= 0.5 * ( pow(getMean(cls, i) - point[i], 2) / getStdev(cls, i) );
	}

	return dist;
}