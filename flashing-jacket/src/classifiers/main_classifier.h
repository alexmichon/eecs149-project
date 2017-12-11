#ifndef MAIN_CLASSIFIER_H
#define MAIN_CLASSIFIER_H

class MainClassifier {
public:
	typedef enum {
		BIKE,
		MUSIC
	} State;

	MainClassifier();

	virtual State getState();

protected:
	State mCurrentState;
};

#endif