#include "src/classifier.h"
#include "src/imu.h"
#include "src/leds.h"


#define NB_LED_STRIPS 5
#define DELAY 100


typedef enum {
	BIKING,
	MUSIC
} MainState;


MainState main_state = BIKING;

MainClassifier main_classifier = MainClassifier();
BikeClassifier bike_classifier = BikeClassifier();

IMU torso_imu = IMU();
IMU left_imu = IMU();
IMU right_imu = IMU();

ImuData torso_data;
ImuData left_data;
ImuData right_data;


LedStrip led_strips[NB_LED_STRIPS];


void setup() {
	// Explanations Needed
	Serial.begin(9600);
}

void loop() {
	read_sensors();
	ControlSignal signal = main_classifier.classify(torso_data, left_data, right_data);
	update_main_state(movement);
	
	switch(main_state) {
		case BIKING:
			update_biking();
			break;
		case MUSIC:
			update_music();
			break;
	}

	update_leds();

	delay(DELAY);
}

void read_sensors() {
	torso_imu.read(&torso_data);
	left_imu.read(&left_data);
	right_imu.read(&right_data);
}

void update_main_state() {
	if (movement == SWITCH) {
		if (main_state == BIKING) {
			main_state = MUSIC;
		}
		else {
			main_state = BIKING;
		}
	}
}

void update_biking() {
	HandGesture gesture = bike_classifier.classify(torso_data, left_data, right_data);
	switch(gesture) {
		
	}
}

void update_music() {

}