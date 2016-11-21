# Moki-ROV 

Pilot your ROV-PI directly from your browser, this will ofcourse only work if you have some kind of network connection to your ROV.
In the setup, in which this software was writen, i am using 100Mb ethernet and Google Chrome as browser (as this one supports the Xpad)
The browser screen will display a HUD, with all the sensor details you have on board your ROV.

If you encounter an issue; please mail details to <rov-pi@team-moki.nl>

This software was build on a Raspberry PI (Model B+)

## Currenty supported/tested 

* Adafruit 16-Channel 12-bit PWM/Servo Driver - I2C interface - PCA9685 (http://www.adafruit.com/product/815)
	•Pin 1/2 Camara movement x/y
	•Pin 7/8 Light Relay (http://www.kiwi-electronics.nl/tweekanaals-relais-module-5v)
	•Pin 12/13/14/15 ESC speed-controllers (brushless / brushed)

* OpenROV Pressure sensor [MS5803-14BA] ** (http://store.openrov.com/products/openrov-imu-depth-module)
	•Senses down up to 130m depth
	•Precision to about 1cm of depth
	•Integrated temperature sensor precise to about 0.1C

* MPU-9150 9-axis IMU (http://store.openrov.com/products/openrov-imu-depth-module)
	•3-axis magnetometer for detection of heading (regardless of orientation)
	•3-axis accelerometer to detect roll and pitch
	•3 axis gyroscope to detect rotational rate

* MCP3424 / ADC-Pi-Plus (https://www.abelectronics.co.uk/products/17/Raspberry-Pi-B/56/ADC-Pi-Plus---Raspberry-Pi-Analogue-to-Digital-converter)
	8 Channel ADC digital converter.

* attopilot (https://www.coolcomponents.co.uk/attopilot-voltage-and-current-sense-breakout-180a.html)
	Voltage/Current sensor 0-60v 180A 

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

4. ./rov start
5. Point your browser to http://[ROV-IP]:3000/

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
