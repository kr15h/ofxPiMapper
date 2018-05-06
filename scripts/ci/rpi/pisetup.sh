#!/bin/bash

echo "Hello! Me is pisetup.sh script."

pwd

cd /home/pi/openFrameworks/addons
git clone --depth=1 https://github.com/jeffcrouse/ofxJSON.git
git clone --depth=1 https://github.com/jvcleave/ofxOMXPlayer.git

cd ofxOMXPlayer
git checkout 0.9.0-compatible
cd ..

cd ofxPiMapper/example_basic
make -j$(nproc)

echo "Done!"
