/*

 Copyright (C) 2017 Eric van Dijken <eric@team-moki.nl>

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

*/

#pragma once
#ifndef _SENSOR_H
#define _SENSOR_H

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Arduino_I2C_ESC.h>
#include <utility/imumaths.h>
#include <MS5837.h>
#include "Config.h"

class Sensor {
    public:
        // IMU
        uint8_t Imu_System();
        uint8_t Imu_Gyro();
        uint8_t Imu_Accel();
        uint8_t Imu_Mag();
        int Imu_Temp();
        float Imu_X();
        float Imu_Y();
        float Imu_Z();
        float Imu_Accl_X();
        float Imu_Accl_Y();
        float Imu_Accl_Z();
        float Imu_Heading();
        float Imu_Roll();
        float Imu_Pitch();
        void Imu_Loop();
        void Imu_Setup();
        // Depth
        float Pressure();
        int Temp();
        float Depth();
        int Alt();
        void Depth_Loop();
        void Depth_Setup();
        // Current/Amps
        float Current();
        float Amps();
        void Current_Setup();
        void Amps_Setup();
        // Overall Setup All
        void Loop();
        void Setup();
        int Time();
        void Time(int);
    private:
        // IMU
        int FOUND_BNO = 0;
        /* Set the delay between fresh samples */
        #define BNO055_SAMPLERATE_DELAY_MS (100)
        Adafruit_BNO055 bno = Adafruit_BNO055(IMU_ADDR);
        uint8_t system_imu = 0;
        uint8_t gyro = 0;
        uint8_t accel = 0;
        uint8_t mag = 0;
        int8_t imu_temp = 0;
        uint8_t system_status = 0;
        uint8_t self_test_results = 0;
        uint8_t system_error = 0;
        sensors_event_t event;
        imu::Vector<3> imu_vec;
        // Depth
        MS5837 MS5837_sensor;
        bool MS5837_status;
        // Current/Amps
        int VRaw; //This will store our raw ADC data
        float VFinal; //This will store the converted data
        int IRaw;
        float IFinal;
        int sensor_time = 0;
};
#endif
