#include "src/classifier.h"
#include "src/imu.h"
#include "src/leds.h"


#define NB_LED_STRIPS 5
#define DELAY 100


typedef enum {
	BIKING,
	MUSIC
} MainState;

typedef enum {
	IDLE,
	BRAKE,
	BRAKE_LEFT,
	BRAKE_RIGHT,
	LEFT,
	RIGHT,
	STOP
} LedSignal;

MainState main_state = BIKING;
LedSignal next_signal = IDLE;

MainClassifier main_classifier = MainClassifier();
BrakeDetector brake_detector = BrakeDetector();
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
	bool is_brake = brake_detector.detect(torso_data, left_data, right_data);
	HandGesture gesture = bike_classifier.classify(torso_data, left_data, right_data);

	//TODO Iter-0: Refactoring of this switch statement if working
	if(is_brake) {
		switch (gesture) {
		    case UNKNOWN:
		      next_signal = BRAKE;
		      break;
		    case LEFT_GEST:
		      next_signal = BRAKE_LEFT;
		      break;
		    case RIGHT_GEST:
		    	next_signal = BRAKE_RIGHT;
		    	break;
		    case STOP_GEST:
		    	next_signal = STOP;
		    	break;
		    default:
		      break;
		}
	} else {
		switch (gesture) {
		    case LEFT_GEST:
		      next_signal = LEFT;
		      break;
		    case RIGHT_GEST:
		    	next_signal = RIGHT;
		    	break;
		    case STOP_GEST:
		    	next_signal = STOP;
		    	break;
		    default:
		    	next_signal = IDEL;
		      break;
		}
	}
}

void update_music() {

}

void update_leds() {

}