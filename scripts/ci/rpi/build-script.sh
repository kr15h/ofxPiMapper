#!/bin/bash

echo "Begin build-script.sh"

sudo apt-get -y install timeout

cd /home/pi/openFrameworks/addons/ofxPiMapper/example_basic
kill -l
which timeout
timeout --version
/usr/bin/timeout --signal=SIGKILL 10 make -j $(nproc)

echo "End build-script.sh"
