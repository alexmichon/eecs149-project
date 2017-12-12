#include "mode_classifier.h"

ModeClassifier::ModeClassifier(): GnbClassifier(), LDA() {

}


ModeClassifier::Signal ModeClassifier::classify(float *torsoData, float *armData, float *forearmData) {
	return NONE;
}


uint8_t ModeClassifier::getNbClasses() {
	return 0;
}

uint8_t ModeClassifier::getNbDims() {
	return 0;
}

uint8_t ModeClassifier::getNbFeatures() {
	return 0;
}



float ModeClassifier::getClassPrior(uint8_t cls) {
	return 0;
}

float ModeClassifier::getMean(uint8_t cls, uint8_t dim) {
	return 0;
}

float ModeClassifier::getStdev(uint8_t cls, uint8_t dim) {
	return 0;
}


float ModeClassifier::getXbar(uint8_t feature) {
	return 0;
}

float ModeClassifier::getScaling(uint8_t feature, uint8_t cls) {
	return 0;
}