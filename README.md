# Moki-ROV2

Pilot your ROV-PI directly from your browser.

If you encounter an issue; please mail details to <rov-pi@team-moki.nl>

This software was build on a Raspberry PI (Model B+)

## Currenty supported/tested 

* Adafruit 16-Channel 12-bit PWM/Servo Driver - I2C interface - PCA9685 (http://www.adafruit.com/product/815)
* BlueRobotics Depth/Pressure sensor [MS5837-30BA] ** (https://www.bluerobotics.com/store/electronics/bar30-sensor-r1/)
* MPU-9250 9-axis IMU 
* MCP3424 / ADC-Pi-Plus (https://www.abelectronics.co.uk/products/17/Raspberry-Pi-B/56/ADC-Pi-Plus---Raspberry-Pi-Analogue-to-Digital-converter)
* attopilot (https://www.coolcomponents.co.uk/attopilot-voltage-and-current-sense-breakout-180a.html)
* XBox One controller
* Raspberry PI Camera Module v2 w/Wide Angle


## Install

```
sudo su -
git clone https://github.com/Moki38/Moki-ROV2.git
cd Moki-ROV2
npm install .
cd ~
apt-get install -y subversion libjpeg8-dev imagemagick libav-tools cmake
git clone https://github.com/jacksonliam/mjpg-streamer.git
cd mjpg-streamer/mjpg-streamer-experimental
make install
cd ../..
```

## Usage

1. mjpg_streamer -b
2. ./rov start
3. Point your browser to http://[ROV-IP]:3000/

## Thanks

The perfect place for ROV builders: http://www.homebuiltrovs.com/rovforum/index.php

## License

The MIT License

Copyright (c) 2014 by Eric van Dijken <rov-pi@team-moki.nl>

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
