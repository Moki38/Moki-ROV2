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
#include "Rov.h"

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
        void Loop(Rov&);

        void Stop(Rov&);
        void Setup(Rov&);
    private:
};
#endif

