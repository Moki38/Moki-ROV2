#!/bin./bash

#
# Moki-ROV2 (Non working software)
#
# If you encounter an issue; please mail details to <rov-pi@team-moki.nl>
# Copyright (c) 2016 by Eric van Dijken <rov-pi@team-moki.nl>

#
# NodeJS
#
cd
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
cd Moki-ROV2
npm install 
cd 

# MJPG-Streamer
apt-get install -y subversion libjpeg8-dev imagemagick libav-tools cmake
git clone https://github.com/jacksonliam/mjpg-streamer.git
cd mjpg-streamer/mjpg-streamer-experimental
make install
cd 
echo "disable_camera_led=1" >> /boot/config.txt

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
echo "Start the ROV software, with \"node rov.js\""
