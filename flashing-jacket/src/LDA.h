#ifndef LDA_H
#define LDA_H

#include "LDA_Parameters.h"

class LDA {

public:
	LDA(const float xbar[LDA_FEATURES], const float scalings[LDA_FEATURES][LDA_DIMENSIONS]);

	void transform(const float *point, float *transformed);

private:

	float m_xbar[LDA_FEATURES];
	float m_scalings[LDA_FEATURES][LDA_DIMENSIONS];

};

extern LDA lda;

#endif
