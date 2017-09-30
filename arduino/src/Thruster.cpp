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

void Thruster::Loop(Rov &R) {

//
// Are we Armed?
//
   if (R.Armed) {

//
// Thruster 1
//
#if defined THRUSTER1_PWM 
         R.T1.esc.writeMicroseconds(THRUSTER1_NEUTRAL + (R.T1.current * 4));
         Serial.print("Thruster_1: ");
         Serial.println(R.T1.current);
#endif
//
// Thruster 2
//
#if defined THRUSTER2_PWM 
         R.T2.esc.writeMicroseconds(THRUSTER2_NEUTRAL + (R.T2.current * 4));
         Serial.print("Thruster_2: ");
         Serial.println(R.T2.current);
#endif
//
// Thruster 3
//
#if defined THRUSTER3_PWM 
         R.T3.esc.writeMicroseconds(THRUSTER3_NEUTRAL + (R.T3.current * 4));
         Serial.print("Thruster_3: ");
         Serial.println(R.T3.current);
#endif
//
// Thruster 4
//
#if defined THRUSTER4_PWM 
         R.T4.esc.writeMicroseconds(THRUSTER4_NEUTRAL + (R.T4.current * 4));
         Serial.print("Thruster_4: ");
         Serial.println(R.T4.current);
#endif
//
// Thruster 5
//
#if defined THRUSTER5_PWM 
         R.T5.esc.writeMicroseconds(THRUSTER5_NEUTRAL + (R.T5.current * 4));
         Serial.print("Thruster_5: ");
         Serial.println(R.T5.current);
#endif
//
// Thruster 6
//
#if defined THRUSTER6_PWM 
         R.T6.esc.writeMicroseconds(THRUSTER6_NEUTRAL + (R.T6.current * 4));
         Serial.print("Thruster_6: ");
         Serial.println(R.T6.current);
#endif

    } // ARMED
} // Thruster::Loop


//
// Thruster::Stop
// 
void Thruster::Stop(Rov &R)
{

    R.T1.target = 0;
    R.T1.current = 0;
#ifdef THRUSTER1_PWM    
    R.T1.esc.writeMicroseconds(THRUSTER1_NEUTRAL);
    Serial.print("Thruster_1:");
    Serial.println(0);
#endif

    R.T2.target = 0;
    R.T2.current = 0;
#ifdef THRUSTER2_PWM    
    R.T2.esc.writeMicroseconds(THRUSTER2_NEUTRAL);
    Serial.print("Thruster_2:");
    Serial.println(0);
#endif

    R.T3.target = 0;
    R.T3.current = 0;
#ifdef THRUSTER3_PWM    
    R.T3.esc.writeMicroseconds(THRUSTER3_NEUTRAL);
    Serial.print("Thruster_3:");
    Serial.println(0);
#endif

    R.T4.target = 0;
    R.T4.current = 0;
#ifdef THRUSTER4_PWM    
    R.T4.esc.writeMicroseconds(THRUSTER4_NEUTRAL);
    Serial.print("Thruster_4:");
    Serial.println(0);
#endif

    R.T5.target = 0;
    R.T5.current = 0;
#ifdef THRUSTER5_PWM    
    R.T5.esc.writeMicroseconds(THRUSTER5_NEUTRAL);
    Serial.print("Thruster_5:");
    Serial.println(0);
#endif

    R.T6.target = 0;
    R.T6.current = 0;
#ifdef THRUSTER6_PWM    
    R.T6.esc.writeMicroseconds(THRUSTER6_NEUTRAL);
    Serial.print("Thruster_6:");
    Serial.println(0);
#endif

} // Thruster::Stop

//
// Thruster::Setup
//
void Thruster::Setup(Rov &R)
{
    R.Power = 0;

    R.T1.target = 0;
    R.T1.current = 0;
#ifdef THRUSTER1_PWM    
    R.T1.esc.attach(THRUSTER1_PIN);
    R.T1.esc.writeMicroseconds(THRUSTER1_NEUTRAL);
    Serial.print("Thruster_1:");
    Serial.println(0);
#endif

    R.T2.target = 0;
    R.T2.current = 0;
#ifdef THRUSTER2_PWM    
    R.T2.esc.attach(THRUSTER2_PIN);
    R.T2.esc.writeMicroseconds(THRUSTER2_NEUTRAL);
    Serial.print("Thruster_2:");
    Serial.println(0);
#endif

    R.T3.target = 0;
    R.T3.current = 0;
#ifdef THRUSTER3_PWM    
    R.T3.esc.attach(THRUSTER3_PIN);
    R.T3.esc.writeMicroseconds(THRUSTER3_NEUTRAL);
    Serial.print("Thruster_3:");
    Serial.println(0);
#endif

    R.T4.target = 0;
    R.T4.current = 0;
#ifdef THRUSTER4_PWM    
    R.T4.esc.attach(THRUSTER4_PIN);
    R.T4.esc.writeMicroseconds(THRUSTER4_NEUTRAL);
    Serial.print("Thruster_4:");
    Serial.println(0);
#endif

    R.T5.target = 0;
    R.T5.current = 0;
#ifdef THRUSTER5_PWM    
    R.T5.esc.attach(THRUSTER5_PIN);
    R.T5.esc.writeMicroseconds(THRUSTER5_NEUTRAL);
    Serial.print("Thruster_5:");
    Serial.println(0);
#endif

    R.T6.target = 0;
    R.T6.current = 0;
#ifdef THRUSTER6_PWM    
    R.T6.esc.attach(THRUSTER6_PIN);
    R.T6.esc.writeMicroseconds(THRUSTER6_NEUTRAL);
    Serial.print("Thruster_6:");
    Serial.println(0);
#endif

} // Thruster::Setup
