#!/usr/bin/env bash

pwd
git clone --depth=1 -b of-master-patch https://github.com/kr15h/ofxJSON addons/ofxJSON 
mv addons/ofxPiMapper/example_basic/addons.make.norpi addons/ofxPiMapper/example_basic/addons.make
mv addons/ofxPiMapper/example_camera/addons.make.norpi addons/ofxPiMapper/example_camera/addons.make
mv addons/ofxPiMapper/example_fbo-sources/addons.make.norpi addons/ofxPiMapper/example_fbo-sources/addons.make
mv addons/ofxPiMapper/example_pocketvj/addons.make.norpi addons/ofxPiMapper/example_pocketvj/addons.make
mv addons/ofxPiMapper/example_remote-client/addons.make.norpi addons/ofxPiMapper/example_remote-client/addons.make
mv addons/ofxPiMapper/example_remote-server/addons.make.norpi addons/ofxPiMapper/example_remote-server/addons.make
mv addons/ofxPiMapper/example_simpler/addons.make.norpi addons/ofxPiMapper/example_simpler/addons.make
rm -rf addons/ofxPiMapper/example_gamepad
