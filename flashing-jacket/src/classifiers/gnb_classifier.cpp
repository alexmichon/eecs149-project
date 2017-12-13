#include "gnb_classifier.h"

#include <float.h>
#include <math.h>

GnbClassifier::GnbClassifier() {
}

uint8_t GnbClassifier::predict(const float *point) {
	uint8_t cls = 0;
	float dist = -FLT_MAX;
	for (uint8_t i = 0; i < getNbClasses(); i++) {
		float new_distance = logLikelihood(i, point);
		if (new_distance > dist) {
			dist = new_distance;
			cls = i;
		}
	}

	return cls;
}

float GnbClassifier::logLikelihood(const uint8_t cls, const float *point) {
	float dist = log(getClassPrior(cls));
	for (uint8_t i = 0; i < getNbDims(); i++) {
		dist -= 0.5 * ( log(2 * M_PI * getStdev(cls, i)) );
		dist -= 0.5 * ( pow(getMean(cls, i) - point[i], 2) / getStdev(cls, i) );
	}

	return dist;
}