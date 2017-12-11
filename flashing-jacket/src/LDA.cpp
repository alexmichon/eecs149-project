#include "LDA.h"

LDA lda = LDA(LDA_XBAR, LDA_SCALINGS);

LDA::LDA(const float xbar[LDA_FEATURES], const float scalings[LDA_FEATURES][LDA_DIMENSIONS]) {
	for (int i = 0; i < LDA_FEATURES; i++) {
		m_xbar[i] = xbar[i];
		for (int j = 0; j < LDA_DIMENSIONS; j++) {
			m_scalings[i][j] = scalings[i][j];
		}
	}
}


void LDA::transform(const float point[LDA_FEATURES], float *transformed) {
	for (int i = 0; i < LDA_DIMENSIONS; i++) {
		transformed[i] = 0;
		for (int j = 0; j < LDA_FEATURES; j++) {
			transformed[i] += (point[j] - m_xbar[j]) * m_scalings[j][i];
		}
	}
}