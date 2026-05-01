#include <iostream>

#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"

#include "Module/Altitude.h"
#include "Module/Inertial.h"

// Inertial sensor on i2c0
#define MPU_SDA_PIN  12
#define MPU_SCL_PIN  13

// Altitude on i2c1
#define BMP_SDA_PIN  14
#define BMP_SCL_PIN  15

int main()
{
    stdio_init_all();
    sleep_ms(2000);
    printf("Starting up...\n\n");

    printf("Creating Inertial...\n");
    Inertial inertial(i2c0, MPU_SDA_PIN, MPU_SCL_PIN);
    printf("Creating Altitude...\n");
    Altitude altitude(i2c1, BMP_SDA_PIN, BMP_SCL_PIN);

    printf("Calling inertial.begin()...\n");
    if (!inertial.begin())
    {
        printf("ERROR: MPU6050 not found! Check GP%d/GP%d\n", MPU_SDA_PIN, MPU_SCL_PIN);
        while (true) tight_loop_contents();
    }
    printf("MPU6050 OK\n");

    printf("Calling altitude.begin()...\n");
    if (!altitude.begin())
    {
        printf("ERROR: BMP180 not found! Check GP%d/GP%d\n", BMP_SDA_PIN, BMP_SCL_PIN);
        while (true) tight_loop_contents();
    }
    printf("BMP180 OK\n");

    float accel[3], gyro[3];
    float temp, pressure;

    while (true)
    {
        inertial.readG(accel, gyro);
        temp = altitude.readTemperature();
        pressure = altitude.readPressure();

        printf("--- IMU ---\n");
        printf("  Accel (g):  X=%7.3f  Y=%7.3f  Z=%7.3f\n", accel[0], accel[1], accel[2]);
        printf("  Gyro (d/s): X=%7.3f  Y=%7.3f  Z=%7.3f\n", gyro[0], gyro[1], gyro[2]);
        printf("--- Baro ---\n");
        printf("  Temp:     %.2f C\n", temp);
        printf("  Pressure: %.2f hPa\n\n", pressure);

        sleep_ms(500);
    }
}
