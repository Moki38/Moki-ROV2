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

#include "comms.h"

#ifdef COMMS_SERIAL
void serialEvent() {

  int pos = 0;

//  serial_command.reserve(200);
  while (Serial.available()) {

    byte inChar = (byte)Serial.read();
    _buffer[pos] = inChar;

    // if the incoming character is a newline, set a flag
    if (inChar == '\n') {
      return;
    } else {
      pos++;
    }
  }
}
#endif

#ifdef COMMS_I2C
void receiveEvent(int howmany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}
#endif

void Comms::setup() {
#ifdef COMMS_I2C
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
#endif

#ifdef COMMS_SERIAL
  Serial.begin(115200);
#endif

}

boolean Comms::Available() {
  if (Serial) {
    return true;
  } else {
    return false;
  }
}

void Comms::loop() {
}
