#ifndef IMU_SIMU_H
#define IMU_SIMU_H

#include "imu.h"


class IMUSimu: public IMU {
public:
	using IMU::IMU;

	virtual bool begin() override;
	virtual void read(Data *data) override;
};

#endif