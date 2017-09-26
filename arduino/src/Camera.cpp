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

#include "Camera.h"

//
// Move_X
//
void Camera::Move_X(Rov &R, int x) {
#ifdef CAMERAX_PWM
    R.CX.writeMicroseconds(x);
    Serial.print("Camx:");
    Serial.println(x);
#endif
}

//
// Move_Y
//
void Camera::Move_Y(Rov &R, int y) {
#ifdef CAMERAY_PWM
    R.CY.writeMicroseconds(y);
    Serial.print("Camy:");
    Serial.println(y);
#endif
}

//
// Center
//
void Camera::Center(Rov &R) {
#ifdef CAMERAX_PWM
    R.CX.attach(CAMERAX_PIN);
    R.CX.writeMicroseconds(CAMERAX_NEUTRAL);
    Serial.print("Camx:");
    Serial.println(CAMERAX_NEUTRAL);
#endif
#ifdef CAMERAY_PWM
    R.CY.attach(CAMERAY_PIN);
    R.CY.writeMicroseconds(CAMERAY_NEUTRAL);
    Serial.print("Camy:");
    Serial.println(CAMERAY_NEUTRAL);
#endif
}

//
// Setup
//
void Camera::Setup(Rov &R) {
#ifdef CAMERAX_PWM
    R.CX.attach(CAMERAX_PIN);
    R.CX.writeMicroseconds(CAMERAX_NEUTRAL);
    Serial.print("Camx:");
    Serial.println(CAMERAX_NEUTRAL);
#endif
#ifdef CAMERAY_PWM
    R.CY.attach(CAMERAY_PIN);
    R.CY.writeMicroseconds(CAMERAY_NEUTRAL);
    Serial.print("Camy:");
    Serial.println(CAMERAY_NEUTRAL);
#endif
}
