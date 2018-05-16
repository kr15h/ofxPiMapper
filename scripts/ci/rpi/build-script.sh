#!/bin/bash

echo "Begin build-script.sh"

date
timelimit -s KILL -t 2000 make -j $(nproc) -C /home/pi/openFrameworks/addons/ofxPiMapper/example_basic
date

echo "End build-script.sh"
