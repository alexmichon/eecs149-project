#include "imu.h"
#include "Arduino.h"

IMU::IMU() {

}

void IMU::read(ImuData *data) {
	data->acc_x = random();
	data->acc_y = random();
	data->acc_z = random();
	data->gyr_x = random();
	data->gyr_y = random();
	data->gyr_z = random();
}