#include "src/classifiers/main_classifier.h"
#include "src/classifiers/gesture_classifier.h"

#include "src/leds/led_strip.h"
#include "src/leds/led_grid.h"

#include "src/leds/signals/brake_signal.h"
#include "src/leds/signals/idle_signal.h"
#include "src/leds/signals/direction_signal.h"
#include "src/leds/signals/music_signal.h"

#include "src/sensors/imu.h"
#include "src/sensors/microphone.h"


// SIMULATION
#define SIMULATION





// PINS
#define PIN_STRIP1 9
#define PIN_STRIP2 10

#define LSM9DS1_SCK 24
#define LSM9DS1_MISO 22
#define LSM9DS1_MOSI 23

#define LSM9DS1_XGCS1 5 // CHIP SELECT IMU 1
#define LSM9DS1_XGCS2 6 // CHIP SELECT IMU 2
#define LSM9DS1_XGCS3 10 // CHIP SELECT IMU 2







// LEDS

// Grid
#define NB_STRIPS 10
#define NB_LEDS 10


#ifndef SIMULATION

// Leds per strips
#define NUMPIXELS1      20
#define NUMPIXELS2      77

LedStrip ledStrip1(NUMPIXELS1, 0, PIN_STRIP1);
LedStrip ledStrip2(NUMPIXELS2, NUMPIXELS1, PIN_STRIP2);
LedStrip *ledStrips[2] = {&ledStrip1, &ledStrip2};

LedGrid ledGrid(ledStrips, 2);

#else

#include "src/leds/led_strip_simu.h"

LedStripSimu ledStrip1(NB_LEDS, 0 * NB_LEDS, 0);
LedStripSimu ledStrip2(NB_LEDS, 1 * NB_LEDS, 0);
LedStripSimu ledStrip3(NB_LEDS, 2 * NB_LEDS, 0);
LedStripSimu ledStrip4(NB_LEDS, 3 * NB_LEDS, 0);
LedStripSimu ledStrip5(NB_LEDS, 4 * NB_LEDS, 0);
LedStripSimu ledStrip6(NB_LEDS, 5 * NB_LEDS, 0);
LedStripSimu ledStrip7(NB_LEDS, 6 * NB_LEDS, 0);
LedStripSimu ledStrip8(NB_LEDS, 7 * NB_LEDS, 0);
LedStripSimu ledStrip9(NB_LEDS, 8 * NB_LEDS, 0);
LedStripSimu ledStrip10(NB_LEDS, 9 * NB_LEDS, 0);

LedStrip *ledStrips[NB_STRIPS] = {
  &ledStrip1, 
  &ledStrip2, 
  &ledStrip3,
  &ledStrip4,
  &ledStrip5,
  &ledStrip6,
  &ledStrip7,
  &ledStrip8,
  &ledStrip9,
  &ledStrip10,
};

LedGrid ledGrid(ledStrips, NB_STRIPS);

#endif






// IMU


IMU torsoImu(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS1);
IMU armImu(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS2);
IMU forearmImu(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS3);

IMU::Data torsoData;
IMU::Data armData;
IMU::Data forearmData;


// MICROPHONE

// sample rate for the input
#define SAMPLE_RATE 2000

// size of the FFT to compute
#define FFT_SIZE 128

// create an FFT analyzer to be used with the I2S input
FFTAnalyzer fftAnalyzer(FFT_SIZE);

Microphone microphone(FFT_SIZE, NB_STRIPS, NB_LEDS);





// SIGNALS
IdleSignal idleSignal(NB_STRIPS, NB_LEDS);
BrakeSignal brakeSignal(NB_STRIPS, NB_LEDS);
LeftSignal leftSignal(NB_STRIPS, NB_LEDS);
RightSignal rightSignal(NB_STRIPS, NB_LEDS);

MusicSignal musicSignal(NB_STRIPS, NB_LEDS, &microphone);







// CLASSIFIERS


#ifndef SIMULATION

MainClassifier mainClassifier;
GestureClassifier gestureClassifier;

#else

#include "src/classifiers/main_classifier_simu.h"
MainClassifierSimu mainClassifier;

#include "src/classifiers/gesture_classifier_simu.h"
GestureClassifierSimu gestureClassifier;

#endif


MainClassifier::State state = MainClassifier::State::MUSIC;
GestureClassifier::State bikeState = GestureClassifier::State::IDLE;




void setup() {
// Open serial communications and wait for port to open:
  // A baud rate of 115200 is used instead of 9600 for a faster data rate
  // on non-native USB ports
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  ledGrid.begin();
  microphone.begin(SAMPLE_RATE);
}



void updateState() {
  state = mainClassifier.getState();
}



void updateBike() {
  bikeState = gestureClassifier.getState();

  switch(bikeState) {
    case GestureClassifier::State::IDLE:
      ledGrid.setSignal(&idleSignal);
      break;
    case GestureClassifier::State::BRAKE:
      ledGrid.setSignal(&brakeSignal);
      break;
    case GestureClassifier::State::LEFT:
      ledGrid.setSignal(&leftSignal);
      break;
    case GestureClassifier::State::RIGHT:
      ledGrid.setSignal(&rightSignal);
      break;
  }
}

void updateMusic() {
  ledGrid.setSignal(&musicSignal);
}


void loop() {
  updateState();

  switch(state) {
    case MainClassifier::State::BIKE:
      updateBike();
      break;
    case MainClassifier::State::MUSIC:
      updateMusic();
      break;
  }

  ledGrid.refresh();

  delay(50);
}