#ifndef CLASSIFIER_H
#define CLASSIFIER_H

typedef enum {
	UNKNOWN = -1,
	SWITCH
} MainMovement;

class MainClassifier {
public:
	MainClasifier();
	MainMovement classify(const ImuData torsoData, const ImuData leftData, const ImuData rightData);
};


typedef enum {
	UNKNOWN = -1,
	BRAKE,
	LEFT_SIGNAL,
	RIGHT_SIGNAL,
	LEFT_END,
	RIGHT_END
} BikeMovement;

class BikeClassifier {
public:
	BikeClassifier();
	BikeMovement classify(const ImuData torsoData, const ImuData leftData, const ImuData rightData);
};

#endif