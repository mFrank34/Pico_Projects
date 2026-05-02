/*
* File: QuadMotorController
 * Author: Michael Franks
 * Description: Quad motor controller using two TB6612FNG modules
 */

#ifndef QUAD_CONTROLLER_H
#define QUAD_CONTROLLER_H

#pragma once
#include "MotorController.h"

class QuadController
{
public:
    QuadController(
        // Front module
        uint f_pwma, uint f_ain1, uint f_ain2,
        uint f_pwmb, uint f_bin1, uint f_bin2,
        uint f_stby,
        // Rear module
        uint r_pwma, uint r_ain1, uint r_ain2,
        uint r_pwmb, uint r_bin1, uint r_bin2,
        uint r_stby
    );

    void begin();

    // Basic movement
    void forward(float speed);
    void backward(float speed);
    void turnLeft(float speed);
    void turnRight(float speed);
    void spinLeft(float speed);
    void spinRight(float speed);
    void brake();
    void coast();

    // Direct control per motor — useful for PID later
    void setFL(float speed); // front left  -1.0 to 1.0
    void setFR(float speed); // front right -1.0 to 1.0
    void setBL(float speed); // back left   -1.0 to 1.0
    void setBR(float speed); // back right  -1.0 to 1.0

private:
    MotorController _front; // Module 1
    MotorController _rear; // Module 2
};

#endif //QUAD_CONTROLLER_H
