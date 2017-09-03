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

#include "sensor.h"

int FOUND_BNO = 0;

int VRaw; //This will store our raw ADC data
float VFinal; //This will store the converted data
int IRaw;
float IFinal;

MS5837 MS5837_sensor;

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055(IMU_ADDR);
uint8_t system_imu = 0;
uint8_t gyro = 0;
uint8_t accel = 0;
uint8_t mag = 0;
uint8_t system_status = 0;
uint8_t self_test_results = 0;
uint8_t system_error = 0;
sensors_event_t event;

uint8_t imu_system() {
  return system_imu;
}

uint8_t imu_gyro() {
  return gyro;
}

uint8_t imu_accel() {
  return accel;
}

uint8_t imu_mag() {
  return mag;
}

float imu_X() {
  return event.orientation.x;
}

float imu_Y() {
  return event.orientation.y;
}

float imu_Z() {
  return event.orientation.z;
}

float imu_heading() {
  return event.orientation.roll;
}

float imu_roll() {
  return event.orientation.pitch;
}

float imu_pitch() {
  return event.orientation.heading;
}

void imu_loop() {
  bno.getEvent(&event);
  bno.getCalibration(&system_imu, &gyro, &accel, &mag);
}

void imu_setup() {
  sensor_t sensor;
  if (bno.begin()) {
           FOUND_BNO = 1;
  }
  delay(1000);
  /* Display some basic information on this sensor */
  if (FOUND_BNO) {
    bno.getSensor(&sensor);
    bno.getSystemStatus(&system_status, &self_test_results, &system_error);
    bno.setExtCrystalUse(true);
  }

}

int pressure_get(){
  return(MS5837_sensor.pressure());
}

int temp_get() {
  return (MS5837_sensor.temperature());
}

int depth_get() {
  return(MS5837_sensor.depth()*100);
}

int alt_get() {
  return (MS5837_sensor.altitude());
}

void depth_loop() {
    MS5837_sensor.read();
}

void depth_setup() {
  MS5837_sensor.init();
    if (DEPTH_WATER == 1) {
      MS5837_sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)
    } else {
      MS5837_sensor.setFluidDensity(1029); // kg/m^3 (freshwater, 1029 for seawater)
    }

}

int current_get() {
  VFinal = -1;
    VRaw = analogRead(CURRENT_PIN);
    if (VRaw < 400) {
    //Conversion
      VFinal = VRaw/12.99; //180 Amp board
    }
  return(VFinal);
}

int amp_get() {
  IFinal = -1;
    IRaw = analogRead(AMP_PIN);
    if (VRaw < 400) {
      //Conversion
      IFinal = IRaw/7.4; //180 Amp board
//      IFinal = IRaw/3.7; //180 Amp board
    }
  return(IFinal);
}

void current_setup() {
}

void amp_setup() {
}

void sensor_setup() {
  imu_setup();
  depth_setup();
  current_setup();
  amp_setup();
}

