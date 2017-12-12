// Source: http://arduinolearning.com/code/arduino-and-ws2812b-example.php

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
 
// Which pin on the Arduino is connected to the NeoPixels?
 
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS1      20
#define NUMPIXELS2      77
 
Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(NUMPIXELS1, 11, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS2, 12, NEO_GRB + NEO_KHZ800);

// Colors
#define RED           pixels1.Color(255,0,0)
#define YELLOW        pixels1.Color(255,255,0)
#define GREEN         pixels1.Color(0,255,0)
#define BLUE          pixels2.Color(0,0,255)
#define OFF           pixels1.Color(0,0,0)

// States
#define GO            0
#define STOPPING      1
#define LEFT          2
#define RIGHT         3
#define NONE          4
 
String msg;
int state;

void allOff() {
  for (int i = 0; i < NUMPIXELS1; i++) {
    pixels1.setPixelColor(i, OFF);
  }
  for (int i = 0; i < NUMPIXELS2; i++) {
    pixels2.setPixelColor(i, OFF);
  }
  pixels1.show();
  pixels2.show();
  delay(500);
}

void stopping() {
  for (int i = 0; i < NUMPIXELS1; i++) {
    pixels1.setPixelColor(i, RED);
  }
  for (int i = 0; i < NUMPIXELS2; i++) {
    pixels2.setPixelColor(i, RED);
  }
  pixels1.show();
  pixels2.show();
  delay(500);
}

