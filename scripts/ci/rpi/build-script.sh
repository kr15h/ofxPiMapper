#!/bin/bash

echo "Begin build-script.sh"

date
timelimit -S 15 -t 2200 make -j $(nproc) -C /home/pi/openFrameworks/addons/ofxPiMapper/example_basic
date
sleep 10

echo "End build-script.sh"
