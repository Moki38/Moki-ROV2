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
#ifndef _ROV_H
#define _ROV_H

class T100 {
    public:
        Servo esc;
        bool once;        // Run only once
        int step = 1;     // Number of step to take before we reach the new current.
        int current;      // Current power (0-100)
        int target;       // Target power (0-100)
};

class Rov {
    public:
        T100 T1;
        T100 T2;
        T100 T3;
        T100 T4;
        T100 T5;
        T100 T6;
        Servo L1;
        Servo L2;
        Servo L3;
        Servo L4;
        Servo CX;
        Servo CY;
        float Heading;
        float Roll;
        float Pitch;
        float Current;
        float Amps;
        float Depth;
        float Altitude;
        float Pressure;
        float Temp_IN;
        float Temp_OUT;
        bool Armed;
        bool Hover;
        bool Pilot;
        int Power;
};

#endif
