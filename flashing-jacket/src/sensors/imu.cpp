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

  	*data[0] = a.acceleration.x;
  	*data[1] = a.acceleration.y;
  	*data[2] = a.acceleration.z;
  	*data[3] = g.gyro.x;
  	*data[4] = g.gyro.y;
  	*data[5] = g.gyro.z;
}