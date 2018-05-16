#!/bin/bash

echo "Begin build-script.sh"

sudo apt-get -y install coreutils

cd /home/pi/openFrameworks/addons/ofxPiMapper/example_basic
timeout --version
sudo timeout --signal=SIGKILL 10 make -j $(nproc)

echo "End build-script.sh"
