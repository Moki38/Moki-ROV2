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
#include "Pilot.h"

double P_Setpoint;
double P_Input;
double P_Output;
double P_aggKp=2;
double P_aggKi=0.1;
double P_aggKd=.5;
double P_consKp=4;
double P_consKi=0.05;
double P_consKd=0.25;
    
PID P_PID(&P_Input, &P_Output, &P_Setpoint, P_consKp, P_consKi, P_consKd, DIRECT);

//
// Set Pilot Heading
//
void Pilot::Heading(int h) {
     pilot_heading = h;
}
 
//
// Loop
//
void Pilot::Loop(Rov &R) {
    //
    // Pilot
    //
    int direction = 0;

    P_Input = R.Heading + 360;
    P_Setpoint = pilot_heading + 360;

    double gap = abs(P_Setpoint - P_Input);

    Serial.print("Pilot_Gap:");
    Serial.println(gap);

    if (P_Input > P_Setpoint) {
        direction = 2;
        P_Input = pilot_heading + 360;
        P_Setpoint = R.Heading + 360;
    }
    if (P_Input < P_Setpoint) {
        direction = 1;
    }


//        if (gap < 10) {
            P_PID.SetTunings(P_consKp, P_consKi, P_consKd);
//        } else {
//            P_PID.SetTunings(aggKp, aggKi, aggKd);
//        }
    P_PID.Compute();

    Serial.print("Pilot_Heading_Input:");
    Serial.println(P_Input);
    Serial.print("Pilot_Heading_Output:");
    Serial.println(P_Output);
    Serial.print("Pilot_Heading_Setpoint:");
    Serial.println(P_Setpoint);

    if (P_Output > 30) {
            //    Serial.print("DEBUG_PILOT_HEADING_OUTPUT_MAX:");
            //    Serial.println(P_Output);
         P_Output = 0;
    };

    if (direction == 2) {
        Serial.print("Pilot_Heading_Output_Left:");
        Serial.println(P_Output);
        Thruster::Left(R, P_Output);

    } else if (direction == 1) {
        Serial.print("Pilot_Heading_Output_Right:");
        Serial.println(P_Output);
        Thruster::Right(R, P_Output);
    } else {
        Thruster::Stop(R);
        P_Output = 0;
    }
}

//
// Setup
//
void Pilot::Setup(Rov &R) {
    R.Pilot = false;
    P_PID.SetMode(AUTOMATIC);
    P_PID.SetOutputLimits(0, 20);
}

