#include "imu.h"

IMU::IMU(int sck, int miso, int mosi, int cs): Adafruit_LSM9DS1(sck, miso, mosi, cs)  {

}


bool IMU::begin() {
	if (!begin()) {
		return false;
	}

	setupAccel(LSM9DS1_ACCELRANGE_2G);
	setupGyro(LSM9DS1_GYROSCALE_245DPS);

	return true;
}


void IMU::read(Data *data) {
	sensors_event_t a, g;
  	getEvent(&a, &g);

  	data->accX = a.acceleration.x;
  	data->accY = a.acceleration.y;
  	data->accZ = a.acceleration.z;

  	data->gyrX = g.gyro.x;
  	data->gyrY = g.gyro.y;
  	data->gyrZ = g.gyro.z;
}