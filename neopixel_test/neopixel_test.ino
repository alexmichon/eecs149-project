// Source: http://arduinolearning.com/code/arduino-and-ws2812b-example.php

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
 
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            6
 
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      10
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
 
int delayval = 500; // delay for half a second
 
void setup() 
{
  pixels.begin(); // This initializes the NeoPixel library.
}
 
void loop() {
 
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
 
  for(int i=0;i<NUMPIXELS;i++)
  {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,255,0));
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(i, pixels.Color(255,0,0));
    pixels.show();
    delay(delayval);
    pixels.setPixelColor(i, pixels.Color(0,0,255));
    pixels.show();
    delay(delayval);
  }
}
