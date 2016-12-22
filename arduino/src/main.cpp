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

int motor_time = 0;
int sensor_time = 0;
int power = 0;

struct Motor {
  int proto;		// proto:  1:'PWM', 2:I2C
  int addr;		// pin: 3 or i2c address
  int neutral;		// neutral: 1500,
  int min;		// min: 1100,
  int max;		// max: 1900,
  int reverse;		// reverse: true 
  Servo servo;
  Arduino_I2C_ESC i2c;
  float voltage;
  float current;
  float temperature;
  int16_t rpm;
  unsigned char direction;	// 0 1 2 4 8 16 32 64 128
};

struct Motor Motor1;
struct Motor Motor2;
struct Motor Motor3;
struct Motor Motor4;

boolean CONFIG_MOTOR = false;

struct Light {
  int proto;		// proto:  1:'PWM', 2:I2C
  int addr;		// pin: 3 or i2c address
  int on;		// min: 1100,
  int off;		// max: 1900,
  Servo servo;
};

struct Light Light1;
struct Light Light2;

boolean CONFIG_LIGHT = false;

struct Camera {
  int proto;		// proto:  1:'PWM', 2:I2C
  int addr;		// pin: 3 or i2c address
  int neutral;		// neutral: 1500,
  int min;		// min: 1100,
  int max;		// max: 1900,
  Servo servo;
};

struct Camera CamX;
struct Camera CamY;

boolean CONFIG_CAMERA = false;

struct Sensor {
  int proto;
  int addr;
  int type;
};

struct Sensor IMU;
struct Sensor DEPTH;
struct Sensor CURRENT;
struct Sensor AMP;

//
// Attopilot 180
//

int VRaw; //This will store our raw ADC data
int IRaw;
float VFinal; //This will store the converted data
float IFinal;

MS5837 MS5837_sensor;

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
  if (Motor1.proto == 'PWM') {
    Motor1.servo.writeMicroseconds(Motor1.neutral);
  }
  if (Motor1.proto == 'I2C') {
    Motor1.i2c.setPWM(Motor1.neutral);
  }

  Motor2.servo.writeMicroseconds(Motor2.neutral);
  Motor3.servo.writeMicroseconds(Motor3.neutral);
  Motor4.servo.writeMicroseconds(Motor4.neutral);
  Serial.print("Stop:");
  Serial.println(1);
}

void motor_setup() {
  motor_time = millis();

  if (Motor1.proto == 'PWM') {
    Motor1.servo.attach(Motor1.addr);
    Motor1.servo.writeMicroseconds(Motor1.neutral);
  }
  if (Motor1.proto == 'I2C') {
    Motor1.i2c(Motor1.addr);
    Motor1.i2c.setPWM(Motor1.neutral);
  }
//  delay (200); 
  Motor2.servo.attach(Motor2.addr);
  Motor2.servo.writeMicroseconds(Motor2.neutral);
//  delay (200); 
  Motor3.servo.attach(Motor3.addr);
  Motor3.servo.writeMicroseconds(Motor3.neutral);
 // delay (200); 
  Motor4.servo.attach(Motor4.addr);
  Motor4.servo.writeMicroseconds(Motor4.neutral);
 // delay (200); 
}

void light_setup() {
  Light1.servo.attach(Light1.addr);
  Light1.servo.writeMicroseconds(Light1.off);
//  delay (200); 
  Light2.servo.attach(Light2.addr);
  Light2.servo.writeMicroseconds(Light2.off);
//  delay (200); 
}

void cam_setup() {
  CamX.servo.attach(CamX.addr);
  CamX.servo.writeMicroseconds(CamX.neutral);
 // delay (200); 

}

void imu_setup() {
  if (IMU.type == 1) {
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
  }
}

void depth_setup() {
  if (CURRENT.type == 1) {
    MS5837_sensor.init();
    MS5837_sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)
  }
}

void current_setup() {
}

void amp_setup() {
}

void sensor_setup() {

  depth_setup();
  imu_setup();
  current_setup();
  amp_setup();

  sensor_time = millis();

}

void setup() {
  delay (6000); 
  serial_command.reserve(200);
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  Wire.begin();

  Serial.println("Ready!");
  READY = 1;
}

void current_run() {
  if (CURRENT.type == 1) {
    VRaw = analogRead(CURRENT.addr);
    if (VRaw < 400) {
    //Conversion
      VFinal = VRaw/12.99; //180 Amp board  
      Serial.print("Volt:");
      Serial.println(VFinal);
    }
  }
}

