#!/bin/bash

echo "Begin build-script.sh"

sudo timelimit -S9 -t2000 -T10 make -j $(nproc) -C /home/pi/openFrameworks/addons/ofxPiMapper/example_basic

echo "End build-script.sh"
