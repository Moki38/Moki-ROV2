#include "config.h"

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "MS5837.h"

unsigned long time;
int MOTOR_ARM = 0;
int FOUND_BNO = 0;
int FOUND_MS5837 = 0;
int FOUND_A180 = 0;
int READY = 0;
String serial_command = "";
String command = "";
String value_string = "";
int value = 0;
boolean command_complete = false;

int sensor_time = 0;
int power = 0;

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;
Servo motor5;
Servo motor6;
Servo light1;
Servo light2;
Servo camx;
Servo camy;

//
// Attopilot 180
//

int VRaw; //This will store our raw ADC data
int IRaw;
float VFinal; //This will store the converted data
float IFinal;

MS5837 sensor;

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(55);

/**************************************************************************/
/*
    Displays some basic information on this sensor from the unified
    sensor API sensor_t type (see Adafruit_Sensor for more information)
*/
/**************************************************************************/
void displaySensorDetails(void)
{
  sensor_t sensor;
  bno.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" xxx");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" xxx");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" xxx");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

/**************************************************************************/
/*
    Display some basic info about the sensor status
*/
/**************************************************************************/
void displaySensorStatus(void)
{
  /* Get the system status values (mostly for debugging purposes) */
  uint8_t system_status, self_test_results, system_error;
  system_status = self_test_results = system_error = 0;
  bno.getSystemStatus(&system_status, &self_test_results, &system_error);

  /* Display the results in the Serial Monitor */
  Serial.println("");
  Serial.print("System Status: 0x");
  Serial.println(system_status, HEX);
  Serial.print("Self Test:     0x");
  Serial.println(self_test_results, HEX);
  Serial.print("System Error:  0x");
  Serial.println(system_error, HEX);
  Serial.println("");
  delay(500);
}

/**************************************************************************/
/*
    Display sensor calibration status
*/
/**************************************************************************/
void displayCalStatus(void)
{
  /* Get the four calibration values (0..3) */
  /* Any sensor data reporting 0 should be ignored, */
  /* 3 means 'fully calibrated" */
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);

  /* The data should be ignored until the system calibration is > 0 */
//  if (!system)
//  {
//    Serial.print("! ");
//  }

  /* Display the individual values */
  Serial.print("Sys:");
  Serial.println(system, DEC);
  Serial.print("Gyro:");
  Serial.println(gyro, DEC);
  Serial.print("Accel:");
  Serial.println(accel, DEC);
  Serial.print("Mag:");
  Serial.println(mag, DEC);
}

void motor_stop() {
  motor1.writeMicroseconds(1500);
  motor2.writeMicroseconds(1500);
  motor3.writeMicroseconds(1500);
  motor4.writeMicroseconds(1500);
}

void setup() {
  delay (6000); 
  motor1.attach(MOTOR1_PIN); 
  motor1.writeMicroseconds(1500);
  delay (200); 
  motor2.attach(MOTOR2_PIN); 
  motor2.writeMicroseconds(1500);
  delay (200); 
  motor3.attach(MOTOR3_PIN); 
  motor3.writeMicroseconds(1500);
  delay (200); 
  motor4.attach(MOTOR4_PIN); 
  motor4.writeMicroseconds(1500);
  
  delay (200); 
  light1.attach(LIGHT1_PIN); 
  light1.writeMicroseconds(1000);
  delay (200); 
  light2.attach(LIGHT2_PIN); 
  light2.writeMicroseconds(1000);

  delay (200); 
  camx.attach(CAMX_PIN); 
  camx.writeMicroseconds(1500);
  delay (200); 

  serial_command.reserve(200);

  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  Wire.begin();

  sensor.init();
  sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)

  /* Initialise the sensor */
  if(bno.begin())
  {
     FOUND_BNO = 1; 
  }

  delay(1000);
  /* Display some basic information on this sensor */
  if (FOUND_BNO) {
    displaySensorDetails();
  /* Optional: Display current status */
    displaySensorStatus();

    bno.setExtCrystalUse(true);
  }

  sensor_time = millis();
  Serial.println("Ready!");
  READY = 1;
}

