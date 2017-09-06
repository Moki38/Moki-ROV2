#!/bin/bash

git pull
npm install winston
mkdir log
cd arduino/
platformio lib install git+https://github.com/br3ttb/Arduino-PID-Library.git
pio run -t upload
cd ..

