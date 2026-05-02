/*
* File: MotorController
 * Author: Michael Franks
 * Description: Dual motor controller via TB6612FNG
 */

#include "MotorController.h"

MotorController::MotorController(
    uint pwma, uint ain1, uint ain2,
    uint pwmb, uint bin1, uint bin2,
    uint stby)
    : _motorA(pwma, ain1, ain2),
      _motorB(pwmb, bin1, bin2),
      _stby_pin(stby)
{
}

void MotorController::begin()
{
    // Init standby pin — must be HIGH to enable motors
    gpio_init(_stby_pin);
    gpio_set_dir(_stby_pin, GPIO_OUT);
    gpio_put(_stby_pin, 1); // enable

    _motorA.begin();
    _motorB.begin();
}

void MotorController::forward(float speed)
{
    _motorA.forward(speed);
    _motorB.forward(speed);
}

void MotorController::backward(float speed)
{
    _motorA.backward(speed);
    _motorB.backward(speed);
}

void MotorController::turnLeft(float speed)
{
    _motorA.forward(speed * 0.5f); // left motor slower
    _motorB.forward(speed); // right motor full
}

void MotorController::turnRight(float speed)
{
    _motorA.forward(speed); // left motor full
    _motorB.forward(speed * 0.5f); // right motor slower
}

void MotorController::spinLeft(float speed)
{
    _motorA.backward(speed);
    _motorB.forward(speed);
}

void MotorController::spinRight(float speed)
{
    _motorA.forward(speed);
    _motorB.backward(speed);
}

void MotorController::brake()
{
    _motorA.brake();
    _motorB.brake();
}

void MotorController::coast()
{
    _motorA.coast();
    _motorB.coast();
}

void MotorController::setMotorA(float speed)
{
    if (speed > 0) _motorA.forward(speed);
    else if (speed < 0) _motorA.backward(-speed);
    else _motorA.coast();
}

void MotorController::setMotorB(float speed)
{
    if (speed > 0) _motorB.forward(speed);
    else if (speed < 0) _motorB.backward(-speed);
    else _motorB.coast();
}
