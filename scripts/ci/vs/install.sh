#!/usr/bin/env bash

echo ">> Custom ofxPiMapper CI install script for VS"
pwd
git clone --depth=1 -b of-master-patch https://github.com/kr15h/ofxJSON addons/ofxJSON 

# Test only part of examples because uf the 60m time limit on AppVeyor
mv addons/ofxPiMapper/example_basic/addons.make.norpi addons/ofxPiMapper/example_basic/addons.make
mv addons/ofxPiMapper/example_fbo-sources/addons.make.norpi addons/ofxPiMapper/example_fbo-sources/addons.make
mv addons/ofxPiMapper/example_remote-client/addons.make.norpi addons/ofxPiMapper/example_remote-client/addons.make
mv addons/ofxPiMapper/example_remote-server/addons.make.norpi addons/ofxPiMapper/example_remote-server/addons.make

# Delete the rest
rm -rf addons/ofxPiMapper/example_gamepad
rm -rf addons/ofxPiMapper/example_pocketvj
rm -rf addons/ofxPiMapper/example_simpler
rm -rf addons/ofxPiMapper/example_camera
echo ">> Custom install script done"
