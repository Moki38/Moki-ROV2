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

#include "Thruster.h"

void Thruster::Run(Rov &R, int DIRECTION, int THRUSTER_POWER) {
//
// Are we Armed?
//
     if (R.Armed) {

//
// Thruster 1
//
         if (DIRECTION & THRUSTER1_DIR) {
             if (DIRECTION & THRUSTER1_REVERSE) {
#if defined THRUSTER1_PWM 
                R.T1.writeMicroseconds(THRUSTER1_NEUTRAL-(4*THRUSTER_POWER));
#endif
                Serial.print("Thruster_1: ");
                Serial.println(-THRUSTER_POWER);
             } else {
#if defined THRUSTER1_PWM 
                R.T1.writeMicroseconds(THRUSTER1_NEUTRAL+(4*THRUSTER_POWER));
#endif
                Serial.print("Thruster_1: ");
                Serial.println(THRUSTER_POWER);
             }
         }

//
// Thruster 2
//
         if (DIRECTION & THRUSTER2_DIR) {
             if (DIRECTION & THRUSTER2_REVERSE) {
#if defined THRUSTER2_PWM 
                R.T2.writeMicroseconds(THRUSTER2_NEUTRAL-(4*THRUSTER_POWER));
#endif
                Serial.print("Thruster_2: ");
                Serial.println(-THRUSTER_POWER);
             } else {
#if defined THRUSTER2_PWM 
                R.T2.writeMicroseconds(THRUSTER2_NEUTRAL+(4*THRUSTER_POWER));
#endif
                Serial.print("Thruster_2: ");
                Serial.println(THRUSTER_POWER);
             }
         }

//
// Thruster 3
//
         if (DIRECTION & THRUSTER3_DIR) {
             if (DIRECTION & THRUSTER3_REVERSE) {
#if defined THRUSTER3_PWM 
                R.T3.writeMicroseconds(THRUSTER3_NEUTRAL-(4*THRUSTER_POWER));
#endif
                Serial.print("Thruster_3: ");
                Serial.println(-THRUSTER_POWER);
             } else {
#if defined THRUSTER3_PWM 
                R.T3.writeMicroseconds(THRUSTER3_NEUTRAL+(4*THRUSTER_POWER));
#endif
                Serial.print("Thruster_3: ");
                Serial.println(THRUSTER_POWER);
             }
         }

//
// Thruster 4
//
         if (DIRECTION & THRUSTER4_DIR) {
             if (DIRECTION & THRUSTER4_REVERSE) {
#if defined THRUSTER4_PWM 
                R.T4.writeMicroseconds(THRUSTER4_NEUTRAL-(4*THRUSTER_POWER));
#endif
                Serial.print("Thruster_4: ");
                Serial.println(-THRUSTER_POWER);
             } else {
#if defined THRUSTER4_PWM 
                R.T4.writeMicroseconds(THRUSTER4_NEUTRAL+(4*THRUSTER_POWER));
#endif
                Serial.print("Thruster_4: ");
                Serial.println(THRUSTER_POWER);
             }
         }

//
// Thruster 5
//
         if (DIRECTION & THRUSTER5_DIR) {
             if (DIRECTION & THRUSTER5_REVERSE) {
#if defined THRUSTER5_PWM 
                R.T5.writeMicroseconds(THRUSTER5_NEUTRAL-(4*THRUSTER_POWER));
#endif
                Serial.print("Thruster_5: ");
                Serial.println(-THRUSTER_POWER);
             } else {
#if defined THRUSTER5_PWM 
                R.T5.writeMicroseconds(THRUSTER5_NEUTRAL+(4*THRUSTER_POWER));
#endif
                Serial.print("Thruster_5: ");
                Serial.println(THRUSTER_POWER);
             }
         }

//
// Thruster 6
//
         if (DIRECTION & THRUSTER6_DIR) {
             if (DIRECTION & THRUSTER6_REVERSE) {
#if defined THRUSTER6_PWM 
                R.T6.writeMicroseconds(THRUSTER6_NEUTRAL-(4*THRUSTER_POWER));
#endif
                Serial.print("Thruster_6: ");
                Serial.println(-THRUSTER_POWER);
             } else {
#if defined THRUSTER6_PWM 
                R.T6.writeMicroseconds(THRUSTER6_NEUTRAL+(4*THRUSTER_POWER));
#endif
                Serial.print("Thruster_6: ");
                Serial.println(THRUSTER_POWER);
             }
        }

    } // ARMED
} // Thruster::Run


//
// Forward
//
void Thruster::Forward(Rov &R) {
    Run(R, THRUSTER_FORWARD, R.Power);
}
void Thruster::Forward(Rov &R, int Power) {
    Run(R, THRUSTER_FORWARD, Power);
}

//
// Reverse
//
void Thruster::Reverse(Rov &R) {
    Run(R, THRUSTER_REVERSE, R.Power);
}
void Thruster::Reverse(Rov &R, int Power) {
    Run(R, THRUSTER_REVERSE, Power);
}

