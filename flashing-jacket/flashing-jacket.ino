#include "src/classifiers/mode_classifier.h"
#include "src/classifiers/gesture_classifier.h"
#include "src/classifiers/signal_classifier.h"

#include "src/leds/led_strip.h"
#include "src/leds/led_grid.h"

#include "src/leds/signals/brake_signal.h"
#include "src/leds/signals/idle_signal.h"
#include "src/leds/signals/direction_signal.h"
#include "src/leds/signals/music_signal.h"

#include "src/sensors/imu.h"
#include "src/sensors/microphone.h"



#define DELAY 50





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

#define SIMULATION_LED



// Grid
#define NB_STRIPS 10
#define NB_LEDS 10


#ifndef SIMULATION_LED

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

#define SIMULATION_IMU

#ifndef SIMULATION_IMU

IMU torsoImu(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS1);
IMU armImu(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS2);
IMU forearmImu(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS3);

#else

#include "src/sensors/imu_simu.h"

IMUSimu torsoImu(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS1);
IMUSimu armImu(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS2);
IMUSimu forearmImu(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS3);

#endif

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

//#define SIMULATION_CLASSIFIERS


#ifndef SIMULATION_CLASSIFIERS

ModeClassifier modeClassifier;
SignalClassifier signalClassifier;
GestureClassifier gestureClassifier;

#else

#include "src/classifiers/mode_classifier_simu.h"
ModeClassifierSimu modeClassifier;

#include "src/classifiers/signal_classifier_simu.h"
SignalClassifierSimu signalClassifier;

#include "src/classifiers/gesture_classifier_simu.h"
GestureClassifierSimu gestureClassifier;

#endif


ModeClassifier::State mode = ModeClassifier::State::MUSIC;
bool gesture = false;
SignalClassifier::State bikeState = SignalClassifier::State::IDLE;




void setup() {
// Open serial communications and wait for port to open:
  // A baud rate of 115200 is used instead of 9600 for a faster data rate
  // on non-native USB ports
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  torsoImu.begin();
  delay(10);
  armImu.begin();
  delay(10);
  forearmImu.begin();

  //microphone.begin(SAMPLE_RATE);
  ledGrid.begin();
  ledGrid.setSignal(&idleSignal);
}



void sense() {
  torsoImu.read(&torsoData);
  armImu.read(&armData);
  forearmImu.read(&forearmData);
}


void analyze() {
  mode = modeClassifier.classify(torsoData, armData, forearmData);

  switch(mode) {
    case ModeClassifier::State::BIKE:
      updateBike();
      break;
    case ModeClassifier::State::MUSIC:
      updateMusic();
      break;
  }
}



void updateBike() {
  gesture = gestureClassifier.classify(torsoData, armData, forearmData);
  if (gesture) {
    bikeState = signalClassifier.classify(torsoData, armData, forearmData);
  }
  else {
    bikeState = SignalClassifier::State::IDLE;
  }

  switch(bikeState) {
    case SignalClassifier::State::IDLE:
      ledGrid.setSignal(&idleSignal);
      break;
    case SignalClassifier::State::STOP:
      ledGrid.setSignal(&brakeSignal);
      break;
    case SignalClassifier::State::LEFT:
      ledGrid.setSignal(&leftSignal);
      break;
    case SignalClassifier::State::RIGHT:
      ledGrid.setSignal(&rightSignal);
      break;
  }
}

void updateMusic() {
  ledGrid.setSignal(&musicSignal);
}


void actuate() {
  ledGrid.refresh();
}


void loop() {
  sense();
  analyze();
  //actuate();

  delay(DELAY);
}
