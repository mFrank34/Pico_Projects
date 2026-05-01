/*
* File: I2cDevice
 * Author: Michael Franks
 * Description: Base class for I2C devices
 */

#include "I2cDevice.h"
#include "hardware/gpio.h"

I2cDevice::I2cDevice(i2c_inst_t* i2c, uint sda, uint scl, uint8_t addr)
    : _i2c(i2c), _sda(sda), _scl(scl), _addr(addr)
{
}

void I2cDevice::initBus(uint32_t freq) const
{
    i2c_init(_i2c, freq);
    gpio_set_function(_sda, GPIO_FUNC_I2C);
    gpio_set_function(_scl, GPIO_FUNC_I2C);
    gpio_pull_up(_sda);
    gpio_pull_up(_scl);
}

void I2cDevice::writeReg(uint8_t reg, uint8_t value) const
{
    uint8_t buf[2] = {reg, value};
    i2c_write_timeout_us(_i2c, _addr, buf, 2, false, 10000);
}

void I2cDevice::readRegs(uint8_t reg, uint8_t* buf, size_t len) const
{
    i2c_write_timeout_us(_i2c, _addr, &reg, 1, true, 10000);
    i2c_read_timeout_us(_i2c, _addr, buf, len, false, 10000);
}

uint8_t I2cDevice::readReg(uint8_t reg) const
{
    uint8_t val = 0;
    readRegs(reg, &val, 1);
    return val;
}