void sensor_run() {
  Serial.print("Time:");
  sensor_time = millis();
  Serial.println(sensor_time);

  VRaw = analogRead(A0);
  IRaw = analogRead(A1);

  if (VRaw < 400) {
  //Conversion
    VFinal = VRaw/12.99; //180 Amp board  
    IFinal = IRaw/3.7; //180 Amp board

    Serial.print("Volt:");
    Serial.println(VFinal);
    Serial.print("Amps:");
    Serial.println(IFinal);
  }

  sensor.read();

  Serial.print("Pressure:"); 
  Serial.println(sensor.pressure()); 
  Serial.print("Temperature:"); 
  Serial.println(sensor.temperature()); 
  Serial.print("Depth:"); 
  Serial.println(sensor.depth()); 
  Serial.print("Altitude:"); 
  Serial.println(sensor.altitude()); 

  if (FOUND_BNO) {
  // Get a new sensor event 
    sensors_event_t event;
    bno.getEvent(&event);

  // Display the floating point data 
    Serial.print("X:");
    Serial.println(event.orientation.x, 4);
    Serial.print("Y:");
    Serial.println(event.orientation.y, 4);
    Serial.print("Z:");
    Serial.println(event.orientation.z, 4);

  // Optional: Display calibration status 
    displayCalStatus();

  // Optional: Display sensor status (debug only) 
    //displaySensorStatus();

  }
}

void loop() {
  if (READY) {
    int time = millis();
    if ((time >= (sensor_time + 1000)) || (time < sensor_time)) { 
      sensor_run();
    }

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
           MOTOR_ARM = 1;
      } else if (command == "DISARM") {
           MOTOR_ARM = 0;
      } else if (command == "Stop") {
           motor_stop();
      } else if (command == "Power") {
           power = value;

// Right Left Reverse Forward Strafe_r Strafe_l Dive Up

      } else if (command == "Forward") {
         if (MOTOR_ARM) {
           motor2.writeMicroseconds(1500+(4*power));  
           motor4.writeMicroseconds(1500+(4*power));  
         }
      } else if (command == "Reverse") {
         if (MOTOR_ARM) {
           motor2.writeMicroseconds(1500-(4*power));  
           motor4.writeMicroseconds(1500-(4*power));  
         }
      } else if (command == "Right") {
         if (MOTOR_ARM) {
           motor2.writeMicroseconds(1500-(4*power));  
           motor4.writeMicroseconds(1500+(4*power));  
         }
      } else if (command == "Left") {
         if (MOTOR_ARM) {
           motor2.writeMicroseconds(1500+(4*power));  
           motor4.writeMicroseconds(1500-(4*power));  
         }
      } else if (command == "Dive") {
         if (MOTOR_ARM) {
           motor1.writeMicroseconds(1500-(4*power));  
           motor3.writeMicroseconds(1500-(4*power));  
         }
      } else if (command == "Up") {
         if (MOTOR_ARM) {
           motor1.writeMicroseconds(1500+(4*power));  
           motor3.writeMicroseconds(1500+(4*power));  
         }
      } else if (command == "Strafe_r") {
         if (MOTOR_ARM) {
           motor1.writeMicroseconds(1500+(4*power));  
           motor3.writeMicroseconds(1500-(4*power));  
         }
      } else if (command == "Strafe_l") {
         if (MOTOR_ARM) {
           motor1.writeMicroseconds(1500-(4*power));  
           motor3.writeMicroseconds(1500+(4*power));  
         }
      } else if (command == "Light1") {
         light1.writeMicroseconds(value);  
      } else if (command == "Light2") {
         light2.writeMicroseconds(value);  
      } else if (command == "Camx") {
         camx.writeMicroseconds(value);  
      } else if (command == "Camy") {
         camy.writeMicroseconds(value);  
      }

      // clear the string:
      serial_command = "";
      command_complete = false;
    }
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
 
