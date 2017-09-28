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
#ifndef _MOVEMENT_H
#define _MOVEMENT_H

#include <Arduino.h>
#include <Servo.h>
#include "Config.h"
#include "Rov.h"
#include "Thruster.h"

#define MOVEMENT_STEPS          5

#define MOVEMENT_FORWARD	0b0000000001
#define MOVEMENT_REVERSE	0b0000000010
#define MOVEMENT_RIGHT		0b0000000100
#define MOVEMENT_LEFT		0b0000001000
#define MOVEMENT_DIVE		0b0000010000
#define MOVEMENT_UP		0b0000100000
#define MOVEMENT_STRAFE_RIGHT	0b0001000000
#define MOVEMENT_STRAFE_LEFT	0b0010000000
#define MOVEMENT_ROLL_RIGHT	0b0100000000
#define MOVEMENT_ROLL_LEFT	0b1000000000

class Movement : public Thruster {
    public:
        void Compute(Rov&);
        void Run(Rov&, int, int);
        void Forward(Rov&);
        void Forward(Rov&, int);
        void Reverse(Rov&);
        void Reverse(Rov&, int);
        void Right(Rov&);
        void Right(Rov&, int);
        void Left(Rov&);
        void Left(Rov&, int);
        void Up(Rov&);
        void Up(Rov&, int);
        void Dive(Rov&);
        void Dive(Rov&, int);
        void Strafe_Right(Rov&);
        void Strafe_Right(Rov&, int);
        void Strafe_Left(Rov&);
        void Strafe_Left(Rov&, int);
        void Roll_Right(Rov&);
        void Roll_Right(Rov&, int);
        void Roll_Left(Rov&);
        void Roll_Left(Rov&, int);

        void Stop(Rov&);
        void Setup(Rov&);
    private:
};
#endif

