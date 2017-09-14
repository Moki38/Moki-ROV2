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
#ifndef _THRUSTER_H
#define _THRUSTER_H

#include <Arduino.h>
#include <Servo.h>
#include "Config.h"

#define THRUSTER_FORWARD	0b0000000001
#define THRUSTER_REVERSE	0b0000000010
#define THRUSTER_RIGHT		0b0000000100
#define THRUSTER_LEFT		0b0000001000
#define THRUSTER_DIVE		0b0000010000
#define THRUSTER_UP		0b0000100000
#define THRUSTER_STRAFE_RIGHT	0b0001000000
#define THRUSTER_STRAFE_LEFT	0b0010000000
#define THRUSTER_ROLL_RIGHT	0b0100000000
#define THRUSTER_ROLL_LEFT	0b1000000000

class Thruster {
    public:
        void Power(int);
        int Power();
        void Arm(bool);
        bool Arm();
// Right Left Reverse Forward Strafe_r Strafe_l Dive Up
        void Run(int, int);
        void Forward(int);
        void Reverse(int);
        void Right(int);
        void Left(int);
        void Up(int);
        void Dive(int);
        void Strafe_Right(int);
        void Strafe_Left(int);
        void Roll_Right(int);
        void Roll_Left(int);
        void Forward();
        void Reverse();
        void Right();
        void Left();
        void Up();
        void Dive();
        void Strafe_Right();
        void Strafe_Left();
        void Roll_Right();
        void Roll_Left();

        void Stop();
        void Setup();
    private:
        bool ARMED = false;
        int POWER = 0;
        Servo T1;
        Servo T2;
        Servo T3;
        Servo T4;
        Servo T5;
        Servo T6;
};
#endif

