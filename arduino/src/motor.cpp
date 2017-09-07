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

#include "motor.h"

int MOTOR_ARM=0;

Servo Motor1;
Servo Motor2;
Servo Motor3;
Servo Motor4;
Servo Motor5;
Servo Motor6;

void motor_arm(int b)
{
    MOTOR_ARM=b;
}

int motor_arm()
{
    return MOTOR_ARM;
}

void motor_forward(int MOTOR_POWER)
{
    if (MOTOR_ARM) {
        Motor1.writeMicroseconds(1500+(4*MOTOR_POWER));
        Motor2.writeMicroseconds(1500-(4*MOTOR_POWER));
        Motor3.writeMicroseconds(1500+(4*MOTOR_POWER));
        Motor4.writeMicroseconds(1500+(4*MOTOR_POWER));
    }
}
void motor_reverse(int MOTOR_POWER)
{
    if (MOTOR_ARM) {
        Motor1.writeMicroseconds(1500-(4*MOTOR_POWER));
        Motor2.writeMicroseconds(1500+(4*MOTOR_POWER));
        Motor3.writeMicroseconds(1500-(4*MOTOR_POWER));
        Motor4.writeMicroseconds(1500-(4*MOTOR_POWER));
    }
}
void motor_right(int MOTOR_POWER)
{
    if (MOTOR_ARM) {
        Motor1.writeMicroseconds(1500-(4*MOTOR_POWER));
        Motor2.writeMicroseconds(1500-(4*MOTOR_POWER));
        Motor3.writeMicroseconds(1500+(4*MOTOR_POWER));
        Motor4.writeMicroseconds(1500-(4*MOTOR_POWER));
    }
}
void motor_left(int MOTOR_POWER)
{
    if (MOTOR_ARM) {
        Motor1.writeMicroseconds(1500+(4*MOTOR_POWER));
        Motor2.writeMicroseconds(1500+(4*MOTOR_POWER));
        Motor3.writeMicroseconds(1500-(4*MOTOR_POWER));
        Motor4.writeMicroseconds(1500+(4*MOTOR_POWER));
    }
}
void motor_dive(int MOTOR_POWER)
{
    if (MOTOR_ARM) {
        Motor5.writeMicroseconds(1500+(4*MOTOR_POWER));
        Motor6.writeMicroseconds(1500-(4*MOTOR_POWER));
    }
}
void motor_up(int MOTOR_POWER)
{
    if (MOTOR_ARM) {
        Motor5.writeMicroseconds(1500-(4*MOTOR_POWER));
        Motor6.writeMicroseconds(1500+(4*MOTOR_POWER));
    }
}
void motor_strafe_right(int MOTOR_POWER)
{
    if (MOTOR_ARM) {
        Motor1.writeMicroseconds(1500-(4*MOTOR_POWER));
        Motor2.writeMicroseconds(1500-(4*MOTOR_POWER));
        Motor3.writeMicroseconds(1500-(4*MOTOR_POWER));
        Motor4.writeMicroseconds(1500+(4*MOTOR_POWER));
    }
}
void motor_strafe_left(int MOTOR_POWER)
{
    if (MOTOR_ARM) {
        Motor1.writeMicroseconds(1500+(4*MOTOR_POWER));
        Motor2.writeMicroseconds(1500+(4*MOTOR_POWER));
        Motor3.writeMicroseconds(1500+(4*MOTOR_POWER));
        Motor4.writeMicroseconds(1500-(4*MOTOR_POWER));
    }
}
void motor_roll_right(int MOTOR_POWER)
{
    if (MOTOR_ARM) {
        Motor5.writeMicroseconds(1500-(4*MOTOR_POWER));
        Motor6.writeMicroseconds(1500+(4*MOTOR_POWER));
    }
}
void motor_roll_left(int MOTOR_POWER)
{
    if (MOTOR_ARM) {
        Motor5.writeMicroseconds(1500+(4*MOTOR_POWER));
        Motor6.writeMicroseconds(1500-(4*MOTOR_POWER));
    }
}

void motor_stop()
{
    Motor1.writeMicroseconds(1500);
    Motor2.writeMicroseconds(1500);
    Motor3.writeMicroseconds(1500);
    Motor4.writeMicroseconds(1500);
    Motor5.writeMicroseconds(1500);
    Motor6.writeMicroseconds(1500);
}

void motor_setup()
{
    Motor1.attach(9);
    Motor1.writeMicroseconds(1500);
    Motor2.attach(10);
    Motor2.writeMicroseconds(1500);
    Motor3.attach(20);
    Motor3.writeMicroseconds(1500);
    Motor4.attach(21);
    Motor4.writeMicroseconds(1500);
    Motor5.attach(22);
    Motor5.writeMicroseconds(1500);
    Motor6.attach(23);
    Motor6.writeMicroseconds(1500);
}

