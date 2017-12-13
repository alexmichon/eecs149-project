#ifndef LDA_H
#define LDA_H

#include <stdint.h>

class LDA {

public:
	LDA();

	void transform(const float *point, float *transformed);

protected:

	virtual uint8_t getNbDims() = 0;
	virtual uint8_t getNbFeatures() = 0;

	virtual float getXbar(uint8_t feature) = 0;
	virtual float getScaling(uint8_t feature, uint8_t cls) = 0;

};

#endif
