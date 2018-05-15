#!/bin/bash

echo "Finalizing OPM RPi image."

cd /home/pi/openFrameworks/addons/ofxPiMapper/example_basic
timeout 25m make -j $(nproc)

echo "OPM RPi image setup done!"
