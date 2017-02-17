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

#include <Servo.h>
#include <Wire.h>
#include "Arduino_I2C_ESC.h"

#ifndef _MOTOR_H
#define _MOTOR_H

typedef struct {
  int proto;            // proto:  1:'PWM', 2:I2C
  int addr;             // pin: 3 or i2c address
  int pole;             // 6 for T100, 8 for T200
  int neutral;          // neutral: 1500,
  int min;              // min: 1100,
  int max;              // max: 1900,
  int reverse;          // reverse: true
  Servo servo;
  float voltage;
  float current;
  float temperature;
  int16_t rpm;
  unsigned char direction;      // 0 1 2 4 8 16 32 64 128
} Motor_Config;

class Motor {
public:
	void setup();
	int time();
	int power();
        void power(int);
	int arm();
	void arm(boolean);
	void loop();
private:
	int _time = 0;
	int _power = 0;
	boolean _armed = false;
};

#endif


