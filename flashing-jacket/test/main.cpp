#include "GaussianNB.h"
#include "LDA.h"
#include "test_points.h"

#include <stdio.h>

int main() {
	int score = 0;

	for (int i = 0; i < NB_TEST_POINTS; i++) {
		const float* point = TEST_POINTS[i];
		int prediction = TEST_PREDICTIONS[i];
		
		float transformed[LDA_DIMENSIONS] = {0};
		lda.transform(point, transformed);

		int cls = gnb.predict(transformed);
		
		if (cls == prediction) {
			score++;
		}
		else {
			printf("Error %d: expected %d,  actual %d\n", i, prediction, cls);
		}
	}

	printf("Score: %d/%d\n", score, NB_TEST_POINTS);

    return 0;
}
