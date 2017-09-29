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
#include "Light.h"

//
// Off
//
void Light::Off(Rov &R) {
#ifdef LIGHT1_PWM
    R.L1.writeMicroseconds(LIGHT1_OFF);
#endif
#ifdef LIGHT1_RELAY
    digitalWrite(LIGHT1_PIN, LOW);  
#endif
    Serial.print("Light_1:");
    Serial.println(0);
#ifdef LIGHT2_PWM
    R.L2.writeMicroseconds(LIGHT2_OFF);
#endif
#ifdef LIGHT2_RELAY
    digitalWrite(LIGHT2_PIN, LOW);  
#endif
    Serial.print("Light_2:");
    Serial.println(0);
#ifdef LIGHT3_PWM
    R.L3.writeMicroseconds(LIGHT3_OFF);
#endif
#ifdef LIGHT3_RELAY
    digitalWrite(LIGHT3_PIN, LOW);  
#endif
    Serial.print("Light_3:");
    Serial.println(0);
#ifdef LIGHT4_PWM
    R.L4.writeMicroseconds(LIGHT4_OFF);
#endif
#ifdef LIGHT4_RELAY
    digitalWrite(LIGHT4_PIN, LOW);  
#endif
    Serial.print("Light_4:");
    Serial.println(0);
}

//
// On
//
void Light::On(Rov &R) {
#ifdef LIGHT1_PWM
    R.L1.writeMicroseconds(LIGHT1_ON);
#endif
#ifdef LIGHT1_RELAY
    digitalWrite(LIGHT1_PIN, HIGH);  
#endif
    Serial.print("Light_1:");
    Serial.println(1);
#ifdef LIGHT2_PWM
    R.L2.writeMicroseconds(LIGHT2_ON);
#endif
#ifdef LIGHT2_RELAY
    digitalWrite(LIGHT2_PIN, HIGH);  
#endif
    Serial.print("Light_2:");
    Serial.println(1);
#ifdef LIGHT3_PWM
    R.L3.writeMicroseconds(LIGHT3_ON);
#endif
#ifdef LIGHT3_RELAY
    digitalWrite(LIGHT3_PIN, HIGH);  
#endif
    Serial.print("Light_3:");
    Serial.println(1);
#ifdef LIGHT4_PWM
    R.L4.writeMicroseconds(LIGHT4_ON);
#endif
#ifdef LIGHT4_RELAY
    digitalWrite(LIGHT4_PIN, HIGH);  
#endif
    Serial.print("Light_4:");
    Serial.println(1);
}

//
// Setup
//
void Light::Setup(Rov &R) {
#ifdef LIGHT1_PWM
    R.L1.attach(LIGHT1_PIN);
    R.L1.writeMicroseconds(LIGHT1_OFF);
#endif
#ifdef LIGHT1_RELAY
    pinMode(LIGHT1_PIN, OUTPUT); 
#endif
    Serial.print("Light_1:");
    Serial.println(0);
#ifdef LIGHT2_PWM
    R.L2.attach(LIGHT2_PIN);
    R.L2.writeMicroseconds(LIGHT2_OFF);
#endif
#ifdef LIGHT2_RELAY
    pinMode(LIGHT2_PIN, OUTPUT); 
#endif
    Serial.print("Light_2:");
    Serial.println(0);
#ifdef LIGHT3_PWM
    R.L3.attach(LIGHT3_PIN);
    R.L3.writeMicroseconds(LIGHT3_OFF);
#endif
#ifdef LIGHT3_RELAY
    pinMode(LIGHT3_PIN, OUTPUT); 
#endif
    Serial.print("Light_3:");
    Serial.println(0);
#ifdef LIGHT4_PWM
    R.L4.attach(LIGHT4_PIN);
    R.L4.writeMicroseconds(LIGHT4_OFF);
#endif
#ifdef LIGHT4_RELAY
    pinMode(LIGHT4_PIN, OUTPUT); 
#endif
    Serial.print("Light_4:");
    Serial.println(0);
}

