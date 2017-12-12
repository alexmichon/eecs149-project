#ifndef LDA_H
#define LDA_H

class LDA {

public:
	LDA();

	void transform(const float *point, float *transformed);

protected:

	virtual int getNbDims() = 0;
	virtual int getNbFeatures() = 0;

	virtual float getXbar(int feature) = 0;
	virtual float getScaling(int feature, int cls) = 0;

};

#endif
