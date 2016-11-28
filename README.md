# Moki-ROV2 (Non working software)

Pilot your ROV-PI directly from your PC webbrowser browser.

If you encounter an issue; please mail details to <rov-pi@team-moki.nl>

This software was build on a Raspberry PI (Model B+)

## Currenty supported/tested (aka, my setup)

```
* Raspberry PI (Model B+)
* Raspberry PI Camera Module v2 w/Wide Angle
* Google Chrome browser on PC
* XBox One controller (bluetooth connected to PC)

* Ardiono Mega2560
* BlueRobotics Depth/Pressure sensor [MS5837-30BA]
* Pololu attopilot 180A
* Adafruit BNO055 IMU
```
## Install

# Raspberry PI
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

```
## NodeJS
sudo su -
wget https://nodejs.org/dist/v6.9.1/node-v6.9.1-linux-armv6l.tar.xz
cd /usr/local
rm -rf bin/node bin/npm include/node lib/node
tar --strip-components 1 -xJf /root/node-v6.9.1-linux-armv6l.tar.xz

## Arduino IDE
wget https://downloads.arduino.cc/arduino-1.6.13-linuxarm.tar.xz
cd /usr/share
tar xfJ ~/arduino-1.6.13-linuxarm.tar.xz
ln -s arduino-1.6.13 arduino

## Arduino UDEV Rules
cd /etc/udev/rules.d/
wget https://raw.githubusercontent.com/platformio/platformio/develop/scripts/99-platformio-udev.rules
systemctl restart udev

# Moki-ROV2 Software
cd
git clone https://github.com/Moki38/Moki-ROV2.git
cd Moki-ROV2
npm install 
cd 

# MJPG-Streamer
apt-get install -y subversion libjpeg8-dev imagemagick libav-tools cmake
git clone https://github.com/jacksonliam/mjpg-streamer.git
cd mjpg-streamer/mjpg-streamer-experimental
make install
cd 

# PlatformIO (Arduino CLI)
pip install -U platformio
cd 
cd Moki-ROV2/arduino
platformio init -b megaatmega2560
cd lib
git clone https://github.com/bluerobotics/BlueRobotics_MS5837_Library.git
git clone https://github.com/adafruit/Adafruit_Sensor.git
git clone https://github.com/adafruit/Adafruit_BNO055.git
cd ..
platformio run
platformio run --target upload

cd
cd Moki-ROV2
# Start the software
mjpg_streamer -b -o "output_http.so -w /root/mjpg-streamer/mjpg-streamer-experimental/www" -i "input_raspicam.so -r 1024x768"
node rov.js
(Open browser to Raspberry PI IP adress, port 3000 => http://172.16.10.20:3000)
```

## Usage

######################################################################################
#                   Arduino Pins
######################################################################################
```
Pin 4    ESC 1    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)    
Pin 5    ESC 2    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)
Pin 6    ESC 3    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)
Pin 7    ESC 4    1100 μs (full reverse) 1500 μs (stop) 1900 μs (forward)

Pin 8    Lum 1    1100 μs (off) to 1900 μs (brightest)
Pin 9    Lum 2    1100 μs (off) to 1900 μs (brightest)

Pin 12   Servo 1  150 - 600   375 neutral

Pin A0   V Attopilot 180A
Pin A1   I Attopilot 180A

# Daisy chain your I2C sensors to the Arduino Pins.
Pin 20   I2C SCL
Pin 21   I2C SDA
5V       I2C 5v
GND      I2C GND
```

# PlatformIO cli commands
```
platformio init -b megaatmega2560
platformio run
platformio run --target upload
platformio device monitor -p /dev/ttyACM0
```

## Easy to mis mistakes
```
Are you sure, you are using the right IP adress?
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
