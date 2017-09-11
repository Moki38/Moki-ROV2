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

#include "thruster.h"

void Thruster::Power(int p) {
    POWER=p;
}

int Thruster::Power() {
    return POWER;
}

void Thruster::Arm(bool b) {
    ARMED=b;
}

bool Thruster::Arm() {
    return ARMED;
}

void Thruster::Run(int THRUSTER_POWER, int DIRECTION) {
//
// Armed
//
     if (ARMED) {

//
// Thruster 1
//
         if (DIRECTION & THRUSTER1_DIR) {
             if (DIRECTION & THRUSTER1_REVERSE) {
#if defined THRUSTER1_PWM 
                T1.writeMicroseconds(THRUSTER1_NEUTRAL-(4*THRUSTER_POWER));
#endif
                Serial.print("THRUSTER_1: ");
                Serial.println(-THRUSTER_POWER);
             } else {
#if defined THRUSTER1_PWM 
                T1.writeMicroseconds(THRUSTER1_NEUTRAL+(4*THRUSTER_POWER));
#endif
                Serial.print("THRUSTER_1: ");
                Serial.println(THRUSTER_POWER);
             }
         }

//
// Thruster 2
//
         if (DIRECTION & THRUSTER2_DIR) {
             if (DIRECTION & THRUSTER2_REVERSE) {
#if defined THRUSTER2_PWM 
                T1.writeMicroseconds(THRUSTER2_NEUTRAL-(4*THRUSTER_POWER));
#endif
                Serial.print("THRUSTER_2: ");
                Serial.println(-THRUSTER_POWER);
             } else {
#if defined THRUSTER2_PWM 
                T1.writeMicroseconds(THRUSTER2_NEUTRAL+(4*THRUSTER_POWER));
#endif
                Serial.print("THRUSTER_2: ");
                Serial.println(THRUSTER_POWER);
             }
         }

//
// Thruster 3
//
         if (DIRECTION & THRUSTER3_DIR) {
             if (DIRECTION & THRUSTER3_REVERSE) {
#if defined THRUSTER3_PWM 
                T1.writeMicroseconds(THRUSTER3_NEUTRAL-(4*THRUSTER_POWER));
#endif
                Serial.print("THRUSTER_3: ");
                Serial.println(-THRUSTER_POWER);
             } else {
#if defined THRUSTER3_PWM 
                T1.writeMicroseconds(THRUSTER3_NEUTRAL+(4*THRUSTER_POWER));
#endif
                Serial.print("THRUSTER_3: ");
                Serial.println(THRUSTER_POWER);
             }
         }

//
// Thruster 4
//
         if (DIRECTION & THRUSTER4_DIR) {
             if (DIRECTION & THRUSTER4_REVERSE) {
#if defined THRUSTER4_PWM 
                T1.writeMicroseconds(THRUSTER4_NEUTRAL-(4*THRUSTER_POWER));
#endif
                Serial.print("THRUSTER_4: ");
                Serial.println(-THRUSTER_POWER);
             } else {
#if defined THRUSTER4_PWM 
                T1.writeMicroseconds(THRUSTER4_NEUTRAL+(4*THRUSTER_POWER));
#endif
                Serial.print("THRUSTER_4: ");
                Serial.println(THRUSTER_POWER);
             }
         }

//
// Thruster 5
//
         if (DIRECTION & THRUSTER5_DIR) {
             if (DIRECTION & THRUSTER5_REVERSE) {
#if defined THRUSTER5_PWM 
                T1.writeMicroseconds(THRUSTER5_NEUTRAL-(4*THRUSTER_POWER));
#endif
                Serial.print("THRUSTER_5: ");
                Serial.println(-THRUSTER_POWER);
             } else {
#if defined THRUSTER5_PWM 
                T1.writeMicroseconds(THRUSTER5_NEUTRAL+(4*THRUSTER_POWER));
#endif
                Serial.print("THRUSTER_5: ");
                Serial.println(THRUSTER_POWER);
             }
         }

//
// Thruster 6
//
         if (DIRECTION & THRUSTER6_DIR) {
             if (DIRECTION & THRUSTER6_REVERSE) {
#if defined THRUSTER6_PWM 
                T1.writeMicroseconds(THRUSTER6_NEUTRAL-(4*THRUSTER_POWER));
#endif
                Serial.print("THRUSTER_6: ");
                Serial.println(-THRUSTER_POWER);
             } else {
#if defined THRUSTER6_PWM 
                T1.writeMicroseconds(THRUSTER6_NEUTRAL+(4*THRUSTER_POWER));
#endif
                Serial.print("THRUSTER_6: ");
                Serial.println(THRUSTER_POWER);
             }
        }

    } // ARMED
} // Thruster::Run

//
// Thruster::Stop
// 
void Thruster::Stop()
{
#ifdef THRUSTER1_PWM    
    T1.writeMicroseconds(THRUSTER1_NEUTRAL);
#endif
    Serial.print("Thruster_1:");
    Serial.println(0);
#ifdef THRUSTER2_PWM    
    T2.writeMicroseconds(THRUSTER2_NEUTRAL);
#endif
    Serial.print("Thruster_2:");
    Serial.println(0);
#ifdef THRUSTER3_PWM    
    T3.writeMicroseconds(THRUSTER3_NEUTRAL);
#endif
    Serial.print("Thruster_3:");
    Serial.println(0);
#ifdef THRUSTER4_PWM    
    T4.writeMicroseconds(THRUSTER4_NEUTRAL);
#endif
    Serial.print("Thruster_4:");
    Serial.println(0);
#ifdef THRUSTER5_PWM    
    T5.writeMicroseconds(THRUSTER5_NEUTRAL);
#endif
    Serial.print("Thruster_5:");
    Serial.println(0);
#ifdef THRUSTER6_PWM    
    T6.writeMicroseconds(THRUSTER6_NEUTRAL);
#endif
    Serial.print("Thruster_6:");
    Serial.println(0);
}

//
// Thruster::Setup
//
void Thruster::Setup()
{
#ifdef THRUSTER1_PWM    
    T1.attach(THRUSTER1_PIN);
    T1.writeMicroseconds(THRUSTER1_NEUTRAL);
#endif
    Serial.print("Thruster_1:");
    Serial.println(0);
#ifdef THRUSTER2_PWM    
    T2.attach(THRUSTER2_PIN);
    T2.writeMicroseconds(THRUSTER2_NEUTRAL);
#endif
    Serial.print("Thruster_2:");
    Serial.println(0);
#ifdef THRUSTER3_PWM    
    T3.attach(THRUSTER3_PIN);
    T3.writeMicroseconds(THRUSTER3_NEUTRAL);
#endif
    Serial.print("Thruster_3:");
    Serial.println(0);
#ifdef THRUSTER4_PWM    
    T4.attach(THRUSTER4_PIN);
    T4.writeMicroseconds(THRUSTER4_NEUTRAL);
#endif
    Serial.print("Thruster_4:");
    Serial.println(0);
#ifdef THRUSTER5_PWM    
    T5.attach(THRUSTER5_PIN);
    T5.writeMicroseconds(THRUSTER5_NEUTRAL);
#endif
    Serial.print("Thruster_5:");
    Serial.println(0);
#ifdef THRUSTER6_PWM    
    T6.attach(THRUSTER6_PIN);
    T6.writeMicroseconds(THRUSTER6_NEUTRAL);
#endif
    Serial.print("Thruster_6:");
    Serial.println(0);
}
