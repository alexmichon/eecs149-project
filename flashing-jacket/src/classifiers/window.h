#ifndef WINDOW_H
#define WINDOW_H

#include <stdint.h>

#define POINT_SIZE 6

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