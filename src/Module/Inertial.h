/*
 * File: Inertial_Measurement
 * Author: Michael Franks 
 * Description:
 */

#ifndef INERTIAL_H
#define INERTIAL_H
#include "I2cDevice.h"

class Inertial : public I2cDevice
{
public:
    Inertial(i2c_inst_t* i2c, uint sda, uint scl, uint8_t addr = 0x68);

    bool begin() override;

    void read(int16_t accel[3], int16_t gyro[3]) const;

    void readG(float accel[3], float gyro[3]) const;

private:
    static constexpr uint8_t REG_PWR_MGMT_1 = 0x6B;
    static constexpr uint8_t REG_ACCEL_X_OUT = 0x3B;
    static constexpr uint8_t REG_WHO_AM_I = 0x75;
};
#endif //INERTIAL_H