void amp_run() {
  if (AMP.type == 1) {
    IRaw = analogRead(AMP.addr);
    if (VRaw < 400) {
      //Conversion
      IFinal = IRaw/3.7; //180 Amp board
      Serial.print("Amps:");
      Serial.println(IFinal);
    }
  }
}

void depth_run() {
  if (DEPTH.type == 1) {
    MS5837_sensor.read();

    Serial.print("Pressure:"); 
    Serial.println(MS5837_sensor.pressure()); 
    Serial.print("Temperature:"); 
    Serial.println(MS5837_sensor.temperature()); 
    Serial.print("Depth:"); 
    Serial.println(MS5837_sensor.depth()); 
    Serial.print("Altitude:"); 
    Serial.println(MS5837_sensor.altitude()); 
  }
}

void imu_run() {
  if (IMU.type == 1) {
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
}

void motor_run() {
  motor_time = millis();
}

void sensor_run() {
  Serial.print("Time:");
  sensor_time = millis();
  Serial.println(sensor_time);

  current_run();
  amp_run();

  depth_run();

  imu_run();

}

void loop() {
  if (READY) {
    int time = millis();
    if ((time >= (sensor_time + 1000)) || (time < sensor_time)) { 
      sensor_run();
    }
    if ((time >= (motor_time + 250)) || (time < motor_time)) { 
      motor_run();
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
           if (Motor1.direction & 0x01) {
             Serial.print("Motor_1:");
             if (Motor1.reverse & 0x01) {
               Motor1.servo.writeMicroseconds(Motor1.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor1.servo.writeMicroseconds(Motor1.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor2.direction & 0x01) {
             Serial.print("Motor_2:");
             if (Motor2.reverse & 0x01) {
               Motor2.servo.writeMicroseconds(Motor2.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor2.servo.writeMicroseconds(Motor2.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor3.direction & 0x01) {
             Serial.print("Motor_3:");
             if (Motor3.reverse & 0x01) {
               Motor3.servo.writeMicroseconds(Motor3.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor3.servo.writeMicroseconds(Motor3.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor4.direction & 0x01) {
             Serial.print("Motor_4:");
             if (Motor4.reverse & 0x01) {
               Motor4.servo.writeMicroseconds(Motor4.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor4.servo.writeMicroseconds(Motor4.neutral+(4*power));
               Serial.println(power);
             }
           } 
         }
      } else if (command == "Reverse") {
         if (MOTOR_ARM) {
           if (Motor1.direction & 0x02) {
             Serial.print("Motor_1:");
             if (Motor1.reverse & 0x02) {
               Motor1.servo.writeMicroseconds(Motor1.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor1.servo.writeMicroseconds(Motor1.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor2.direction & 0x02) {
             Serial.print("Motor_2:");
             if (Motor2.reverse & 0x02) {
               Motor2.servo.writeMicroseconds(Motor2.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor2.servo.writeMicroseconds(Motor2.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor3.direction & 0x02) {
             Serial.print("Motor_3:");
             if (Motor3.reverse & 0x02) {
               Motor3.servo.writeMicroseconds(Motor3.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor3.servo.writeMicroseconds(Motor3.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor4.direction & 0x02) {
             Serial.print("Motor_4:");
             if (Motor4.reverse & 0x02) {
               Motor4.servo.writeMicroseconds(Motor4.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor4.servo.writeMicroseconds(Motor4.neutral+(4*power));
               Serial.println(power);
             }
           } 
         }
      } else if (command == "Right") {
         if (MOTOR_ARM) {
           if (Motor1.direction & 0x04) {
             Serial.print("Motor_1:");
             if (Motor1.reverse & 0x04) {
               Motor1.servo.writeMicroseconds(Motor1.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor1.servo.writeMicroseconds(Motor1.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor2.direction & 0x04) {
             Serial.print("Motor_2:");
             if (Motor2.reverse & 0x04) {
               Motor2.servo.writeMicroseconds(Motor2.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor2.servo.writeMicroseconds(Motor2.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor3.direction & 0x04) {
             Serial.print("Motor_3:");
             if (Motor3.reverse & 0x04) {
               Motor3.servo.writeMicroseconds(Motor3.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor3.servo.writeMicroseconds(Motor3.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor4.direction & 0x04) {
             Serial.print("Motor_4:");
             if (Motor4.reverse & 0x04) {
               Motor4.servo.writeMicroseconds(Motor4.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor4.servo.writeMicroseconds(Motor4.neutral+(4*power));
               Serial.println(power);
             }
           } 
         }
      } else if (command == "Left") {
         if (MOTOR_ARM) {
           if (Motor1.direction & 0x08) {
             Serial.print("Motor_1:");
             if (Motor1.reverse & 0x08) {
               Motor1.servo.writeMicroseconds(Motor1.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor1.servo.writeMicroseconds(Motor1.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor2.direction & 0x08) {
             Serial.print("Motor_2:");
             if (Motor2.reverse & 0x08) {
               Motor2.servo.writeMicroseconds(Motor2.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor2.servo.writeMicroseconds(Motor2.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor3.direction & 0x08) {
             Serial.print("Motor_3:");
             if (Motor3.reverse & 0x08) {
               Motor3.servo.writeMicroseconds(Motor3.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor3.servo.writeMicroseconds(Motor3.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor4.direction & 0x08) {
             Serial.print("Motor_4:");
             if (Motor4.reverse & 0x08) {
               Motor4.servo.writeMicroseconds(Motor4.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor4.servo.writeMicroseconds(Motor4.neutral+(4*power));
               Serial.println(power);
             }
           } 
         }
      } else if (command == "Dive") {
         if (MOTOR_ARM) {
           if (Motor1.direction & 0x10) {
             Serial.print("Motor_1:");
             if (Motor1.reverse & 0x10) {
               Motor1.servo.writeMicroseconds(Motor1.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor1.servo.writeMicroseconds(Motor1.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor2.direction & 0x10) {
             Serial.print("Motor_2:");
             if (Motor2.reverse & 0x10) {
               Motor2.servo.writeMicroseconds(Motor2.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor2.servo.writeMicroseconds(Motor2.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor3.direction & 0x10) {
             Serial.print("Motor_3:");
             if (Motor3.reverse & 0x10) {
               Motor3.servo.writeMicroseconds(Motor3.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor3.servo.writeMicroseconds(Motor3.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor4.direction & 0x10) {
             Serial.print("Motor_4:");
             if (Motor4.reverse & 0x10) {
               Motor4.servo.writeMicroseconds(Motor4.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor4.servo.writeMicroseconds(Motor4.neutral+(4*power));
               Serial.println(power);
             }
           } 
         }
      } else if (command == "Up") {
         if (MOTOR_ARM) {
           if (Motor1.direction & 0x20) {
             Serial.print("Motor_1:");
             if (Motor1.reverse & 0x20) {
               Motor1.servo.writeMicroseconds(Motor1.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor1.servo.writeMicroseconds(Motor1.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor2.direction & 0x20) {
             Serial.print("Motor_2:");
             if (Motor2.reverse & 0x20) {
               Motor2.servo.writeMicroseconds(Motor2.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor2.servo.writeMicroseconds(Motor2.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor3.direction & 0x20) {
             Serial.print("Motor_3:");
             if (Motor3.reverse & 0x20) {
               Motor3.servo.writeMicroseconds(Motor3.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor3.servo.writeMicroseconds(Motor3.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor4.direction & 0x20) {
             Serial.print("Motor_4:");
             if (Motor4.reverse & 0x20) {
               Motor4.servo.writeMicroseconds(Motor4.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor4.servo.writeMicroseconds(Motor4.neutral+(4*power));
               Serial.println(power);
             }
           } 
         }
      } else if (command == "Strafe_r") {
         if (MOTOR_ARM) {
           if (Motor1.direction & 0x40) {
             Serial.print("Motor_1:");
             if (Motor1.reverse & 0x40) {
               Motor1.servo.writeMicroseconds(Motor1.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor1.servo.writeMicroseconds(Motor1.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor2.direction & 0x40) {
             Serial.print("Motor_2:");
             if (Motor2.reverse & 0x40) {
               Motor2.servo.writeMicroseconds(Motor2.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor2.servo.writeMicroseconds(Motor2.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor3.direction & 0x40) {
             Serial.print("Motor_3:");
             if (Motor3.reverse & 0x40) {
               Motor3.servo.writeMicroseconds(Motor3.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor3.servo.writeMicroseconds(Motor3.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor4.direction & 0x40) {
             Serial.print("Motor_4:");
             if (Motor4.reverse & 0x40) {
               Motor4.servo.writeMicroseconds(Motor4.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor4.servo.writeMicroseconds(Motor4.neutral+(4*power));
               Serial.println(power);
             }
           } 
         }
      } else if (command == "Strafe_l") {
         if (MOTOR_ARM) {
           if (Motor1.direction & 0x80) {
             Serial.print("Motor_1:");
             if (Motor1.reverse & 0x80) {
               Motor1.servo.writeMicroseconds(Motor1.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor1.servo.writeMicroseconds(Motor1.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor2.direction & 0x80) {
             Serial.print("Motor_2:");
             if (Motor2.reverse & 0x80) {
               Motor2.servo.writeMicroseconds(Motor2.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor2.servo.writeMicroseconds(Motor2.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor3.direction & 0x80) {
             Serial.print("Motor_3:");
             if (Motor3.reverse & 0x80) {
               Motor3.servo.writeMicroseconds(Motor3.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor3.servo.writeMicroseconds(Motor3.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor4.direction & 0x80) {
             Serial.print("Motor_4:");
             if (Motor4.reverse & 0x80) {
               Motor4.servo.writeMicroseconds(Motor4.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor4.servo.writeMicroseconds(Motor4.neutral+(4*power));
               Serial.println(power);
             }
           } 
         }
      } else if (command == "Roll_r") {
         if (MOTOR_ARM) {
           if (Motor1.direction & 0x40) {
             Serial.print("Motor_1:");
             if (Motor1.reverse & 0x40) {
               Motor1.servo.writeMicroseconds(Motor1.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor1.servo.writeMicroseconds(Motor1.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor2.direction & 0x40) {
             Serial.print("Motor_2:");
             if (Motor2.reverse & 0x40) {
               Motor2.servo.writeMicroseconds(Motor2.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor2.servo.writeMicroseconds(Motor2.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor3.direction & 0x40) {
             Serial.print("Motor_3:");
             if (Motor3.reverse & 0x40) {
               Motor3.servo.writeMicroseconds(Motor3.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor3.servo.writeMicroseconds(Motor3.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor4.direction & 0x40) {
             Serial.print("Motor_4:");
             if (Motor4.reverse & 0x40) {
               Motor4.servo.writeMicroseconds(Motor4.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor4.servo.writeMicroseconds(Motor4.neutral+(4*power));
               Serial.println(power);
             }
           } 
         }
      } else if (command == "Roll_l") {
         if (MOTOR_ARM) {
           if (Motor1.direction & 0x80) {
             Serial.print("Motor_1:");
             if (Motor1.reverse & 0x80) {
               Motor1.servo.writeMicroseconds(Motor1.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor1.servo.writeMicroseconds(Motor1.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor2.direction & 0x80) {
             Serial.print("Motor_2:");
             if (Motor2.reverse & 0x80) {
               Motor2.servo.writeMicroseconds(Motor2.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor2.servo.writeMicroseconds(Motor2.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor3.direction & 0x80) {
             Serial.print("Motor_3:");
             if (Motor3.reverse & 0x80) {
               Motor3.servo.writeMicroseconds(Motor3.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor3.servo.writeMicroseconds(Motor3.neutral+(4*power));
               Serial.println(power);
             }
           }
           if (Motor4.direction & 0x80) {
             Serial.print("Motor_4:");
             if (Motor4.reverse & 0x80) {
               Motor4.servo.writeMicroseconds(Motor4.neutral-(4*power));
               Serial.println(-power);
             } else {
               Motor4.servo.writeMicroseconds(Motor4.neutral+(4*power));
               Serial.println(power);
             }
           } 
         }
      } else if (command == "Light1") {
         Light1.servo.writeMicroseconds(value);  
      } else if (command == "Light2") {
         Light2.servo.writeMicroseconds(value);  
      } else if (command == "Camx") {
         CamX.servo.writeMicroseconds(value);  
      } else if (command == "Camy") {
         CamY.servo.writeMicroseconds(value);  

// Config part
      } else if (command == "CFG_M1_PROTO") {
         Motor1.proto = value;  
      } else if (command == "CFG_M1_ADDR") {
         Motor1.addr = value;  
      } else if (command == "CFG_M1_N") {
         Motor1.neutral = value;  
      } else if (command == "CFG_M1_MIN") {
         Motor1.min = value;  
      } else if (command == "CFG_M1_MAX") {
         Motor1.max = value;  
      } else if (command == "CFG_M1_REV") {
         Motor1.reverse = value;  
      } else if (command == "CFG_M1_DIR") {
         Motor1.direction = value;  
      } else if (command == "CFG_M2_PROTO") {
         Motor2.proto = value;  
      } else if (command == "CFG_M2_ADDR") {
         Motor2.addr = value;  
      } else if (command == "CFG_M2_N") {
         Motor2.neutral = value;  
      } else if (command == "CFG_M2_MIN") {
         Motor2.min = value;  
      } else if (command == "CFG_M2_MAX") {
         Motor2.max = value;  
      } else if (command == "CFG_M2_REV") {
         Motor2.reverse = value;  
      } else if (command == "CFG_M2_DIR") {
         Motor2.direction = value;  
      } else if (command == "CFG_M3_PROTO") {
         Motor3.proto = value;  
      } else if (command == "CFG_M3_ADDR") {
         Motor3.addr = value;  
      } else if (command == "CFG_M3_N") {
         Motor3.neutral = value;  
      } else if (command == "CFG_M3_MIN") {
         Motor3.min = value;  
      } else if (command == "CFG_M3_MAX") {
         Motor3.max = value;  
      } else if (command == "CFG_M3_REV") {
         Motor3.reverse = value;  
      } else if (command == "CFG_M3_DIR") {
         Motor3.direction = value;  
      } else if (command == "CFG_M4_PROTO") {
         Motor4.proto = value;  
      } else if (command == "CFG_M4_ADDR") {
         Motor4.addr = value;  
      } else if (command == "CFG_M4_N") {
         Motor4.neutral = value;  
      } else if (command == "CFG_M4_MIN") {
         Motor4.min = value;  
      } else if (command == "CFG_M4_MAX") {
         Motor4.max = value;  
      } else if (command == "CFG_M4_REV") {
         Motor4.reverse = value;  
      } else if (command == "CFG_M4_DIR") {
         Motor4.direction = value;  

      } else if (command == "MOTOR_SETUP") {
         serial_command = "";
         command_complete = false;
         motor_setup();  

      } else if (command == "CFG_L1_PROTO") {
         Light1.proto = value;  
      } else if (command == "CFG_L1_ADDR") {
         Light1.addr = value;  
      } else if (command == "CFG_L1_ON") {
         Light1.on= value;  
      } else if (command == "CFG_L1_OFF") {
         Light1.off = value;  
      } else if (command == "CFG_L2_PROTO") {
         Light2.proto = value;  
      } else if (command == "CFG_L2_ADDR") {
         Light2.addr = value;  
      } else if (command == "CFG_L2_ON") {
         Light2.on = value;  
      } else if (command == "CFG_L2_OFF") {
         Light2.off = value;  

      } else if (command == "LIGHT_SETUP") {
         serial_command = "";
         command_complete = false;
         light_setup();  

      } else if (command == "CFG_CX_PROTO") {
         CamX.proto = value;  
      } else if (command == "CFG_CX_ADDR") {
         CamX.addr = value;  
      } else if (command == "CFG_CX_N") {
         CamX.neutral = value;  
      } else if (command == "CFG_CX_MIN") {
         CamX.min = value;  
      } else if (command == "CFG_CX_MAX") {
         CamX.max = value;  

      } else if (command == "CAM_SETUP") {
         serial_command = "";
         command_complete = false;
         cam_setup();  

      } else if (command == "CFG_IMU_PROTO") {
         IMU.proto = value;  
      } else if (command == "CFG_IMU_ADDR") {
         IMU.addr = value;  
      } else if (command == "CFG_IMU_TYPE") {
         IMU.type = value;  
      
      } else if (command == "IMU_SETUP") {
         serial_command = "";
         command_complete = false;
         imu_setup();  

      } else if (command == "CFG_DEPTH_PROTO") {
         DEPTH.proto = value;  
      } else if (command == "CFG_DEPTH_ADDR") {
         DEPTH.addr = value;  
      } else if (command == "CFG_DEPTH_TYPE") {
         DEPTH.type = value;  
      
      } else if (command == "DEPTH_SETUP") {
         serial_command = "";
         command_complete = false;
         depth_setup();  

      } else if (command == "CFG_CURRENT_PROTO") {
         CURRENT.proto = value;  
      } else if (command == "CFG_CURRENT_ADDR") {
         CURRENT.addr = value;  
      } else if (command == "CFG_CURRENT_TYPE") {
         CURRENT.type = value;  
      
      } else if (command == "CURRENT_SETUP") {
         serial_command = "";
         command_complete = false;
         current_setup();  

      } else if (command == "CFG_AMP_PROTO") {
         AMP.proto = value;  
      } else if (command == "CFG_AMP_ADDR") {
         AMP.addr = value;  
      } else if (command == "CFG_AMP_TYPE") {
         AMP.type = value;  
      
      } else if (command == "AMP_SETUP") {
         serial_command = "";
         command_complete = false;
         amp_setup();  

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
 
