#!/bin/bash

cd ~/openFrameworks/addons/ofxPiMapper
mv example_basic/addons.make.norpi example_basic/addons.make
mv example_camera/addons.make.norpi example_camera/addons.make
mv example_fbo-sources/addons.make.norpi example_fbo-sources/addons.make
mv example_pocketvj/addons.make.norpi example_pocketvj/addons.make
mv example_remote-client/addons.make.norpi example_remote-client/addons.make
mv example_remote-server/addons.make.norpi example_remote-server/addons.make
mv example_simpler/addons.make.norpi example_simpler/addons.make
rm -rf example_gamepad
