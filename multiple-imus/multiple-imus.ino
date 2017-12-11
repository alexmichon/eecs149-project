#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!

// i2c
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

#define LSM9DS1_SCK 24
#define LSM9DS1_MISO 22
#define LSM9DS1_MOSI 23

#define LSM9DS1_XGCS1 5 // CHIP SELECT IMU 1
#define LSM9DS1_XGCS2 10 // CHIP SELECT IMU 2

// You can also use software SPI

// Feather: set manually SPI pins
Adafruit_LSM9DS1 lsm1 = Adafruit_LSM9DS1(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS1);
Adafruit_LSM9DS1 lsm2 = Adafruit_LSM9DS1(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS2);

// Or hardware SPI! In this case, only CS pins are passed in
//Adafruit_LSM9DS1 lsm1 = Adafruit_LSM9DS1(LSM9DS1_XGCS1);
//Adafruit_LSM9DS1 lsm2 = Adafruit_LSM9DS1(LSM9DS1_XGCS2);


void setupSensor(Adafruit_LSM9DS1 l)
{
  // 1.) Set the accelerometer range
  l.setupAccel(l.LSM9DS1_ACCELRANGE_2G);
  //l.setupAccel(l.LSM9DS1_ACCELRANGE_4G);
  //l.setupAccel(l.LSM9DS1_ACCELRANGE_8G);
  //l.setupAccel(l.LSM9DS1_ACCELRANGE_16G);

  // 2.) Setup the gyroscope
  l.setupGyro(l.LSM9DS1_GYROSCALE_245DPS);
  //l.setupGyro(l.LSM9DS1_GYROSCALE_500DPS);
  //l.setupGyro(l.LSM9DS1_GYROSCALE_2000DPS);
}


void setup() 
{
  Serial.begin(115200);

  while (!Serial) {
    delay(1); // will pause Zero, Leonardo, etc until serial console opens
  }
  
  Serial.println("LSM9DS1 data read demo");
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm1.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS1 1. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS1 9DOF 1");

  delay(10); // Keep it or initialization of next IMU fails

  if (!lsm2.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS1 2. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS1 9DOF 2");

  // helper to just set the default scaling we want, see above!
  setupSensor(lsm1);

  delay(10); // Keep it or initialization of next IMU fails
  
  setupSensor(lsm2);
}

void loop() 
{
  /* Get a new sensor event */ 
  sensors_event_t a1, g1;
  
  lsm1.getEvent(&a1, &g1);

  Serial.println("Sensor 1");
  Serial.print("Accel X: "); Serial.print(a1.acceleration.x); Serial.print(" m/s^2");
  Serial.print("\tY: "); Serial.print(a1.acceleration.y);     Serial.print(" m/s^2 ");
  Serial.print("\tZ: "); Serial.print(a1.acceleration.z);     Serial.println(" m/s^2 ");

  Serial.print("Gyro X: "); Serial.print(g1.gyro.x);   Serial.print(" dps");
  Serial.print("\tY: "); Serial.print(g1.gyro.y);      Serial.print(" dps");
  Serial.print("\tZ: "); Serial.print(g1.gyro.z);      Serial.println(" dps");

  Serial.println();

  /* Get a new sensor event */ 
  sensors_event_t a2, g2;

  lsm2.getEvent(&a2, &g2); 

  Serial.println("Sensor 2");
  Serial.print("Accel X: "); Serial.print(a2.acceleration.x); Serial.print(" m/s^2");
  Serial.print("\tY: "); Serial.print(a2.acceleration.y);     Serial.print(" m/s^2 ");
  Serial.print("\tZ: "); Serial.print(a2.acceleration.z);     Serial.println(" m/s^2 ");

  Serial.print("Gyro X: "); Serial.print(g2.gyro.x);   Serial.print(" dps");
  Serial.print("\tY: "); Serial.print(g2.gyro.y);      Serial.print(" dps");
  Serial.print("\tZ: "); Serial.print(g2.gyro.z);      Serial.println(" dps");

  Serial.println();

  delay(100);
}
