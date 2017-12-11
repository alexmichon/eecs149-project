#ifndef GAUSSIAN_NB_H
#define GAUSSIAN_NB_H

#include "GaussianNB_Parameters.h"

class GaussianNB {

public:
	GaussianNB(const float class_prior[LDA_CLASSES], const float means[LDA_CLASSES][LDA_DIMENSIONS], const float stdevs[LDA_CLASSES][LDA_DIMENSIONS] );

	int predict(const float *point);

private:

	float log_likelihood(const int cls, const float *point);

	float m_class_prior[LDA_CLASSES];
	float m_means[LDA_CLASSES][LDA_DIMENSIONS];
	float m_stdevs[LDA_CLASSES][LDA_DIMENSIONS];

};

extern GaussianNB gnb;

#endif
