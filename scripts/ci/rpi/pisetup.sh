#!/bin/bash

echo "Hello! Me is pisetup.sh script."

cd /home/pi/openFrameworks/addons
git clone --depth=1 https://github.com/jeffcrouse/ofxJSON.git
git clone --depth=1 https://github.com/kr15h/ofxPiMapper.git

cd ofxPiMapper/example_basic
make

echo "Done!"
