#include "gesture_classifier.h"
#include <string.h>

GestureClassifier::GestureClassifier(): GnbClassifier(), LDA(),
	mWindow(Window(GESTURE_WINDOW))
{
}


bool GestureClassifier::classify(float *forearmData) {
	// memcpy(&(newPoint[0]), torsoData, 6 * sizeof(float));
	// memcpy(&(newPoint[6]), armData, 6 * sizeof(float));
	// memcpy(&(newPoint[12]), forearmData, 6 * sizeof(float));

	mWindow.push(forearmData);
	transform(mWindow.get(), reducedPoint);

	uint8_t cls = predict(reducedPoint);

	return (cls == 0);
}


uint8_t GestureClassifier::getNbClasses() {
	return GESTURE_CLASSES;
}

uint8_t GestureClassifier::getNbDims() {
	return GESTURE_DIMENSIONS;
}

uint8_t GestureClassifier::getNbFeatures() {
	return GESTURE_FEATURES;
}



float GestureClassifier::getClassPrior(uint8_t cls) {
	return GESTURE_GNB_CLASS_PRIOR[cls];
}

float GestureClassifier::getMean(uint8_t cls, uint8_t dim) {
	return GESTURE_GNB_MEANS[cls][dim];
}

float GestureClassifier::getStdev(uint8_t cls, uint8_t dim) {
	return GESTURE_GNB_STDEVS[cls][dim];
}


float GestureClassifier::getXbar(uint8_t feature) {
	return GESTURE_XBAR[feature];
}

float GestureClassifier::getScaling(uint8_t feature, uint8_t cls) {
	return GESTURE_SCALINGS[feature][cls];
}