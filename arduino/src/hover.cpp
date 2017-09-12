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
#include "hover.h"

double H_Setpoint;
double H_Input;
double H_Output;
double H_aggKp=2;
double H_aggKi=0.1;
double H_aggKd=.5;
double H_consKp=4;
double H_consKi=0.05;
double H_consKd=0.25;
    
PID H_PID(&H_Input, &H_Output, &H_Setpoint, H_consKp, H_consKi, H_consKd, DIRECT);

//
// On
//
void Hover::On() {
     active = true;
}

//
// Off
//
void Hover::Off() {
     active = false;
}


//
// Active
//
bool Hover::Active() {
    return active;
}

//
// Depth
//
void Hover::Depth(int d) {
     hover_depth = d;
}
 
//
// Loop
//
void Hover::Loop(Thruster &T, Sensor &S) {
    //
    // Hover
    //
    H_Input = S.Depth();
    H_Setpoint = hover_depth;

    double gap = abs(H_Setpoint - H_Input);

    Serial.print("Hover_Gap:");
    Serial.println(gap);

    if (gap < 10) {
        H_PID.SetTunings(H_consKp, H_consKi, H_consKd);
    } else {
        H_PID.SetTunings(H_aggKp, H_aggKi, H_aggKd);
    }

    H_PID.Compute();

    Serial.print("Hover_Input:");
    Serial.println(H_Input);
    Serial.print("Hover_Setpoint:");
    Serial.println(H_Setpoint);
    Serial.print("Hover_Output:");
    Serial.println(H_Output);
    if (S.Depth() > hover_depth) {
        Serial.println("Hover_Up:");
        Serial.println(H_Output);
        T.Up(H_Output);
    } else if (S.Depth() < hover_depth) {
        Serial.println("Hover_Dive:");
        Serial.println(H_Output);
        T.Dive(H_Output);
    } else {
        T.Stop();
        H_Output = 0;
        Serial.print("Hover_Output:");
        Serial.println(H_Output);
    }
}

//
// Setup
//
void Hover::Setup() {
    H_PID.SetMode(AUTOMATIC);
    H_PID.SetOutputLimits(0, 30);
}

