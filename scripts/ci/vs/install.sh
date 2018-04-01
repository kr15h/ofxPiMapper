#!/usr/bin/env bash

- /usr/bin/pwd
- /usr/bin/git clone --depth=1 -b of-master-patch https://github.com/kr15h/ofxJSON addons/ofxJSON 
- /usr/bin/mv addons/%APPVEYOR_PROJECT_NAME%/example_basic/addons.make.norpi addons/%APPVEYOR_PROJECT_NAME%/example_basic/addons.make
- /usr/bin/mv addons/%APPVEYOR_PROJECT_NAME%/example_camera/addons.make.norpi addons/%APPVEYOR_PROJECT_NAME%/example_camera/addons.make
- /usr/bin/mv addons/%APPVEYOR_PROJECT_NAME%/example_fbo-sources/addons.make.norpi addons/%APPVEYOR_PROJECT_NAME%/example_fbo-sources/addons.make
- /usr/bin/mv addons/%APPVEYOR_PROJECT_NAME%/example_pocketvj/addons.make.norpi addons/%APPVEYOR_PROJECT_NAME%/example_pocketvj/addons.make
- /usr/bin/mv addons/%APPVEYOR_PROJECT_NAME%/example_remote-client/addons.make.norpi addons/%APPVEYOR_PROJECT_NAME%/example_remote-client/addons.make
- /usr/bin/mv addons/%APPVEYOR_PROJECT_NAME%/example_remote-server/addons.make.norpi addons/%APPVEYOR_PROJECT_NAME%/example_remote-server/addons.make
- /usr/bin/mv addons/%APPVEYOR_PROJECT_NAME%/example_simpler/addons.make.norpi addons/%APPVEYOR_PROJECT_NAME%/example_simpler/addons.make
- /usr/bin/rm -rf addons/%APPVEYOR_PROJECT_NAME%/example_gamepad
