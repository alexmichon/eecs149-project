#ifndef CLASSIFIER_H
#define CLASSIFIER_H

typedef enum {
	UNKNOWN = -1,
	SWITCH,
} ControlSignal;

class MainClassifier {
public:
	MainClasifier();
	ControlSignal classify(const ImuData torsoData, const ImuData leftData, const ImuData rightData);
};

class BrakeDetector {
public:
	BrakeDetector();
	bool detect(const ImuData torsoData, const ImuData leftData, const ImuData rightData);
}

typedef enum {
	UNKNOWN = -1,
	LEFT_GEST,
	RIGHT_GEST,
	STOP_GEST
} HandGesture;

class BikeClassifier {
public:
	BikeClassifier();
	HandGesture classify(const ImuData torsoData, const ImuData leftData, const ImuData rightData);
};

#endif