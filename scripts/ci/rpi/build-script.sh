#!/bin/bash

echo "Begin build-script.sh"

cd /home/pi/openFrameworks/addons/ofxPiMapper/example_basic
timeout --version
timeout -signal=KILL 1800 make -j $(nproc)

echo "End build-script.sh"
