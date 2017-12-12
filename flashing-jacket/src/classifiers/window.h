#ifndef WINDOW_H
#define WINDOW_H

#include <stdint.h>

#define POINT_SIZE 18

class Window {

public:
	Window(uint8_t size);

	void push(float *point);
	float * get();

protected:
	uint8_t mSize;

	float *mSample;
};

#endif