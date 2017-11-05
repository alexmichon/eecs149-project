#include "classifier.h"

MainClassifier::MainClassifier() {

}

MainMovement MainClassifier::classify(const ImuData torsoData, const ImuData leftData, const ImuData rightData) {
	return UNKNOWN;
}




BikeClassifier::BikeClassifier() {

}

BikeMovement BikeClassifier::classify(const ImuData torsoData, const ImuData leftData, const ImuData rightData) {
	return UNKNOWN;
}