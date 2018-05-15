#!/bin/bash

echo "Begin build-script.sh"

cd /home/pi/openFrameworks/addons/ofxPiMapper/example_basic
timeout -k 30m make -j $(nproc)

echo "End build-script.sh"
