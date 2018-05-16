#!/bin/bash

echo "Begin build-script.sh"

sudo apt-get -y install timelimit

cd /home/pi/openFrameworks/addons/ofxPiMapper/example_basic

timelimit -s KILL 10 make -j $(nproc)

echo "End build-script.sh"
