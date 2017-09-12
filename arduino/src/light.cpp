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
#include "light.h"

//
// Off
//
void Light::Off() {
#ifdef LIGHT1_PWM
    L1.writeMicroseconds(LIGHT1_OFF);
#endif
    Serial.print("Light_1:");
    Serial.println(0);
#ifdef LIGHT2_PWM
    L2.writeMicroseconds(LIGHT2_OFF);
#endif
    Serial.println(0);
#ifdef LIGHT3_PWM
    L3.writeMicroseconds(LIGHT3_OFF);
#endif
    Serial.print("Light_3:");
    Serial.println(0);
#ifdef LIGHT4_PWM
    L4.writeMicroseconds(LIGHT4_OFF);
#endif
    Serial.print("Light_4:");
    Serial.println(0);
}

//
// On
//
void Light::On() {
#ifdef LIGHT1_PWM
    L1.writeMicroseconds(LIGHT1_ON);
#endif
    Serial.print("Light_1:");
    Serial.println(1);
#ifdef LIGHT2_PWM
    L2.writeMicroseconds(LIGHT2_ON);
#endif
    Serial.println(1);
#ifdef LIGHT3_PWM
    L3.writeMicroseconds(LIGHT3_ON);
#endif
    Serial.print("Light_3:");
    Serial.println(1);
#ifdef LIGHT4_PWM
    L4.writeMicroseconds(LIGHT4_ON);
#endif
    Serial.print("Light_4:");
    Serial.println(1);
}

//
// Setup
//
void Light::Setup() {
#ifdef LIGHT1_PWM
    L1.attach(LIGHT1_PIN);
    L1.writeMicroseconds(LIGHT1_OFF);
#endif
    Serial.print("Light_1:");
    Serial.println(0);
#ifdef LIGHT2_PWM
    L2.attach(LIGHT2_PIN);
    L2.writeMicroseconds(LIGHT2_OFF);
#endif
    Serial.print("Light_2:");
    Serial.println(0);
#ifdef LIGHT3_PWM
    L3.attach(LIGHT3_PIN);
    L3.writeMicroseconds(LIGHT3_OFF);
#endif
    Serial.print("Light_3:");
    Serial.println(0);
#ifdef LIGHT4_PWM
    L4.attach(LIGHT4_PIN);
    L4.writeMicroseconds(LIGHT4_OFF);
#endif
    Serial.print("Light_4:");
    Serial.println(0);
}

