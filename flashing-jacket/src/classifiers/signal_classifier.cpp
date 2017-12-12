#include "signal_classifier.h"
#include <string.h>

SignalClassifier::SignalClassifier(): GnbClassifier(), LDA(),
	mWindow(Window(SIGNAL_WINDOW))
{
}


SignalClassifier::State SignalClassifier::classify(float *torsoData, float *armData, float *forearmData) {
	memcpy(&(newPoint[0]), torsoData, 6 * sizeof(float));
	memcpy(&(newPoint[6]), armData, 6 * sizeof(float));
	memcpy(&(newPoint[12]), forearmData, 6 * sizeof(float));

	mWindow.push(newPoint);
	transform(mWindow.get(), reducedPoint);

	uint8_t cls = predict(reducedPoint);

	switch(cls) {
		case 0:
			return LEFT;
		case 1:
			return RIGHT;
		case 2:
			return STOP;
	}

	return IDLE;
}


uint8_t SignalClassifier::getNbClasses() {
	return SIGNAL_CLASSES;
}

uint8_t SignalClassifier::getNbDims() {
	return SIGNAL_DIMENSIONS;
}

uint8_t SignalClassifier::getNbFeatures() {
	return SIGNAL_FEATURES;
}



float SignalClassifier::getClassPrior(uint8_t cls) {
	return SIGNAL_GNB_CLASS_PRIOR[cls];
}

float SignalClassifier::getMean(uint8_t cls, uint8_t dim) {
	return SIGNAL_GNB_MEANS[cls][dim];
}

float SignalClassifier::getStdev(uint8_t cls, uint8_t dim) {
	return SIGNAL_GNB_STDEVS[cls][dim];
}


float SignalClassifier::getXbar(uint8_t feature) {
	return SIGNAL_XBAR[feature];
}

float SignalClassifier::getScaling(uint8_t feature, uint8_t cls) {
	return SIGNAL_SCALINGS[feature][cls];
}