void left() {
  allOff();
  pixels1.setPixelColor(4, YELLOW);
  pixels1.setPixelColor(5, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  pixels1.setPixelColor(3, YELLOW);
  pixels1.setPixelColor(6, YELLOW);
  pixels1.setPixelColor(14, YELLOW);
  pixels1.setPixelColor(15, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  pixels1.setPixelColor(2, YELLOW);
  pixels1.setPixelColor(7, YELLOW);
  pixels1.setPixelColor(13, YELLOW);
  pixels1.setPixelColor(16, YELLOW);
  pixels2.setPixelColor(3, YELLOW);
  pixels2.setPixelColor(4, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  pixels1.setPixelColor(1, YELLOW);
  pixels1.setPixelColor(8, YELLOW);
  pixels1.setPixelColor(12, YELLOW);
  pixels1.setPixelColor(17, YELLOW);
  pixels2.setPixelColor(2, YELLOW);
  pixels2.setPixelColor(5, YELLOW);
  pixels2.setPixelColor(13, YELLOW);
  pixels2.setPixelColor(14, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  pixels1.setPixelColor(0, YELLOW);
  pixels1.setPixelColor(9, YELLOW);
  pixels1.setPixelColor(11, YELLOW);
  pixels1.setPixelColor(18, YELLOW);
  pixels2.setPixelColor(1, YELLOW);
  pixels2.setPixelColor(6, YELLOW);
  pixels2.setPixelColor(12, YELLOW);
  pixels2.setPixelColor(15, YELLOW);
  pixels2.setPixelColor(23, YELLOW);
  pixels2.setPixelColor(24, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 0; i < 10; i++)
    pixels1.setPixelColor(i, OFF);
  pixels1.setPixelColor(10, YELLOW);
  pixels1.setPixelColor(19, YELLOW);
  pixels2.setPixelColor(0, YELLOW);
  pixels2.setPixelColor(7, YELLOW);
  pixels2.setPixelColor(11, YELLOW);
  pixels2.setPixelColor(16, YELLOW);
  pixels2.setPixelColor(22, YELLOW);
  pixels2.setPixelColor(25, YELLOW);
  pixels2.setPixelColor(33, YELLOW);
  pixels2.setPixelColor(34, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 10; i < 20; i++)
    pixels1.setPixelColor(i, OFF);
  pixels2.setPixelColor(8, YELLOW);
  pixels2.setPixelColor(10, YELLOW);
  pixels2.setPixelColor(17, YELLOW);
  pixels2.setPixelColor(21, YELLOW);
  pixels2.setPixelColor(26, YELLOW);
  pixels2.setPixelColor(32, YELLOW);
  pixels2.setPixelColor(35, YELLOW);
  pixels2.setPixelColor(41, YELLOW);
  pixels2.setPixelColor(42, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 0; i < 9; i++)
    pixels2.setPixelColor(i, OFF);
  pixels2.setPixelColor(9, YELLOW);
  pixels2.setPixelColor(18, YELLOW);
  pixels2.setPixelColor(20, YELLOW);
  pixels2.setPixelColor(27, YELLOW);
  pixels2.setPixelColor(31, YELLOW);
  pixels2.setPixelColor(36, YELLOW);
  pixels2.setPixelColor(40, YELLOW);
  pixels2.setPixelColor(43, YELLOW);
  pixels2.setPixelColor(51, YELLOW);
  pixels2.setPixelColor(52, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 9; i < 19; i++)
    pixels2.setPixelColor(i, OFF);
  pixels2.setPixelColor(19, YELLOW);
  pixels2.setPixelColor(28, YELLOW);
  pixels2.setPixelColor(30, YELLOW);
  pixels2.setPixelColor(39, YELLOW);
  pixels2.setPixelColor(44, YELLOW);
  pixels2.setPixelColor(50, YELLOW);
  pixels2.setPixelColor(53, YELLOW);
  pixels2.setPixelColor(61, YELLOW);
  pixels2.setPixelColor(62, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 19; i < 29; i++)
    pixels2.setPixelColor(i, OFF);
  pixels2.setPixelColor(29, YELLOW);
  pixels2.setPixelColor(38, YELLOW);
  pixels2.setPixelColor(45, YELLOW);
  pixels2.setPixelColor(49, YELLOW);
  pixels2.setPixelColor(54, YELLOW);
  pixels2.setPixelColor(60, YELLOW);
  pixels2.setPixelColor(63, YELLOW);
  pixels2.setPixelColor(71, YELLOW);
  pixels2.setPixelColor(72, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 29; i < 37; i++)
    pixels2.setPixelColor(i, OFF);
  pixels2.setPixelColor(37, YELLOW);
  pixels2.setPixelColor(46, YELLOW);
  pixels2.setPixelColor(48, YELLOW);
  pixels2.setPixelColor(55, YELLOW);
  pixels2.setPixelColor(59, YELLOW);
  pixels2.setPixelColor(64, YELLOW);
  pixels2.setPixelColor(70, YELLOW);
  pixels2.setPixelColor(73, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 37; i < 47; i++)
    pixels2.setPixelColor(i, OFF);
  pixels2.setPixelColor(47, YELLOW);
  pixels2.setPixelColor(56, YELLOW);
  pixels2.setPixelColor(58, YELLOW);
  pixels2.setPixelColor(65, YELLOW);
  pixels2.setPixelColor(69, YELLOW);
  pixels2.setPixelColor(74, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 47; i < 57; i++)
    pixels2.setPixelColor(i, OFF);
  pixels2.setPixelColor(57, YELLOW);
  pixels2.setPixelColor(66, YELLOW);
  pixels2.setPixelColor(68, YELLOW);
  pixels2.setPixelColor(75, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 57; i < 67; i++)
    pixels2.setPixelColor(i, OFF);
  pixels2.setPixelColor(67, YELLOW);
  pixels2.setPixelColor(76, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 67; i < 77; i++)
    pixels2.setPixelColor(i, OFF);
  delay(50);
}

void right() {
  allOff();
  pixels2.setPixelColor(71, YELLOW);
  pixels2.setPixelColor(72, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  pixels2.setPixelColor(70, YELLOW);
  pixels2.setPixelColor(73, YELLOW);
  pixels2.setPixelColor(61, YELLOW);
  pixels2.setPixelColor(62, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  pixels2.setPixelColor(69, YELLOW);
  pixels2.setPixelColor(74, YELLOW);
  pixels2.setPixelColor(60, YELLOW);
  pixels2.setPixelColor(63, YELLOW);
  pixels2.setPixelColor(51, YELLOW);
  pixels2.setPixelColor(52, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  pixels2.setPixelColor(68, YELLOW);
  pixels2.setPixelColor(75, YELLOW);
  pixels2.setPixelColor(59, YELLOW);
  pixels2.setPixelColor(64, YELLOW);
  pixels2.setPixelColor(50, YELLOW);
  pixels2.setPixelColor(53, YELLOW);
  pixels2.setPixelColor(41, YELLOW);
  pixels2.setPixelColor(42, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  pixels2.setPixelColor(67, YELLOW);
  pixels2.setPixelColor(76, YELLOW);
  pixels2.setPixelColor(58, YELLOW);
  pixels2.setPixelColor(65, YELLOW);
  pixels2.setPixelColor(49, YELLOW);
  pixels2.setPixelColor(54, YELLOW);
  pixels2.setPixelColor(40, YELLOW);
  pixels2.setPixelColor(43, YELLOW);
  pixels2.setPixelColor(33, YELLOW);
  pixels2.setPixelColor(34, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 67; i < 77; i++)
    pixels2.setPixelColor(i, OFF);
  pixels2.setPixelColor(57, YELLOW);
  pixels2.setPixelColor(66, YELLOW);
  pixels2.setPixelColor(48, YELLOW);
  pixels2.setPixelColor(55, YELLOW);
  pixels2.setPixelColor(39, YELLOW);
  pixels2.setPixelColor(44, YELLOW);
  pixels2.setPixelColor(32, YELLOW);
  pixels2.setPixelColor(35, YELLOW);
  pixels2.setPixelColor(23, YELLOW);
  pixels2.setPixelColor(24, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 57; i < 67; i++)
    pixels2.setPixelColor(i, OFF);
  pixels2.setPixelColor(47, YELLOW);
  pixels2.setPixelColor(56, YELLOW);
  pixels2.setPixelColor(38, YELLOW);
  pixels2.setPixelColor(45, YELLOW);
  pixels2.setPixelColor(31, YELLOW);
  pixels2.setPixelColor(36, YELLOW);
  pixels2.setPixelColor(22, YELLOW);
  pixels2.setPixelColor(25, YELLOW);
  pixels2.setPixelColor(13, YELLOW);
  pixels2.setPixelColor(14, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 47; i < 57; i++)
    pixels2.setPixelColor(i, OFF);
  pixels2.setPixelColor(37, YELLOW);
  pixels2.setPixelColor(46, YELLOW);
  pixels2.setPixelColor(30, YELLOW);
  pixels2.setPixelColor(21, YELLOW);
  pixels2.setPixelColor(26, YELLOW);
  pixels2.setPixelColor(12, YELLOW);
  pixels2.setPixelColor(15, YELLOW);
  pixels2.setPixelColor(3, YELLOW);
  pixels2.setPixelColor(4, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 37; i < 47; i++)
    pixels2.setPixelColor(i, OFF);
  pixels2.setPixelColor(29, YELLOW);
  pixels2.setPixelColor(20, YELLOW);
  pixels2.setPixelColor(27, YELLOW);
  pixels2.setPixelColor(11, YELLOW);
  pixels2.setPixelColor(16, YELLOW);
  pixels2.setPixelColor(2, YELLOW);
  pixels2.setPixelColor(5, YELLOW);
  pixels1.setPixelColor(14, YELLOW);
  pixels1.setPixelColor(15, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 29; i < 37; i++)
    pixels2.setPixelColor(i, OFF);
  pixels2.setPixelColor(19, YELLOW);
  pixels2.setPixelColor(28, YELLOW);
  pixels2.setPixelColor(10, YELLOW);
  pixels2.setPixelColor(17, YELLOW);
  pixels2.setPixelColor(1, YELLOW);
  pixels2.setPixelColor(6, YELLOW);
  pixels1.setPixelColor(13, YELLOW);
  pixels1.setPixelColor(16, YELLOW);
  pixels1.setPixelColor(4, YELLOW);
  pixels1.setPixelColor(5, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 19; i < 29; i++)
    pixels2.setPixelColor(i, OFF);
  pixels2.setPixelColor(9, YELLOW);
  pixels2.setPixelColor(18, YELLOW);
  pixels2.setPixelColor(0, YELLOW);
  pixels2.setPixelColor(7, YELLOW);
  pixels1.setPixelColor(12, YELLOW);
  pixels1.setPixelColor(17, YELLOW);
  pixels1.setPixelColor(3, YELLOW);
  pixels1.setPixelColor(6, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 9; i < 19; i++)
    pixels2.setPixelColor(i, OFF);
  pixels2.setPixelColor(8, YELLOW);
  pixels1.setPixelColor(11, YELLOW);
  pixels1.setPixelColor(18, YELLOW);
  pixels1.setPixelColor(2, YELLOW);
  pixels1.setPixelColor(7, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 0; i < 9; i++)
    pixels2.setPixelColor(i, OFF);
  pixels1.setPixelColor(10, YELLOW);
  pixels1.setPixelColor(19, YELLOW);
  pixels1.setPixelColor(1, YELLOW);
  pixels1.setPixelColor(8, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 10; i < 20; i++)
    pixels1.setPixelColor(i, OFF);
  pixels1.setPixelColor(0, YELLOW);
  pixels1.setPixelColor(9, YELLOW);
  pixels1.show();
  pixels2.show();
  delay(50);
  for (int i = 0; i < 10; i++)
    pixels1.setPixelColor(i, OFF);
  delay(50);
}

void go() {
  for (int i = 0; i < NUMPIXELS1; i++) {
    pixels1.setPixelColor(i, GREEN);
  }
  for (int i = 0; i < NUMPIXELS2; i++) {
    pixels2.setPixelColor(i, GREEN);
  }
  pixels1.show();
  pixels2.show();
  delay(500);
}
 
void setup() 
{
  pixels1.begin(); // This initializes the NeoPixel library.
  pixels2.begin();

  Serial.begin(9600);

  state = NONE;
}
 
void loop() {
  if (Serial.available() > 0) { 
    msg = Serial.readString();
    if (msg == "go")
      state = GO;
    else if (msg == "stop")
      state = STOPPING;
    else if (msg == "left")
      state = LEFT;
    else if (msg == "right")
      state = RIGHT;
    else {
      state = NONE;
      Serial.println("Invalid message");
    }
    Serial.println("Received");
  }

  switch(state) {
    case GO:
      go();
      break;
    case STOPPING:
      stopping();
      break;
    case LEFT:
      left();
      break;
    case RIGHT:
      right();
      break;
    case NONE:
      allOff();
  }
}

