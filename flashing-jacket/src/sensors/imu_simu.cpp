#include "imu_simu.h"



bool IMUSimu::begin() {
	return true;
}


void IMUSimu::read(Data *data) {
	for (int i = 0; i < 6; i++) {
		(*data)[i] = random(-100, 100) / 100;
	}
}