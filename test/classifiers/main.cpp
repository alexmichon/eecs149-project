#include "main_classifier.h"
#include "test_points.h"

#include <stdio.h>

int main() {
	int score = 0;

	MainClassifier mainClassifier = MainClassifier();

	for (int i = 0; i < NB_TEST_POINTS; i++) {
		const float* point = TEST_POINTS[i];
		int prediction = TEST_PREDICTIONS[i];

		int cls = mainClassifier.predict(point);
		
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
