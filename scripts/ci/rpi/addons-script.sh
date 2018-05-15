#!/bin/bash

echo "Compiling addons."

cd /home/pi/openFrameworks/addons/ofxOMXPlayer/example-basic
make -j $(nproc)

cd /home/pi/openFrameworks/addons/ofxJSON/example_file_read_write
make -j $(nproc)

echo "Compiling addons done!"
