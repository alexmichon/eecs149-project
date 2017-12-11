#ifndef GESTURE_CLASSIFIER_H
#define GESTURE_CLASSIFIER_H

class GestureClassifier {
public:
	typedef enum {
		IDLE,
		BRAKE,
		LEFT,
		RIGHT
	} State;

	GestureClassifier();

	virtual State getState();

protected:
	State mCurrentState;
};

#endif