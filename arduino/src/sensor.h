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

#ifndef _SENSOR_H
#define _SENSOR_H

#include "config.h"

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Arduino_I2C_ESC.h>
#include <utility/imumaths.h>
#include "MS5837.h"

uint8_t imu_system();
uint8_t imu_gyro();
uint8_t imu_accel();
uint8_t imu_mag();
int imu_temp_get();
float imu_X();
float imu_Y();
float imu_Z();
float imu_accl_X();
float imu_accl_Y();
float imu_accl_Z();
float imu_heading();
float imu_roll();
float imu_pitch();

void imu_loop();
void imu_setup();

float pressure_get();
int temp_get();
float depth_get();
int alt_get();
void depth_loop();
void depth_setup();

float current_get();
float amp_get();
void current_setup();
void amp_setup();

void sensor_setup();

#endif

