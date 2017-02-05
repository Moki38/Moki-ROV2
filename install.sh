#!/bin/bash

#
# Moki-ROV2 (Non working software)
#
# If you encounter an issue; please mail details to <rov-pi@team-moki.nl>
# Copyright (c) 2016 by Eric van Dijken <rov-pi@team-moki.nl>

HOST_IP=`hostname -I`

#
# NodeJS
#
cd
wget https://nodejs.org/dist/v6.9.5/node-v6.9.5-linux-armv6l.tar.xz
cd /usr/local
rm -rf bin/node bin/npm include/node lib/node
tar --strip-components 1 -xJf /root/node-v6.9.5-linux-armv6l.tar.xz

## Arduino IDE
cd
wget https://downloads.arduino.cc/arduino-1.8.1-linuxarm.tar.xz
cd /usr/share
tar xfJ ~/arduino-1.8.1-linuxarm.tar.xz
ln -s arduino-1.8.1 arduino

## Arduino UDEV Rules
cd /etc/udev/rules.d/
wget https://github.com/platformio/platformio-core/blob/develop/scripts/99-platformio-udev.rules
#wget https://raw.githubusercontent.com/platformio/platformio/develop/scripts/99-platformio-udev.rules
systemctl restart udev

# Moki-ROV2 Software
cd
cd Moki-ROV2
sed -i "s/172.16.10.20:8080/$HOST_IP:8080/g" public/index.html
sed -i "s/ :8080/:8080/g" public/index.html
npm install 

# MJPG-Streamer
cd
apt-get install -y subversion libjpeg8-dev imagemagick libav-tools cmake
git clone https://github.com/jacksonliam/mjpg-streamer.git
cd mjpg-streamer/mjpg-streamer-experimental
make install
echo "disable_camera_led=1" >> /boot/config.txt

# PlatformIO (Arduino CLI)
#pip install -U platformio
cd
wget https://raw.githubusercontent.com/platformio/platformio/develop/scripts/get-platformio.py
python get-platformio.py
cd 
cd Moki-ROV2/arduino
platformio init -b teensy31
cd lib
git clone https://github.com/bluerobotics/BlueRobotics_MS5837_Library.git
git clone https://github.com/adafruit/Adafruit_Sensor.git
git clone https://github.com/adafruit/Adafruit_BNO055.git
git clone https://github.com/sparkfun/SparkFun_MPU-9250_Breakout_Arduino_Library.git
git clone https://github.com/bluerobotics/Arduino_I2C_ESC.git
cd ..
platformio run
platformio run --target upload

cd
cd Moki-ROV2
echo "Start the ROV software, with \"node rov.js\""
