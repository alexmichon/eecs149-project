#include "src/microphone/microphone.h"
#include "src/leds/led_strip.h"
#include "src/leds/led_strip_simu.h"
#include "src/leds/led_grid.h"

#include "src/leds/signals/brake_signal.h"
#include "src/leds/signals/idle_signal.h"


// SIMULATION
#define SIMULATION





// PINS
#define PIN_STRIP1 9
#define PIN_STRIP2 10









// LEDS

// Grid
#define NB_STRIPS 10
#define NB_LEDS 10


// Leds per strips
#define NUMPIXELS1      20
#define NUMPIXELS2      77

#ifndef SIMULATION
LedStrip ledStrip1(NUMPIXELS1, 0, PIN_STRIP1);
LedStrip ledStrip2(NUMPIXELS2, NUMPIXELS1, PIN_STRIP2);
#else
LedStripSimu ledStrip1(NUMPIXELS1, 0, PIN_STRIP1);
LedStripSimu ledStrip2(NUMPIXELS2, NUMPIXELS1, PIN_STRIP2);
#endif

LedStrip *ledStrips[2] = {&ledStrip1, &ledStrip2};
LedGrid ledGrid(ledStrips, 2);





// SIGNALS
IdleSignal idleSignal(NB_STRIPS, NB_LEDS);
BrakeSignal brakeSignal(NB_STRIPS, NB_LEDS);






// MICROPHONE

// sample rate for the input
#define SAMPLE_RATE 2000

// size of the FFT to compute
#define FFT_SIZE 128

// create an FFT analyzer to be used with the I2S input
FFTAnalyzer fftAnalyzer(FFT_SIZE);

Microphone microphone(FFT_SIZE, NB_STRIPS, NB_LEDS);

int amplitudes[NB_STRIPS];







// States
#define BIKE 0
#define MUSIC 1

int state = BIKE;



// Bike States
#define BIKE_IDLE 0
#define BIKE_BRAKE 1

int bikeState = BIKE_IDLE;




void setup() {
// Open serial communications and wait for port to open:
  // A baud rate of 115200 is used instead of 9600 for a faster data rate
  // on non-native USB ports
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  ledGrid.begin();
  //microphone.begin(SAMPLE_RATE);
}


void updateBike() {
  switch(bikeState) {
    case BIKE_IDLE:
      ledGrid.setSignal(&idleSignal);
      break;
    case BIKE_BRAKE:
      ledGrid.setSignal(&brakeSignal);
      break;
  }

  ledGrid.refresh();
}

void updateMusic() {
  if (microphone.available()) {
    // read the new spectrum
    microphone.read(amplitudes);
  }
}


void loop() {
  switch(state) {
    case BIKE:
      updateBike();
      break;
    case MUSIC:
      updateMusic();
      break;
  }

  delay(100);
} 
