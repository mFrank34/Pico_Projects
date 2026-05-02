/*
* File: MotorController
* Author: Michael Franks
* Description: Dual motor controller via TB6612FNG
*/

#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#pragma once
#include "Motor.h"

class MotorController
{
public:
    MotorController(
        uint pwma, uint ain1, uint ain2,
        uint pwmb, uint bin1, uint bin2,
        uint stby
    );

    void begin();

    void forward(float speed); // both motors forward
    void backward(float speed); // both motors backward
    void turnLeft(float speed); // left slower
    void turnRight(float speed); // right slower
    void spinLeft(float speed); // opposite directions
    void spinRight(float speed); // opposite directions
    void brake(); // hard stop
    void coast(); // free roll

    // Direct motor control
    void setMotorA(float speed); // -1.0 to 1.0
    void setMotorB(float speed); // -1.0 to 1.0

private:
    Motor _motorA;
    Motor _motorB;
    uint _stby_pin;
};
#endif //MOTORCONTROLLER_H
