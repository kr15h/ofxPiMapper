#!/bin/bash

echo "Compiling addons."

cd /home/pi/openFrameworks/addons/ofxOMXPlayer/example-basic
make -j

cd /home/pi/openFrameworks/addons/ofxJSON/example_file_read_write
make -j

echo "Compiling addons done!"
