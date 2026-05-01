/*
 * File: Altitude
 * Author: Michael Franks 
 * Description:
 */

#include "Altitude.h"
#include "pico/stdlib.h"

Altitude::Altitude(i2c_inst_t* i2c, uint sda, uint scl, uint8_t addr)
    : I2cDevice(i2c, sda, scl, addr)
{
}

bool Altitude::begin()
{
    if (readReg(0xD0) != 0x55) return false;
    readCalibration();
    return true;
}

void Altitude::readCalibration()
{
    uint8_t raw[22];
    readRegs(REG_CALIB, raw, 22);

    AC1 = (raw[0] << 8) | raw[1];
    AC2 = (raw[2] << 8) | raw[3];
    AC3 = (raw[4] << 8) | raw[5];
    AC4 = (raw[6] << 8) | raw[7];
    AC5 = (raw[8] << 8) | raw[9];
    AC6 = (raw[10] << 8) | raw[11];
    B1 = (raw[12] << 8) | raw[13];
    B2 = (raw[14] << 8) | raw[15];
    MB = (raw[16] << 8) | raw[17];
    MC = (raw[18] << 8) | raw[19];
    MD = (raw[20] << 8) | raw[21];
}

int32_t Altitude::readRawTemp()
{
    writeReg(REG_CONTROL, CMD_TEMP);
    sleep_ms(5);
    uint8_t raw[2];
    readRegs(REG_RESULT, raw, 2);
    return (raw[0] << 8) | raw[1];
}

int32_t Altitude::readRawPressure()
{
    writeReg(REG_CONTROL, CMD_PRESSURE);
    sleep_ms(8);
    uint8_t raw[3];
    readRegs(REG_RESULT, raw, 3);
    return ((raw[0] << 16) | (raw[1] << 8) | raw[2]) >> 8;
}

float Altitude::readTemperature()
{
    int32_t UT = readRawTemp();
    int32_t X1 = ((UT - AC6) * AC5) >> 15;
    int32_t X2 = (MC << 11) / (X1 + MD);
    B5 = X1 + X2;
    return ((B5 + 8) >> 4) / 10.0f;
}

float Altitude::readPressure()
{
    readTemperature(); // Updates B5

    int32_t UP = readRawPressure();
    int32_t B6 = B5 - 4000;
    int32_t X1 = (B2 * (B6 * B6 >> 12)) >> 11;
    int32_t X2 = AC2 * B6 >> 11;
    int32_t X3 = X1 + X2;
    int32_t B3 = (((AC1 * 4 + X3)) + 2) >> 2;

    X1 = AC3 * B6 >> 13;
    X2 = (B1 * (B6 * B6 >> 12)) >> 16;
    X3 = ((X1 + X2) + 2) >> 2;
    uint32_t B4 = AC4 * (uint32_t)(X3 + 32768) >> 15;
    uint32_t B7 = ((uint32_t)UP - B3) * 50000;

    int32_t p = (B7 < 0x80000000) ? (B7 * 2) / B4 : (B7 / B4) * 2;

    X1 = (p >> 8) * (p >> 8);
    X1 = (X1 * 3038) >> 16;
    X2 = (-7357 * p) >> 16;

    return (p + ((X1 + X2 + 3791) >> 4)) / 100.0f;
}
