#include "src/GaussianNB.h"
#include "src/GaussianNB_Parameters.h"

GaussianNB gnb = GaussianNB(MEANS, STDEVS);

float point[DIMENSIONS];


void setup() {
	Serial.begin(115200);
}

void loop() {
	for (uint16_t i = 0; i < DIMENSIONS; i++) {
    while(!Serial.available());
		point[i] = Serial.parseFloat();
    Serial.print("Received: ");Serial.println(point[i]);
	}

	Serial.println(gnb.predict(point));
}
