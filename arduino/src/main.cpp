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

String serial_command = "";
String command = "";
String value_string = "";
int value = 0;
boolean command_complete = false;

int sensor_time = 0;
int motor_time = 0;
int ping_time = 0;
int pong_time = 0;
int power = 0;

int pilot = 0;
int pilot_heading = 0;
int hover = 0;
float hover_depth = 0;

void setup() {
  unsigned int timeout = millis();

  motor_setup();
  light_setup();
  camera_setup();
  sensor_setup();

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

void sensor_loop() {
  Serial.print("Time:");
  sensor_time = millis();
  Serial.println(sensor_time);

  Serial.print("Volt:");
  Serial.println(current_get());

  Serial.print("Amps:");
  Serial.println(amp_get());

  depth_loop();
  Serial.print("Pressure:");
  Serial.println(pressure_get());
  Serial.print("Temperature:");
  Serial.println(temp_get());
  Serial.print("Depth:");
  Serial.println(depth_get());
  Serial.print("Altitude:");
  Serial.println(alt_get());

  imu_loop();
  Serial.print("X:");
  Serial.println(imu_X(), 4);
  Serial.print("Y:");
  Serial.println(imu_Y(), 4);
  Serial.print("Z:");
  Serial.println(imu_Z(), 4);
  Serial.print("Heading:");
  Serial.println(imu_heading(), 4);
  Serial.print("Roll:");
  Serial.println(imu_roll(), 4);
  Serial.print("Pitch:");
  Serial.println(imu_pitch(), 4);
}

void hover_loop() {
//
// Hover
//
      if (hover == true) {
        if (depth_get() > hover_depth+1) {
          motor_up(30);
	Serial.print("Motor_5:");
	Serial.println(power);
	Serial.print("Motor_6:");
	Serial.println(power);
        } else if (depth_get() < hover_depth-1) {
          motor_dive(30);
	Serial.print("Motor_5:");
	Serial.println(power);
	Serial.print("Motor_6:");
	Serial.println(power);
        } else {
          motor_stop();
	Serial.print("Motor_5:");
	Serial.println(0);
	Serial.print("Motor_6:");
	Serial.println(0);
        }
      }
}
void pilot_loop() {
//
// Pilot
//
      if (pilot == true) {
//	Serial.println("Debug_Pilot");
        if (imu_heading() > pilot_heading+1) {
//	  Serial.println("Debug_Pilot_Left");
          motor_left(10);
	Serial.print("Motor_1:");
	Serial.println(power);
	Serial.print("Motor_2:");
	Serial.println(power);
	Serial.print("Motor_3:");
	Serial.println(power);
	Serial.print("Motor_4:");
	Serial.println(power);
        } else if (imu_heading() < pilot_heading-1) {
//	  Serial.println("Debug_Pilot_Right");
          motor_right(10);
	Serial.print("Motor_1:");
	Serial.println(power);
	Serial.print("Motor_2:");
	Serial.println(power);
	Serial.print("Motor_3:");
	Serial.println(power);
	Serial.print("Motor_4:");
	Serial.println(power);
        } else {
          motor_stop();
	Serial.print("Motor_1:");
	Serial.println(0);
	Serial.print("Motor_2:");
	Serial.println(0);
	Serial.print("Motor_3:");
	Serial.println(0);
	Serial.print("Motor_4:");
	Serial.println(0);
        }
      }
}

void motor_loop() {
  motor_time = millis();
//  motor_stop();
}

void pingpong_loop() {
  Serial.println("PONG");
  if (pong_time >= (ping_time + 2500)) {
    motor_stop();
  }
}

void loop() {
//
// Run at "fixed" times
//
  int time = millis();
//
// Every 500 μs run the sensor loop
//
  if ((time >= (sensor_time + 500)) || (time < sensor_time)) {
    sensor_loop();
  }
//
// Every 2500 μs run the ping loop
//
  if (time >= (pong_time + 2500)) {
    pingpong_loop();
  }
//
// Every 150 μs run the motor loop.
//
  if ((time >= (motor_time + 150)) || (time < motor_time)) {
    pilot_loop();
    hover_loop();
    motor_loop();
  }

//
// Command
//
   if (command_complete) {
      serial_command.trim();
      int pos = serial_command.indexOf(':');
      command = serial_command.substring(0,pos);
      value_string = serial_command.substring(pos+1);
      value = value_string.toInt();

      Serial.print("Command: ");
      Serial.print(command);
      Serial.print(" Value: ");
      Serial.println(value);

      if (command == "ARM") {
           motor_arm(true);
      } else if (command == "PING") {
         ping_time = millis();
      } else if (command == "DISARM") {
	   motor_stop();
           motor_arm(false);

      } else if (command == "Stop") {
           motor_stop();
   	   Serial.print("Motor_1:");
	   Serial.println(0);
	   Serial.print("Motor_2:");
	   Serial.println(0);
	   Serial.print("Motor_3:");
	   Serial.println(0);
	   Serial.print("Motor_4:");
	   Serial.println(0);
	   Serial.print("Motor_5:");
	   Serial.println(0);
	   Serial.print("Motor_6:");
	   Serial.println(0);

      } else if (command == "Pilot") {
           if (value >= 0) {
             pilot = true;
             pilot_heading = value;
           } else {
             pilot = false;
           }
      } else if (command == "Hover") {
           if (value >= 0) {
             hover = true;
             hover_depth = value;
           } else {
             hover = false;
           }
      } else if (command == "Power") {
           power = value;

// Right Left Reverse Forward Strafe_r Strafe_l Dive Up
      } else if (command == "Forward") {
        motor_forward(power);
//	Serial.println("Debug_Forward");
	Serial.print("Motor_1:");
	Serial.println(-power);
	Serial.print("Motor_2:");
	Serial.println(power);
	Serial.print("Motor_3:");
	Serial.println(power);
	Serial.print("Motor_4:");
	Serial.println(-power);
        
      } else if (command == "Reverse") {
        motor_reverse(power);
//  	Serial.println("Debug_Reverse");
	Serial.print("Motor_1:");
	Serial.println(power);
	Serial.print("Motor_2:");
	Serial.println(-power);
	Serial.print("Motor_3:");
	Serial.println(-power);
	Serial.print("Motor_4:");
	Serial.println(power);

      } else if (command == "Right") {
	motor_right(power);
	Serial.print("Motor_1:");
	Serial.println(power);
	Serial.print("Motor_2:");
	Serial.println(-power);
	Serial.print("Motor_3:");
	Serial.println(power);
	Serial.print("Motor_4:");
	Serial.println(-power);

      } else if (command == "Left") {
	motor_left(power);
	Serial.print("Motor_1:");
	Serial.println(-power);
	Serial.print("Motor_2:");
	Serial.println(power);
	Serial.print("Motor_3:");
	Serial.println(-power);
	Serial.print("Motor_4:");
	Serial.println(power);

      } else if (command == "Dive") {
	motor_dive(power);
	Serial.print("Motor_5:");
	Serial.println(power);
	Serial.print("Motor_6:");
	Serial.println(-power);

      } else if (command == "Up") {
	motor_up(power);
	Serial.print("Motor_5:");
	Serial.println(-power);
	Serial.print("Motor_6:");
	Serial.println(power);

      } else if (command == "Strafe_r") {
	motor_strafe_right(power);
	Serial.print("Motor_1:");
	Serial.println(power);
	Serial.print("Motor_2:");
	Serial.println(power);
	Serial.print("Motor_3:");
	Serial.println(power);
	Serial.print("Motor_4:");
	Serial.println(power);

      } else if (command == "Strafe_l") {
	motor_strafe_left(power);
	Serial.print("Motor_1:");
	Serial.println(-power);
	Serial.print("Motor_2:");
	Serial.println(-power);
	Serial.print("Motor_3:");
	Serial.println(-power);
	Serial.print("Motor_4:");
	Serial.println(-power);

      } else if (command == "Roll_r") {
	motor_roll_right(power);
	Serial.print("Motor_5:");
	Serial.println(-power);
	Serial.print("Motor_6:");
	Serial.println(power);

      } else if (command == "Roll_l") {
	motor_roll_left(power);
	Serial.print("Motor_5:");
	Serial.println(power);
	Serial.print("Motor_6:");
	Serial.println(-power);

      } else if (command == "Light1") {
         if (value == LIGHT1_OFF) {
           light_off();
         } else {
           light_on();
         }
      } else if (command == "Light2") {
         if (value == LIGHT1_OFF) {
           light_off();
         } else {
           light_on();
         }
      } else if (command == "Camx") {
         camera_movex(value);
      } else if (command == "Camy") {
         camera_movey(value);
      }

      serial_command = "";
      command_complete = false;
    }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    serial_command += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      command_complete = true;
    }
  }
}

