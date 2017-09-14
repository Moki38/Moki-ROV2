# Moki-ROV2 (Pilot your ROV directly from your PC)

If you gonna use this code, please let me know by email!

Warning: This is NOT out-of-the-box software, it will need advanced linux/arduino/hardware skills to get it working!

If you encounter an issue; please mail details to <rov-pi@team-moki.nl>

This software was build on a Raspberry PI (Model B+)

Wiki can be found at: http://wiki.team-moki.nl/display/MOK

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

* BlueROV2 Frame (6 thrusters)
```
## Install

#
# Raspberry PI
#
Download "RASPBIAN LITE" from https://www.raspberrypi.org/downloads/raspbian/
Put the image on a SD card (ymmv)

Boot, login using pi/raspberry
Change the password

Update your Raspberry PI distribution.
```
sudo apt-get update
sudo apt-get dist-upgrade
```

Install some linux tools, to get started.
```
sudo apt-get install -y locate htop git i2c-tools build-essential
```

set fixed ip (sudo vi /etc/dhcpcd.conf)
interface eth0
```
static ip_address=172.16.10.20/24
static routers=172.16.10.1
static domain_name_servers=172.16.10.1
```

```
sudo raspi-config (update raspi-config)
sudo raspi-config (expand root filesystem (Advanced Options))
sudo raspi-config (enable camera / i2c (Interfacing Options))
```


```
reboot 
```


Install the MOKI-ROV2 software, may take a while..
```
sudo su -
git clone https://github.com/Moki38/Moki-ROV2.git
cd Moki-ROV2
./install.sh
 
# Check/Update the Moki-ROV config files, for your settings/config.
vi config.js
vi arduino/src/config.h

# Start the ROV software
node rov.js
(Open browser to Raspberry PI's IP adress, port 80 => http://172.16.10.20)
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
# Arduino Pins => Configured in "Moki-ROV2/config.js"
######################################################################################
Teensy 3.2 (example pin layout)
```
Digital Pin 9    ESC 1    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)    
Digital Pin 10   ESC 2    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)
Digital Pin 20   ESC 3    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)
Digital Pin 21   ESC 4    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)
Digital Pin 22   ESC 5    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)
Digital Pin 23   ESC 6    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)

Digital Pin 3    Lum 1    1100 μs (off) to 1900 μs (brightest)
Digital Pin 4    Lum 2    1100 μs (off) to 1900 μs (brightest)

Digital Pin 5    Servo Cam X    1100 μs (full down) 1500 μs (central) 1900 μs (full up)

Analog Pin A0   V Attopilot 180A
Analog Pin A1   I Attopilot 180A

# Daisy chain your I2C sensors to the Arduino Pins.
Digital Pin 19   I2C SCL0
Digital Pin 18   I2C SDA0
3.3V    I2C 3.3v
GND     I2C GND

# If you alse want to add the Raspberry PI to the I2C chain, do NOT connect 3.3V on the Arduino/Teensy.
3.3V    +3.3V Power (pin 1)
SDA     GPIO 0      (pin 3)
SCL     GPIO 1      (pin 5)
GND     Ground      (pin 6)

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
Did you also check the files, in the public directory?
```
```
XBOX One controller sluggisch, make sure your browser window is active?
```
```
Motors not running, check Power setting (> 0%) and if "MOTOR: ARMED"
```

## Debugging
```
root@raspberrypi:~/Moki-ROV2# i2cdetect -y 1
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:          -- -- -- -- -- -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- 28 -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- -- -- -- -- -- 76 --
```
```
root@raspberrypi:~/Moki-ROV2# lsusb
Bus 001 Device 004: ID 16c0:0483 Van Ooijen Technische Informatica Teensyduino Serial
Bus 001 Device 003: ID 0424:ec00 Standard Microsystems Corp. SMSC9512/9514 Fast Ethernet Adapter
Bus 001 Device 002: ID 0424:9514 Standard Microsystems Corp.
Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
root@raspberrypi:~/Moki-ROV2# ls -l /dev/ttyACM0
crw-rw---- 1 root dialout 166, 0 Jul 17 19:04 /dev/ttyACM0
```

## Thanks

The perfect place for ROV builders: http://www.homebuiltrovs.com/rovforum/index.php
The people at http://www.bluerobotics.com/ for building great stuff (makes ROV building easier/faster)

## License

The MIT License

Copyright (c) 2016 by Eric van Dijken <eric@team-moki.nl>

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
