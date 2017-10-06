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

#pragma once
#ifndef _CONFIG_H
#define _CONFIG_H

//
// Motor BITS
//
//                                   s
//                                  st
//                                  tr r    
//                                  raro    
//                                  afol    rf 
//                                  fell    eo 
//                                  erlr   rvr 
//                                  lilid liew 
//                                  eiegi egrr 
//                                  fhfhvufhsa 
//                                  fttteptted 
//                                  ||||||||||
//#define THRUSTERX_DIR           0b0011001111	// if bit is set, thruster will run (see thruster.h) 

#define THRUSTER1_PWM
#define THRUSTER1_PIN		3
#undef  THRUSTER1_I2C
#undef  THRUSTER1_ADDR	        //0x29
#undef  THRUSTER1_POLE	        //6
#define THRUSTER1_NEUTRAL	1500
#define THRUSTER1_MIN		1100
#define THRUSTER1_MAX		1900
#define THRUSTER1_DIR           0b0011001111	// if bit is set, thruster will run (see thruster.h) 
#define THRUSTER1_REVERSE       0b0001000110	// if bit is set, thruster will reverse

#define THRUSTER2_PWM
#define THRUSTER2_PIN	        22
#define THRUSTER2_NEUTRAL	1500
#define THRUSTER2_MIN	        1100
#define THRUSTER2_MAX	        1900
#define THRUSTER2_DIR           0b0011001111	// if bit is set, thruster will run (see thruster.h) 
#define THRUSTER2_REVERSE       0b0001000101	// if bit is set, thruster will reverse

#define THRUSTER3_PWM
#define THRUSTER3_PIN	        4
#define THRUSTER3_NEUTRAL	1500
#define THRUSTER3_MIN	        1100
#define THRUSTER3_MAX	        1900
#define THRUSTER3_DIR		0b0011001111	// if bit is set, thruster will run (see thruster.h) 
#define THRUSTER3_REVERSE	0b0001001010	// if bit is set, thruster will reverse

#define THRUSTER4_PWM
#define THRUSTER4_PIN	        21
#define THRUSTER4_NEUTRAL	1500
#define THRUSTER4_MIN	        1100
#define THRUSTER4_MAX	        1900
#define THRUSTER4_DIR		0b0011001111	// if bit is set, thruster will run (see thruster.h) 
#define THRUSTER4_REVERSE	0b0010100110	// if bit is set, thruster will reverse

#define THRUSTER5_PWM
#define THRUSTER5_PIN	        20
#define THRUSTER5_NEUTRAL	1500
#define THRUSTER5_MIN	        1100
#define THRUSTER5_MAX	        1900
#define THRUSTER5_DIR		0b1100110000	// if bit is set, thruster will run (see thruster.h) 
#define THRUSTER5_REVERSE	0b0100101111	// if bit is set, thruster will reverse

#define THRUSTER6_PWM
#define THRUSTER6_PIN	        23
#define THRUSTER6_NEUTRAL	1500
#define THRUSTER6_MIN	        1100
#define THRUSTER6_MAX	        1900
#define THRUSTER6_DIR		0b1100110000	// if bit is set, thruster will run (see thruster.h) 
#define THRUSTER6_REVERSE	0b1000011111	// if bit is set, thruster will reverse

#define LIGHT1_PWM
#undef  LIGHT1_RELAY
#define LIGHT1_PIN	9
#define LIGHT1_ON	1900
#define	LIGHT1_OFF	1100

#define LIGHT2_PWM
#undef  LIGHT2_RELAY
#define LIGHT2_PIN	10
#define LIGHT2_ON	1900
#define	LIGHT2_OFF	1100

#define LIGHT3_PWM
#undef  LIGHT3_RELAY
#define LIGHT3_PIN	5
#define LIGHT3_ON	1900
#define	LIGHT3_OFF	1100

#define LIGHT4_PWM
#undef  LIGHT4_RELAY
#define LIGHT4_PIN	6
#define LIGHT4_ON	1900
#define	LIGHT4_OFF	1100

#define CAMERAX_PWM
#define CAMERAX_PIN	5
#define CAMERAX_NEUTRAL	1500
#define CAMERAX_MIN	1100
#define CAMERAX_MAX	1900

#undef  CAMERAY_PWM

#define	IMU_I2C
#define	IMU_TYPE	1	// 1 = BNO055
#define	IMU_ADDR	55

#define DEPTH_I2C
#define DEPTH_TYPE	1	// 1 = MS5837_30BA
#define DEPTH_WATER	1	// 1 = fresh, 2 = salt
#define DEPTH_ADDR	0x76

#define	VOLT_ANALOG
#define VOLT_TYPE	2	// 1 = ATTOPILOT_A180
                                // 2 = HKPilot 10S Power module
#define VOLT_PIN	1	// A0

#define AMP_ANALOG
#define	AMP_TYPE	2	// 1 ATTOPILOT_A180 
                                // 2 = HKPilot 10S Power module
#define AMP_PIN		0	// A1

#endif

