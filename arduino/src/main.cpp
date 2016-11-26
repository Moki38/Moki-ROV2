#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "MS5837.h"

//
// Attopilot 180
//

int VRaw; //This will store our raw ADC data
int IRaw;
float VFinal; //This will store the converted data
float IFinal;

MS5837 sensor;

Servo esc_1; // create servo object to control a servo
Servo esc_2; // create servo object to control a servo
Servo esc_3; // create servo object to control a servo
Servo esc_4; // create servo object to control a servo
Servo lum_1; // create servo object to control a servo
Servo lum_2; // create servo object to control a servo
Servo ser_1; // create servo object to control a servo

int pos = 0;    // variable to store the servo position
int i = 0;    // variable to store the servo position

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
  Serial.print("\t");
  if (!system)
  {
    Serial.print("! ");
  }

  /* Display the individual values */
  Serial.print("Sys:");
  Serial.print(system, DEC);
  Serial.print(" G:");
  Serial.print(gyro, DEC);
  Serial.print(" A:");
  Serial.print(accel, DEC);
  Serial.print(" M:");
  Serial.print(mag, DEC);
}

void setup() {
  Serial.begin(9600);
  
  Wire.begin();
  sensor.init();
  sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)

  esc_1.attach(4);  // attaches the servo on pin 9 to the servo object
  esc_1.writeMicroseconds(1500);  // attaches the servo on pin 9 to the servo object
  esc_2.attach(5);  // attaches the servo on pin 9 to the servo object
  esc_2.writeMicroseconds(1500);  // attaches the servo on pin 9 to the servo object
  esc_3.attach(6);  // attaches the servo on pin 9 to the servo object
  esc_3.writeMicroseconds(1500);  // attaches the servo on pin 9 to the servo object
  esc_4.attach(7);  // attaches the servo on pin 9 to the servo object
  esc_4.writeMicroseconds(1500);  // attaches the servo on pin 9 to the servo object
  delay(1000); // delay to allow the ESC to recognize the stopped signal
  lum_1.attach(8);  // attaches the servo on pin 9 to the servo object
  lum_1.writeMicroseconds(1100);  // attaches the servo on pin 9 to the servo object
  lum_2.attach(9);  // attaches the servo on pin 9 to the servo object
  lum_2.writeMicroseconds(1100);  // attaches the servo on pin 9 to the servo object
  delay(1000); // delay to allow the ESC to recognize the stopped signal
  ser_1.attach(12);  // attaches the servo on pin 9 to the servo object
  ser_1.writeMicroseconds(375);  // attaches the servo on pin 9 to the servo object
 
  Serial.println("Orientation Sensor Test"); Serial.println("");

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000); // delay to allow the ESC to recognize the stopped signal

  /* Display some basic information on this sensor */
  displaySensorDetails();

  /* Optional: Display current status */
  displaySensorStatus();

  bno.setExtCrystalUse(true);
}

void loop() {

  VRaw = analogRead(A0);
  IRaw = analogRead(A1);

  //Conversion
  VFinal = VRaw/12.99; //180 Amp board  
  IFinal = IRaw/3.7; //180 Amp board

  sensor.read();

  Serial.print("Pressure: "); 
  Serial.print(sensor.pressure()); 
  Serial.println(" mbar");
  
  Serial.print("Temperature: "); 
  Serial.print(sensor.temperature()); 
  Serial.println(" deg C");
  
  Serial.print("Depth: "); 
  Serial.print(sensor.depth()); 
  Serial.println(" m");
  
  Serial.print("Altitude: "); 
  Serial.print(sensor.altitude()); 
  Serial.println(" m above mean sea level");

  Serial.print(VFinal);
  Serial.println("   Volts");
  Serial.print(IFinal);
  Serial.println("   Amps");
  Serial.println("");
  Serial.println("");
  delay(1000);

   /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  /* Display the floating point data */
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);

  /* Optional: Display calibration status */
  displayCalStatus();

  /* Optional: Display sensor status (debug only) */
  //displaySensorStatus();

  /* New line for the next sample */
  Serial.println("");

  /* Wait the specified delay before requesting nex data */
  delay(BNO055_SAMPLERATE_DELAY_MS); 
//  for (pos = 45; pos <= 135; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
    ser_1.write(90);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//  for (pos = 135; pos >= 45; pos -= 1) { // goes from 180 degrees to 0 degrees
//    ser_1.write(pos);              // tell servo to go to position in variable 'pos'
//    //delay(15);                       // waits 15ms for the servo to reach the position
//  }
}

