#include "lda.h"

LDA::LDA() {
}


void LDA::transform(const float *point, float *transformed) {
	for (int i = 0; i < getNbDims(); i++) {
		transformed[i] = 0;
		for (int j = 0; j < getNbFeatures(); j++) {
			transformed[i] += (point[j] - getXbar(j)) * getScaling(j, i);
		}
	}
}