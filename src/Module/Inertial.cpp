/*
* File: Inertial
 * Author: Michael Franks
 * Description: MPU6050 accelerometer/gyroscope driver
 */

#include "Inertial.h"

Inertial::Inertial(i2c_inst_t* i2c, uint sda, uint scl, uint8_t addr)
    : I2cDevice(i2c, sda, scl, addr)
{
}

bool Inertial::begin()
{
    initBus(); // was missing!
    sleep_ms(100);
    writeReg(REG_PWR_MGMT_1, 0x00); // wake from sleep
    sleep_ms(100);
    return readReg(REG_WHO_AM_I) == 0x68; // & changed to ==
}

void Inertial::read(int16_t accel[3], int16_t gyro[3]) const
{
    uint8_t raw[14];
    readRegs(REG_ACCEL_X_OUT, raw, 14);

    accel[0] = (raw[0] << 8) | raw[1];
    accel[1] = (raw[2] << 8) | raw[3];
    accel[2] = (raw[4] << 8) | raw[5];

    gyro[0] = (raw[8] << 8) | raw[9];
    gyro[1] = (raw[10] << 8) | raw[11];
    gyro[2] = (raw[12] << 8) | raw[13];
}

void Inertial::readG(float accel[3], float gyro[3]) const
{
    int16_t rawAccel[3], rawGyro[3];
    read(rawAccel, rawGyro);

    for (int i = 0; i < 3; i++)
    {
        accel[i] = rawAccel[i] / 16384.0f;
        gyro[i] = rawGyro[i] / 131.0f;
    }
}
