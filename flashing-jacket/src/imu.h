#ifndef IMU_H
#define IMU_H

typedef struct {
	float acc_x;
	float acc_y;
	float acc_z;
	float gyr_x;
	float gyr_y;
	float gyr_z;
} ImuData;

class IMU {
public:
	IMU();
	void read(ImuData *data);
}