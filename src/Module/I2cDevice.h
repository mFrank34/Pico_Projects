/*
 * File: I2CDevice
 * Author: Michael Franks 
 * Description:
 */

#ifndef I2cDEVICE_H
#define I2cDEVICE_H

#pragma once
#include "hardware/i2c.h"

class I2cDevice
{
public:
    I2cDevice(i2c_inst_t* i2c, uint sda, uint scl, uint8_t addr);

    virtual ~I2cDevice() = default;
    virtual bool begin() = 0; // Pure virtual — each sensor must implement

protected:
    i2c_inst_t* _i2c;
    uint8_t _addr;
    uint _sda;
    uint _scl;

    void initBus(uint32_t freq = 400000) const;

    void writeReg(uint8_t reg, uint8_t value) const;
    void readRegs(uint8_t reg, uint8_t* buf, size_t len) const;
    uint8_t readReg(uint8_t reg) const;
};

#endif // I2cDEVICE_H
