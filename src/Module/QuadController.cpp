/*
 * File: QuadMotorController
 * Author: Michael Franks
 * Description: Quad motor controller using two TB6612FNG modules
 */

#include "QuadController.h"

QuadController::QuadController(
    uint f_pwma, uint f_ain1, uint f_ain2,
    uint f_pwmb, uint f_bin1, uint f_bin2,
    uint f_stby,
    uint r_pwma, uint r_ain1, uint r_ain2,
    uint r_pwmb, uint r_bin1, uint r_bin2,
    uint r_stby)
    : _front(f_pwma, f_ain1, f_ain2, f_pwmb, f_bin1, f_bin2, f_stby),
      _rear(r_pwma, r_ain1, r_ain2, r_pwmb, r_bin1, r_bin2, r_stby)
{
}

void QuadController::begin()
{
    _front.begin();
    _rear.begin();
}

void QuadController::forward(float speed)
{
    _front.forward(speed);
    _rear.forward(speed);
}

void QuadController::backward(float speed)
{
    _front.backward(speed);
    _rear.backward(speed);
}

void QuadController::turnLeft(float speed)
{
    // Left motors slower, right motors faster
    _front.setMotorA(speed * 0.5f); // FL slower
    _front.setMotorB(speed); // FR full
    _rear.setMotorA(speed * 0.5f); // BL slower
    _rear.setMotorB(speed); // BR full
}

void QuadController::turnRight(float speed)
{
    // Right motors slower, left motors faster
    _front.setMotorA(speed); // FL full
    _front.setMotorB(speed * 0.5f); // FR slower
    _rear.setMotorA(speed); // BL full
    _rear.setMotorB(speed * 0.5f); // BR slower
}

void QuadController::spinLeft(float speed)
{
    _front.setMotorA(-speed); // FL backward
    _front.setMotorB(speed); // FR forward
    _rear.setMotorA(-speed); // BL backward
    _rear.setMotorB(speed); // BR forward
}

void QuadController::spinRight(float speed)
{
    _front.setMotorA(speed); // FL forward
    _front.setMotorB(-speed); // FR backward
    _rear.setMotorA(speed); // BL forward
    _rear.setMotorB(-speed); // BR backward
}

void QuadController::brake()
{
    _front.brake();
    _rear.brake();
}

void QuadController::coast()
{
    _front.coast();
    _rear.coast();
}

void QuadController::setFL(float speed)
{
    _front.setMotorA(speed);
}

void QuadController::setFR(float speed)
{
    _front.setMotorB(speed);
}

void QuadController::setBL(float speed)
{
    _rear.setMotorA(speed);
}

void QuadController::setBR(float speed)
{
    _rear.setMotorB(speed);
}
