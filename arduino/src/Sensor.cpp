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

#include "Sensor.h"

uint8_t Sensor::Imu_System() {
    return system_imu;
}

uint8_t Sensor::Imu_Gyro() {
    return gyro;
}

uint8_t Sensor::Imu_Accel() {
    return accel;
}

uint8_t Sensor::Imu_Mag() {
    return mag;
}

int Sensor::Imu_Temp() {
    return (imu_temp);
}

float Sensor::Imu_Accl_X() {
    return (imu_vec.x()); //x acceleration
}

float Sensor::Imu_Accl_Y() {
    return (imu_vec.y()); //x acceleration
}

float Sensor::Imu_Accl_Z() {
    return (imu_vec.z()); //x acceleration
}

float Sensor::Imu_X() {
    return event.orientation.x;
}

float Sensor::Imu_Y() {
    return event.orientation.y;
}

float Sensor::Imu_Z() {
    return event.orientation.z;
}

float Sensor::Imu_Heading() {
    return event.orientation.roll;
}

float Sensor::Imu_Roll() {
    return -event.orientation.pitch;
}

float Sensor::Imu_Pitch() {
    if (event.orientation.heading < 0) {
        return -(event.orientation.heading+180);
    } else {
        return abs(event.orientation.heading-180);
    }
}

void Sensor::Imu_Loop() {
    bno.getEvent(&event);
    imu_temp = bno.getTemp();
    // Possible vector values can be:
    // - VECTOR_ACCELEROMETER - m/s^2
    // - VECTOR_MAGNETOMETER  - uT
    // - VECTOR_GYROSCOPE     - rad/s
    // - VECTOR_EULER         - degrees
    // - VECTOR_LINEARACCEL   - m/s^2
    // - VECTOR_GRAVITY       - m/s^2

    imu_vec = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);

    bno.getCalibration(&system_imu, &gyro, &accel, &mag);
}

void Sensor::Imu_Setup() {
    sensor_t sensor;
    if (bno.begin()) {
        FOUND_BNO = 1;
    }
    delay(1000);
    /* Display some basic information on this sensor */
    if (FOUND_BNO) {
        bno.getSensor(&sensor);
        bno.getSystemStatus(&system_status, &self_test_results, &system_error);
        bno.setExtCrystalUse(true);
    }

}

float Sensor::Pressure() {
    if (MS5837_status) {
        return (MS5837_sensor.pressure());
    } else {
        return -1;
    }
}

int Sensor::Temp() {
    if (MS5837_status) {
        return (MS5837_sensor.temperature());
    } else {
        return -1;
    }
}

float Sensor::Depth() {
    if (MS5837_status) {
        return (MS5837_sensor.depth()*100);
    } else {
        return -1;
    }
}

int Sensor::Alt() {
    if (MS5837_status) {
        return (MS5837_sensor.altitude());
    } else {
        return -1;
    }
}

void Sensor::Depth_Loop() {
    MS5837_sensor.read();
}

void Sensor::Depth_Setup() {
    MS5837_status = MS5837_sensor.init();
    if (DEPTH_WATER == 1) {
        MS5837_sensor.setFluidDensity(997); // kg/m^3 (freshwater)
    } else {
        MS5837_sensor.setFluidDensity(1029); // kg/m^3 (sea/saltwater)
    }
}

float Sensor::Current() {
    VFinal = -1;
    VRaw = analogRead(CURRENT_PIN);
    if (VRaw < 400) {
        //Conversion
        VFinal = VRaw/12.99; //180 Amp board
    }
    return (VFinal);
}

float Sensor::Amps() {
    IFinal = -1;
    IRaw = analogRead(AMP_PIN);
//    Serial.print("Amps_RAW:");
//    Serial.println(IRaw);
    if (IRaw < 400) {
        //Conversion
        //      IFinal = IRaw/7.4; //180 Amp board
        IFinal = IRaw/3.7; //180 Amp board
    }
    return (IFinal);
}

void Sensor::Current_Setup() {
}

void Sensor::Amps_Setup() {
}

int Sensor::Time() {
    return sensor_time;
}

void Sensor::Time(int time) {
    sensor_time = time;
}

void Sensor::Setup() {
    Imu_Setup();
    Depth_Setup();
    Current_Setup();
    Amps_Setup();
}

void Sensor::Loop() {
    Serial.print("Time:");
    sensor_time = millis();
    Serial.println(sensor_time);

    Serial.print("Volt:");
    Serial.println(Current(),4);
    Serial.print("Amps:");
    Serial.println(Amps(),4);

    Depth_Loop();
    Serial.print("Pressure:");
    Serial.println(Pressure(), 4);
    Serial.print("Temp_Out:");
    Serial.println(Temp());
    Serial.print("Depth:");
    Serial.println(Depth(), 4);
    Serial.print("Altitude:");
    Serial.println(Alt());

    Imu_Loop();
    Serial.print("X:");
    Serial.println(Imu_X(), 4);
    Serial.print("Y:");
    Serial.println(Imu_Y(), 4);
    Serial.print("Z:");
    Serial.println(Imu_Z(), 4);
    Serial.print("ACCL_X:");
    Serial.println(Imu_Accl_X(), 4);
    Serial.print("ACCL_Y:");
    Serial.println(Imu_Accl_Y(), 4);
    Serial.print("ACCL_Z:");
    Serial.println(Imu_Accl_Z(), 4);
    Serial.print("Heading:");
    Serial.println(Imu_Heading(), 4);
    Serial.print("Roll:");
    Serial.println(Imu_Roll(), 4);
    Serial.print("Pitch:");
    Serial.println(Imu_Pitch(), 4);
    Serial.print("Temp_In:");
    Serial.println(Imu_Temp());
    Serial.print("Sys:");
    Serial.println(Imu_System());
    Serial.print("Gyro:");
    Serial.println(Imu_Gyro());
    Serial.print("Accel:");
    Serial.println(Imu_Accel());
    Serial.print("Mag:");
    Serial.println(Imu_Mag());
}
