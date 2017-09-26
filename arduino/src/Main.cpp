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

#include "Main.h"

//
// Serial vars
//
String serial_command = "";
String command = "";
String value_string = "";
int value = 0;
boolean command_complete = false;

Rov R;
Thruster T;
Light L;
Camera C;
Sensor S;
Hover H;
Pilot P;

//
// Timeout vars
//
int thruster_time = 0;
int ping_time = 0;
int pong_time = 0;

void setup()
{
    unsigned int timeout = millis();

    T.Setup(R);
    L.Setup(R);
    C.Setup(R);
    S.Setup(R);
    P.Setup(R);
    H.Setup(R);
 
    // Init serial communication
    serial_command.reserve(200);
    Serial.begin(115200);

    // Wait for Serial port to be available
    while ((timeout <= millis() + 10000)) {
        if (Serial) {
            Serial.println("ARDUINO READY");
            timeout = -1;
            ping_time = millis();
            pong_time = millis();
        } else {
            timeout = millis();
        }
    }
    //  if (timeout > 0) {
    //  }

}

void pingpong_loop()
{
    pong_time = millis();
    Serial.println("Pong:0");
    if (pong_time >= (ping_time + 2500)) {
        T.Stop(R);
        L.Off(R);
        R.Pilot = false;
        R.Hover = false;
        R.Power = 0;
        R.Armed = false;
        Serial.println("Timeout:1");
    }
}

void loop()
{
    //
    // Run at "fixed" times
    //
    int time = millis();
    //
    // Every 500 μs run the sensor loop
    //
    if ((time >= (S.Time() + 500)) || (time < S.Time())) {
        S.Loop(R);
    }
    //
    // Every 2500 μs run the ping loop
    //
    if (time >= (pong_time + 2500)) {
        pingpong_loop();
    }
    //
    // Every 150 μs run the thruster loop.
    //
    if ((time >= (thruster_time + 150)) || (time < thruster_time)) {
        if (R.Pilot == true) {
            P.Loop(R);
        }
        if (R.Hover == true) {
            H.Loop(R);
        }
        thruster_time = millis();
    }

    //
    // Incoming Serial Command from PI.
    //
    if (command_complete) {
        serial_command.trim();
        int pos = serial_command.indexOf(':');
        command = serial_command.substring(0, pos);
        value_string = serial_command.substring(pos + 1);
        value = value_string.toInt();

        if (command != "Ping") {
            Serial.print("Command: ");
            Serial.print(command);
            Serial.print(" Value: ");
            Serial.println(value);
        }

        if (command == "ARM") {
            R.Armed = true;

        } else if (command == "Ping") {
            ping_time = millis();

        } else if (command == "Disarm") {
            T.Stop(R);
            L.Off(R);
            R.Power = 0;
            R.Armed = false;

        } else if (command == "Stop") {
            T.Stop(R);

        } else if (command == "Pilot") {
            if (value >= 400) {
                R.Pilot = false;
            } else {
                R.Pilot = true;
                P.Heading(value);
            }

        } else if (command == "Hover") {
            if (value >= 0) {
                R.Hover = true;
                H.Depth(value);
            } else {
                R.Hover = false;
            }

        } else if (command == "Power") {
            R.Power = value;

            // Right Left Reverse Forward Strafe_r Strafe_l Dive Up
        } else if (command == "Forward") {
            T.Forward(R);
        } else if (command == "Reverse") {
            T.Reverse(R);
        } else if (command == "Right") {
            T.Right(R);
        } else if (command == "Left") {
            T.Left(R);
        } else if (command == "Dive") {
            T.Dive(R);
        } else if (command == "Up") {
            T.Up(R);
        } else if (command == "Strafe_r") {
            T.Strafe_Right(R);
        } else if (command == "Strafe_l") {
            T.Strafe_Left(R);
        } else if (command == "Roll_r") {
            T.Roll_Right(R);
        } else if (command == "Roll_l") {
            T.Roll_Left(R);
        } else if (command == "Light_1") {
            if (value == 0) {
                L.Off(R);
            } else {
                L.On(R);
            }
        } else if (command == "Light_2") {
            if (value == 0) {
                L.Off(R);
            } else {
                L.On(R);
            }
        } else if (command == "Light_3") {
            if (value == 0) {
                L.Off(R);
            } else {
                L.On(R);
            }
        } else if (command == "Light_4") {
            if (value == 0) {
                L.Off(R);
            } else {
                L.On(R);
            }

        } else if (command == "Camx") {
            C.Move_X(R, value);
        } else if (command == "Camy") {
            C.Move_Y(R, value);
        }

        serial_command = "";
        command_complete = false;
    }
}

void serialEvent()
{
    while (Serial.available()) {
        // get the new byte:
        char inChar = (char) Serial.read();
        // add it to the inputString:
        serial_command += inChar;
        // if the incoming character is a newline, set a flag
        // so the main loop can do something about it:
        if (inChar == '\n') {
            command_complete = true;
        }
    }
}
