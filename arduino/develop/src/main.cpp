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

#include "main.h"

Motor motor;
Config config;
Light light;
Sensor sensor;
Comms comms;
Camera camera;

void setup() {
  int timeout = millis();

//
// Init comms
//
  comms.setup();
//
// Wait for comms to be available
//
  while ((timeout <= millis() + 10000)) {
    if (comms.Available()) {
      config.setup();
      motor.setup();
      light.setup();
      camera.setup();
      sensor.setup();
      timeout = -1;
    } else {
      timeout = millis();
    }
  }
//  if (timeout > 0) {
//  }
}

void loop() {
//
// Run at "fixed" times
//  
  int time = millis();
//
// Every 1000 μs run the sensor loop
//
  if ((time >= (sensor.time() + 1000)) || (time < sensor.time())) {
    sensor.loop();
  }
//
// Every 250 μs run the motor loop.
//
  if ((time >= (motor.time() + 250)) || (time < motor.time())) {
    motor.loop();
  }


}

