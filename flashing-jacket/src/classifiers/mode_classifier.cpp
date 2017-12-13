#include "mode_classifier.h"
#include <string.h>

ModeClassifier::ModeClassifier(): GnbClassifier(), LDA(),
	mWindow(Window(MODE_WINDOW))
{
}


bool ModeClassifier::classify(float *forearmData) {
	// memcpy(&(newPoint[0]), torsoData, 6 * sizeof(float));
	// memcpy(&(newPoint[6]), armData, 6 * sizeof(float));
	// memcpy(&(newPoint[12]), forearmData, 6 * sizeof(float));

	mWindow.push(forearmData);
	transform(mWindow.get(), reducedPoint);

	uint8_t cls = predict(reducedPoint);

	return (cls == 0);
}


uint8_t ModeClassifier::getNbClasses() {
	return MODE_CLASSES;
}

uint8_t ModeClassifier::getNbDims() {
	return MODE_DIMENSIONS;
}

uint8_t ModeClassifier::getNbFeatures() {
	return MODE_FEATURES;
}



float ModeClassifier::getClassPrior(uint8_t cls) {
	return MODE_GNB_CLASS_PRIOR[cls];
}

float ModeClassifier::getMean(uint8_t cls, uint8_t dim) {
	return MODE_GNB_MEANS[cls][dim];
}

float ModeClassifier::getStdev(uint8_t cls, uint8_t dim) {
	return MODE_GNB_STDEVS[cls][dim];
}


float ModeClassifier::getXbar(uint8_t feature) {
	return MODE_XBAR[feature];
}

float ModeClassifier::getScaling(uint8_t feature, uint8_t cls) {
	return MODE_SCALINGS[feature][cls];
}