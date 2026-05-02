#include <cstdio>
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "Module/Altitude.h"
#include "Module/Inertial.h"
#include "Module/Battery.h"

// Inertial sensor on i2c0
#define MPU_SDA_PIN 12
#define MPU_SCL_PIN 13

// Altitude on i2c1
#define BMP_SDA_PIN 14
#define BMP_SCL_PIN 15

// Battery on ADC0
#define BATTERY_PIN 26

#define PWMA 0 // Motor A speed (PWM)
#define AIN1 1 // Motor A direction
#define AIN2 2 // Motor A direction
#define PWMB 3 // Motor B speed (PWM)
#define BIN1 4 // Motor B direction
#define BIN2 5 // Motor B direction
#define STBY 6 // Standby enable


void blinkBattery(float percent)
{
    int blinks = percent > 60 ? 3 : percent > 30 ? 2 : 1;
    for (int i = 0; i < blinks; i++)
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(200);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(200);
    }
    sleep_ms(1000); // pause between blink groups
}

int main()
{
    stdio_init_all();
    sleep_ms(2000);

    // Init CYW43 for LED use
    if (cyw43_arch_init())
    {
        printf("ERROR: CYW43 init failed!\n");
        while (true) tight_loop_contents();
    }
    printf("CYW43 OK\n");

    printf("Creating Inertial...\n");
    Inertial inertial(i2c0, MPU_SDA_PIN, MPU_SCL_PIN);
    printf("Creating Altitude...\n");
    Altitude altitude(i2c1, BMP_SDA_PIN, BMP_SCL_PIN);
    printf("Creating Battery...\n");
    Battery battery(BATTERY_PIN);

    if (!inertial.begin())
    {
        printf("ERROR: MPU6050 not found! Check GP%d/GP%d\n", MPU_SDA_PIN, MPU_SCL_PIN);
        while (true) tight_loop_contents();
    }
    printf("MPU6050 OK\n");

    if (!altitude.begin())
    {
        printf("ERROR: BMP180 not found! Check GP%d/GP%d\n", BMP_SDA_PIN, BMP_SCL_PIN);
        while (true) tight_loop_contents();
    }
    printf("BMP180 OK\n");
    printf("All sensors ready!\n\n");

    float accel[3], gyro[3];
    float temp, pressure;

    int loop_count = 0;

    while (true)
    {
        inertial.readG(accel, gyro);
        temp = altitude.readTemperature();
        pressure = altitude.readPressure();

        if (stdio_usb_connected())
        {
            printf("--- IMU ---\n");
            printf("  Accel (g):  X=%7.3f  Y=%7.3f  Z=%7.3f\n", accel[0], accel[1], accel[2]);
            printf("  Gyro (d/s): X=%7.3f  Y=%7.3f  Z=%7.3f\n", gyro[0], gyro[1], gyro[2]);
            printf("--- Baro ---\n");
            printf("  Temp:     %.2f C\n", temp);
            printf("  Pressure: %.2f hPa\n\n", pressure);
            printf("--- Battery ---\n");
            if (battery.isUsbConnected())
                printf("  USB connected\n\n");
            else
                printf("  %.2fV  %.1f%%\n\n", battery.voltage(), battery.percentage());
        }

        // Only blink every 10 loops (~5 seconds)
        loop_count++;
        if (loop_count >= 10)
        {
            loop_count = 0;
            blinkBattery(battery.percentage());
        }

        sleep_ms(500);
    }
}
