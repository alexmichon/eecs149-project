#include "window.h"
#include <string.h>
#include <stdlib.h>
#include <Arduino.h>

Window::Window(uint8_t size) {
	mSize = size;

	mSample = (float *) malloc(mSize * POINT_SIZE * sizeof(float));
}

void Window::push(float *point) {
	for (uint8_t i = 0; i < mSize - 1; i++) {
		memcpy(&(mSample[i * POINT_SIZE]), &(mSample[(i+1) * POINT_SIZE]), POINT_SIZE * sizeof(float));
	}

	memcpy(&(mSample[(mSize - 1) * POINT_SIZE]), point, POINT_SIZE * sizeof(float));
}

float * Window::get() {
	return mSample;
}