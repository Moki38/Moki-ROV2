# Moki-ROV2 (Working software, with my setup) 

Pilot your ROV-PI directly from your PC webbrowser browser.

If you encounter an issue; please mail details to <rov-pi@team-moki.nl>

This software was build on a Raspberry PI (Model B+)

## Currenty supported/tested (aka, my setup)

```
* Raspberry PI (Model B+)
* Raspberry PI Camera Module v2 w/Wide Angle
* Google Chrome browser on PC
* XBox One controller (bluetooth connected to PC)

* Teensy 3.2 (replaces Arduino Mega2560, but both will work)
* BlueRobotics Depth/Pressure sensor [MS5837-30BA]
* Pololu attopilot 180A
* Adafruit BNO055 IMU
```
## Install

#
# Raspberry PI
#
Download "RASPBIAN JESSIE LITE" from https://www.raspberrypi.org/downloads/raspbian/
Put the image on a SD card (ymmv)

Boot, login using pi/raspberry
change the password

sudo apt-get install -y locate htop git i2c-tools build-essential

set fixed ip (sudo vi /etc/dhcpcd.conf)
interface eth0
```
static ip_address=172.16.10.20/24
static routers=172.16.10.1
static domain_name_servers=172.16.10.1
```

sudo raspi-config (enable camera / i2c)

sudo apt-get update
sudo apt-get dist-upgrade

reboot 


Install the MOKI-ROV2 software, may take a while..
```
sudo su -
git clone https://github.com/Moki38/Moki-ROV2.git
cd Moki-ROV2
./install.sh
 
# Start the ROV software
node rov.js
(Open browser to Raspberry PI IP adress, port 80 => http://172.16.10.20)
```

## Controls

XBOX Controller
```
 'A': Hover ON/OFF
 'B': AutoPilot ON/OFF
 'X': Kill Power (0%)
 'Y': Lights ON/OFF

 VIEW: DisARM Motor
 Menu: ARM Motor

 LB: Power -10%
 RB: Power +10%

 Pad UP: Camera Down (-10%)
 Pad DOWN: Camera Up (+10%)

 RT: Roll Right
 LT: Roll Left

 LS Up:    Forward
 LS Down:  Reverse
 LS Left:  Turn left
 LS Right: Turn Right

 RS Up:    Up
 RS Down:  Dive
 RS Left:  Strafe Left
 RS Right: Strafe Right

```

Keyboard
```
 'A': Abort (will kill the engines, etc.) (Safety: if XBOX Controller fails)
```

## Usage

######################################################################################
# Arduino Pins => Configured in "Moki-ROV2/arduino/src/config.h"
######################################################################################
Arduino UNO (example pin layout)
```
Pin 3    ESC 1    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)    
Pin 5    ESC 2    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)
Pin 6    ESC 3    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)
Pin 9    ESC 4    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)

Pin 10   Lum 1    1100 μs (off) to 1900 μs (brightest) (Daisy chain, if you have multiple Lumen Lights)

Pin 11   Servo Cam X    1100 μs (full down) 1500 μs (central) 1900 μs (full up)

Pin A0   V Attopilot 180A
Pin A1   I Attopilot 180A

# Daisy chain your I2C sensors to the Arduino Pins.
Pin A5   I2C SCL
Pin A4   I2C SDA
5V       I2C 5v
GND      I2C GND

# Power 
USB Powered from PI
```

Arduino Mega2560 (example pin layout)
```
Pin 4    ESC 1    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)    
Pin 5    ESC 2    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)
Pin 6    ESC 3    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)
Pin 7    ESC 4    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)

Pin 8    Lum 1    1100 μs (off) to 1900 μs (brightest)
Pin 9    Lum 2    1100 μs (off) to 1900 μs (brightest)

Pin 12   Servo Cam X    1100 μs (full down) 1500 μs (central) 1900 μs (full up)

Pin A0   V Attopilot 180A
Pin A1   I Attopilot 180A

# Daisy chain your I2C sensors to the Arduino Pins.
Pin 20   I2C SCL
Pin 21   I2C SDA
5V       I2C 5v
GND      I2C GND

# Power 
USB Powered from PI
```

Teensy 3.2 (example pin layout)
```
Digital Pin 3    ESC 1    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)    
Digital Pin 4    ESC 2    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)
Digital Pin 23   ESC 3    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)
Digital Pin 22   ESC 4    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)

Digital Pin 6    Lum 1    1100 μs (off) to 1900 μs (brightest)
Digital Pin 20   Lum 2    1100 μs (off) to 1900 μs (brightest)

Digital Pin 10   Servo Cam X    1100 μs (full down) 1500 μs (central) 1900 μs (full up)

Analog Pin A0   V Attopilot 180A
Analog Pin A1   I Attopilot 180A

# Daisy chain your I2C sensors to the Arduino Pins.
Digital Pin 19   I2C SCL0
Digital Pin 18   I2C SDA0
5V      I2C 5v
GND     I2C GND

# Power (Cut/scratch circuit to separate VIN from VUSB)
GND
Vin
```

# PlatformIO cli commands (debug only)
```
platformio init -b uno (for Arduino Uno)
platformio init -b megaatmega2560 (for Arduino Mega2560)
platformio init -b teensy31 (for Teensy 3.2)
platformio run
platformio run --target upload
platformio device monitor -p /dev/ttyACM0
```

## Easy to mis mistakes
```
Are you sure, you are using the right IP adress?
```
```
XBOX One controller sluggisch, make sure your browser window is active?
```
```
Motors not running, check Power setting (> 0%) and if "MOTOR: ARMED"
```

## Thanks

The perfect place for ROV builders: http://www.homebuiltrovs.com/rovforum/index.php
The people at http://www.bluerobotics.com/ for building great stuff (makes ROV building easier/faster)

## License

The MIT License

Copyright (c) 2016 by Eric van Dijken <rov-pi@team-moki.nl>

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
