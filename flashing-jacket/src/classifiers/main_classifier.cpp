#include "main_classifier.h"
#include <string.h>

MainClassifier::MainClassifier(): GnbClassifier(), LDA() {
	mCurrentState = BIKE;
}


MainClassifier::State MainClassifier::classify(float *torsoData, float *armData, float *forearmData) {
	memcpy(&(fullPoint[0]), torsoData, 6 * sizeof(float));
	memcpy(&(fullPoint[6]), armData, 6 * sizeof(float));
	memcpy(&(fullPoint[12]), forearmData, 6 * sizeof(float));



	int cls = predict(reducedPoint);

	switch(cls) {
		case 0:
			return BIKE;
		case 1:
			return MUSIC;
	}

	return BIKE;
}


int MainClassifier::getNbClasses() {
	return MAIN_CLASSES;
}

int MainClassifier::getNbDims() {
	return MAIN_DIMENSIONS;
}

int MainClassifier::getNbFeatures() {
	return MAIN_FEATURES;
}



float MainClassifier::getClassPrior(int cls) {
	return MAIN_GNB_CLASS_PRIOR[cls];
}

float MainClassifier::getMean(int cls, int dim) {
	return MAIN_GNB_MEANS[cls][dim];
}

float MainClassifier::getStdev(int cls, int dim) {
	return MAIN_GNB_STDEVS[cls][dim];
}


float MainClassifier::getXbar(int feature) {
	return MAIN_XBAR[feature];
}

float MainClassifier::getScaling(int feature, int cls) {
	return MAIN_SCALINGS[feature][cls];
}