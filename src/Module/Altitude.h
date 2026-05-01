/*
* File: Altitude
 * Author: Michael Franks
 * Description: BMP180 pressure/temperature driver
 */

#pragma once
#include <cstdint>
#include "I2cDevice.h"

class Altitude : public I2cDevice
{
public:
    Altitude(i2c_inst_t* i2c, uint sda, uint scl, uint8_t addr = 0x77);

    bool begin() override;
    float readTemperature();
    float readPressure();

private:
    int16_t AC1, AC2, AC3;
    uint16_t AC4, AC5, AC6;
    int16_t B1, B2, MB, MC, MD;
    int32_t B5;

    void readCalibration();
    int32_t readRawTemp();
    int32_t readRawPressure();

    static constexpr uint8_t REG_CALIB = 0xAA;
    static constexpr uint8_t REG_CONTROL = 0xF4;
    static constexpr uint8_t REG_RESULT = 0xF6;
    static constexpr uint8_t CMD_TEMP = 0x2E;
    static constexpr uint8_t CMD_PRESSURE = 0x34;
};
