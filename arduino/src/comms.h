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

#include <Wire.h>

#ifndef _COMMS_H
#define _COMMS_H

//
// Comms Configuration defines
//
#define COMMS_I2C               // Enable I2C comms
#define COMMS_SERIAL            // Enable Serial comms
#define COMMS_SERIAL_DEBUG      // Enable Serial debug messages

String serial_command = "";
boolean command_complete = false;

class Comms {
public:
	void setup();
	void loop();
private:
	int x = 0;
};

#endif /* _COMMS_H */


