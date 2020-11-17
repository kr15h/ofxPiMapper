#!/bin/bash

echo "This script should be run from the patches/msys2 directory"

cp --force ./sound/ofOpenALSoundPlayer.* ../../../../libs/openFrameworks/sound/
cp --force ./makefileCommon/config.addons.mk ../../../../libs/openFrameworksCompiled/project/makefileCommon/config.addons.mk

echo "Patch for msys2 complete"