//
// Right
//
void Thruster::Right(Rov &R) {
    Run(R, THRUSTER_RIGHT, R.Power);
}
void Thruster::Right(Rov &R, int Power) {
    Run(R, THRUSTER_RIGHT, Power);
}

//
// Left
//
void Thruster::Left(Rov &R) {
    Run(R, THRUSTER_LEFT, R.Power);
}
void Thruster::Left(Rov &R, int Power) {
    Run(R, THRUSTER_LEFT, Power);
}

//
// Up
//
void Thruster::Up(Rov &R) {
    Run(R, THRUSTER_UP, R.Power);
}
void Thruster::Up(Rov &R, int Power) {
    Run(R, THRUSTER_UP, Power);
}

//
// Dive
//
void Thruster::Dive(Rov &R) {
    Run(R, THRUSTER_DIVE, R.Power);
}
void Thruster::Dive(Rov &R, int Power) {
    Run(R, THRUSTER_DIVE, Power);
}

//
// Strafe_Right
//
void Thruster::Strafe_Right(Rov &R) {
    Run(R, THRUSTER_STRAFE_RIGHT, R.Power);
}
void Thruster::Strafe_Right(Rov &R, int Power) {
    Run(R, THRUSTER_STRAFE_RIGHT, Power);
}

//
// Strafe_Left
//
void Thruster::Strafe_Left(Rov &R) {
    Run(R, THRUSTER_STRAFE_LEFT, R.Power);
}
void Thruster::Strafe_Left(Rov &R, int Power) {
    Run(R, THRUSTER_STRAFE_LEFT, Power);
}

//
// Roll_Right
//
void Thruster::Roll_Right(Rov &R) {
    Run(R, THRUSTER_ROLL_RIGHT, R.Power);
}
void Thruster::Roll_Right(Rov &R, int Power) {
    Run(R, THRUSTER_ROLL_RIGHT, Power);
}

//
// Roll_Left
//
void Thruster::Roll_Left(Rov &R) {
    Run(R, THRUSTER_ROLL_LEFT, R.Power);
}
void Thruster::Roll_Left(Rov &R, int Power) {
    Run(R, THRUSTER_ROLL_LEFT, Power);
}

//
// Thruster::Stop
// 
void Thruster::Stop(Rov &R)
{
//    R.Power = 0;
#ifdef THRUSTER1_PWM    
    R.T1.writeMicroseconds(THRUSTER1_NEUTRAL);
#endif
    Serial.print("Thruster_1:");
    Serial.println(0);
#ifdef THRUSTER2_PWM    
    R.T2.writeMicroseconds(THRUSTER2_NEUTRAL);
#endif
    Serial.print("Thruster_2:");
    Serial.println(0);
#ifdef THRUSTER3_PWM    
    R.T3.writeMicroseconds(THRUSTER3_NEUTRAL);
#endif
    Serial.print("Thruster_3:");
    Serial.println(0);
#ifdef THRUSTER4_PWM    
    R.T4.writeMicroseconds(THRUSTER4_NEUTRAL);
#endif
    Serial.print("Thruster_4:");
    Serial.println(0);
#ifdef THRUSTER5_PWM    
    R.T5.writeMicroseconds(THRUSTER5_NEUTRAL);
#endif
    Serial.print("Thruster_5:");
    Serial.println(0);
#ifdef THRUSTER6_PWM    
    R.T6.writeMicroseconds(THRUSTER6_NEUTRAL);
#endif
    Serial.print("Thruster_6:");
    Serial.println(0);
}

//
// Thruster::Setup
//
void Thruster::Setup(Rov &R)
{
    R.Power = 0;

#ifdef THRUSTER1_PWM    
    R.T1.attach(THRUSTER1_PIN);
    R.T1.writeMicroseconds(THRUSTER1_NEUTRAL);
#endif
    Serial.print("Thruster_1:");
    Serial.println(0);
#ifdef THRUSTER2_PWM    
    R.T2.attach(THRUSTER2_PIN);
    R.T2.writeMicroseconds(THRUSTER2_NEUTRAL);
#endif
    Serial.print("Thruster_2:");
    Serial.println(0);
#ifdef THRUSTER3_PWM    
    R.T3.attach(THRUSTER3_PIN);
    R.T3.writeMicroseconds(THRUSTER3_NEUTRAL);
#endif
    Serial.print("Thruster_3:");
    Serial.println(0);
#ifdef THRUSTER4_PWM    
    R.T4.attach(THRUSTER4_PIN);
    R.T4.writeMicroseconds(THRUSTER4_NEUTRAL);
#endif
    Serial.print("Thruster_4:");
    Serial.println(0);
#ifdef THRUSTER5_PWM    
    R.T5.attach(THRUSTER5_PIN);
    R.T5.writeMicroseconds(THRUSTER5_NEUTRAL);
#endif
    Serial.print("Thruster_5:");
    Serial.println(0);
#ifdef THRUSTER6_PWM    
    R.T6.attach(THRUSTER6_PIN);
    R.T6.writeMicroseconds(THRUSTER6_NEUTRAL);
#endif
    Serial.print("Thruster_6:");
    Serial.println(0);
}
