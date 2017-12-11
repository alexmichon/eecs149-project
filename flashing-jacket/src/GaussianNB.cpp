#include "GaussianNB.h"
#include <float.h>
#include <math.h>
#include <stdio.h>

GaussianNB gnb = GaussianNB(GNB_CLASS_PRIOR, GNB_MEANS, GNB_STDEVS);

GaussianNB::GaussianNB(const float class_prior[LDA_CLASSES], const float means[LDA_CLASSES][LDA_DIMENSIONS], const float stdevs[LDA_CLASSES][LDA_DIMENSIONS]) {
	for (int i = 0; i < LDA_CLASSES; i++) {
		m_class_prior[i] = class_prior[i];
		for (int j = 0; j < LDA_DIMENSIONS; j++) {
			m_means[i][j] = means[i][j];
			m_stdevs[i][j] = stdevs[i][j];
		}
	}
}

int GaussianNB::predict(const float *point) {
	int cls = 0;
	float dist = -FLT_MAX;
	for (int i = 0; i < LDA_CLASSES; i++) {
		float new_distance = log_likelihood(i, point);
		if (new_distance > dist) {
			dist = new_distance;
			cls = i;
		}
	}

	return cls;
}

float GaussianNB::log_likelihood(const int cls, const float *point) {
	float dist = log(m_class_prior[cls]);
	for (int i = 0; i < LDA_DIMENSIONS; i++) {
		dist -= 0.5 * ( log(2 * M_PI * m_stdevs[cls][i]) );
		dist -= 0.5 * ( pow(m_means[cls][i] - point[i], 2) / m_stdevs[cls][i] );
	}

	return dist;
}