#ifndef IMU_H
#define IMU_H

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!

class IMU: public Adafruit_LSM9DS1 {
public:

	typedef float Data[6];

	IMU(int sck, int miso, int mosi, int cs);

	virtual bool begin();
	virtual void read(Data *data);

};

#endif