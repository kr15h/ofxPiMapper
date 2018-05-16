#!/bin/bash

echo "Begin build-script.sh"

sudo apt-get -y install timelimit

/usr/bin/timelimit -s KILL 10 /usr/bin/make -j $(nproc) -C /home/pi/openFrameworks/addons/ofxPiMapper/example_basic

echo "End build-script.sh"
