#!/bin/bash

echo "Begin build-script.sh"

sudo apt-get -y install timelimit

timelimit -s KILL -t 10 make -j $(nproc) -C /home/pi/openFrameworks/addons/ofxPiMapper/example_basic

echo "End build-script.sh"
