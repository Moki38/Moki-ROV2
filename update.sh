#!/bin/bash

function version_1_0_1() {
git pull
npm install winston
mkdir log
cd arduino/
platformio lib install git+https://github.com/br3ttb/Arduino-PID-Library.git
pio run -t upload
cd ..
}

version=`cat VERSION`

case $version in
  1.0.0)
    version_1_0_1
    ;;
  *)
    echo "No update available for this version"
    exit 1
esac  

