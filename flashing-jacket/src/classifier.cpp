#include "classifier.h"

/* ==================================================
 * ================ MainClassifier ==================
 * ================================================== */

MainClassifier::MainClassifier() {

}

MainMovement MainClassifier::classify(const ImuData torsoData, const ImuData leftData, const ImuData rightData) {
	return UNKNOWN;
}

/* ==================================================
 * ================ BrakeDetector ===================
 * ================================================== */

BrakeDetector::BrakeDetector() {

}

BrakeDetector::detect(const ImuData torsoData, const ImuData leftData, const ImuData rightData) {
  return false;
}

/* ==================================================
 * ================ BikeClassifier ==================
 * ================================================== */

BikeClassifier::BikeClassifier() {

}

BikeMovement BikeClassifier::classify(const ImuData torsoData, const ImuData leftData, const ImuData rightData) {
	return UNKNOWN;
}