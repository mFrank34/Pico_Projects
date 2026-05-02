/*
* File: Motor
 * Author: Michael Franks
 * Description: Single DC motor control via TB6612FNG
 */

#ifndef MOTOR_H
#define MOTOR_H

#pragma once
#include "pico/stdlib.h"
#include "hardware/pwm.h"

class Motor
{
public:
    Motor(uint pwm_pin, uint in1_pin, uint in2_pin);

    void begin();
    void forward(float speed); // 0.0 - 1.0
    void backward(float speed); // 0.0 - 1.0
    void brake();
    void coast();

private:
    uint _pwm_pin;
    uint _in1_pin;
    uint _in2_pin;
    uint _pwm_slice;
    uint _pwm_channel;

    void setSpeed(float speed);

    static constexpr uint PWM_WRAP = 4095;
};

#endif //MOTOR_H
