# This fork adds some important functions to PiMapper.
### 1. Slide show function (implemented in master branch):
PiMapper has now a slideshow and plays all images in a folder. There is an integrated directory watcher für updating new added images. Transition and slidetime can be edited via .xml file.

### 2. Circular shapes for mapping (there are only square and tringle shapes so far):
Simple Circular mapping shape (more complex version with movable center might come later)

### 3. Mapping converter:
Finalize the mapping converter, to convert exported .svg from Mapio and Madmapper to ofxPiMapper: https://github.com/magdesign/mapping-converter

### 4. Bezier handles:
Adding bezier handles to masks for better aligment: https://github.com/TsubokuLab/ofxBezierWarpManager
### 5. Play all videos from a folder:
This should be a an additional FBO source in PiMapper, looping all videos in /media/internal/video/*
### 6. Grid Warp (meshing of square shapes):
check out this http://www.hv-a.com/lpmt/sssm.pdf on page: 10
https://forum.openframeworks.cc/t/grid-mesh-warping/12883
### 7. SoftEdge:
Image overlay to making adges transparent, could be achieved with overlaing a png with a black gradient.
### 7. Color Adjustment:
Adjust brightness and contrast.


## Targeting OF_0.9.x on RaspberryPi.
Each function will be rewarded to the coder from a pot sponsered by http://pocketvj.com
Keybindings are edited to match the CP of PocketVJ.

# ofxPiMapper

[![Join the chat at https://gitter.im/kr15h/ofxPiMapper](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/kr15h/ofxPiMapper?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

Projection mapping addon for openFrameworks that runs on the Raspberry Pi.

The project started as master's thesis project by [Krisjanis Rijnieks](https://rijnieks.com) at the [Helsinki Media Lab](https://medialab.aalto.fi/). Currently undergoing changes. Expect the API to be incompatible with your projects from the past or present-day.


## Running the Example

You can use the example application of the addon for projection mapping projects where static images or videos have to be projection mapped. Make sure you are using the **latest stable** version of openFrameworks.

1. Put your own sources in the `example/bin/data/sources` directory. Use [Handbrake](https://handbrake.fr/) with the **Fast 720p30** preset to encode your videos. 

2. Compile and run the example project.
    ```bash
    cd openFrameworks/addons/ofxPiMapper/example
    make && ./bin/example
    ```

3. Use the `-f` flag to launch it fullscreen.
    ```bash
    ./bin/example -f
    ```


## Problems with Audio

If you are having problems with audio playback, here are two steps for you. Before you do these, make sure audio of your video file works.


### Step 1

Open example openFrameworks application `ofApp.cpp` file in a text editor.

```
cd /home/pi/openFrameworks/addons/ofxPiMapper/example
nano src/ofApp.cpp
```

Make sure that the following line looks as follows.

```
ofx::piMapper::VideoSource::enableAudio = true;
```

Save the file (CTRL + X, Y and ENTER). Recompile and run the example.

```
make && make run
```

### Step 2

If the sound still does not work, try to use `raspi-config`.

```
sudo raspi-config
```

Select "7 Advanced Options" and "A9 Audio" then "0 Auto". You can use one of the force options if you want to be 100% sure.

Open alsamixer.

```
alsamixer
```

Set the volume to a value between 90 to 100 by using the arrow keys. ESC to exit the mixer.

Launch ofxPiMapper example, select a surface and set a video source with audio. Should work.


## Development

Keeping it simple. Developing ofxPiMapper master branch against the latest stable release version of openFrameworks. 


## Licence

ofxPiMapper is distributed under the [MIT License](https://en.wikipedia.org/wiki/MIT_License). See the [LICENSE](LICENSE.md) file for further details. Just add my name somewhere along your project [Krisjanis Rijnieks](https://rijnieks.com) whenever possible. And join [my workshops](https://ofxpimapper.com/workshops).


## Dependencies

Before moving on, make sure that you have all the dependencies installed. 

 - ofxGui (available in oF by default)
 - ofxXmlSettings (available in oF by default)
 - [ofxOMXPlayer](https://github.com/jvcleave/ofxOMXPlayer) (needed only on Raspberry Pi)

To install dependencies, `cd` into `openFrameworks/addons` directory and execute the following:

```bash
git clone https://github.com/jvcleave/ofxOMXPlayer.git
```

The `ofxOMXPlayer` addon recommends you to use its releases. Currently the latest release is `0.9.0-compatible`. To checkout the code of the relase, go to the `ofxOMXPlayer` addon directory and checkout the relase.

```
cd openFrameworks/addons/ofxOMXPlayer
git checkout 0.9.0-compatible
```

You can check the latest releases on the [ofxOMXPlayer GitHub repository](https://github.com/jvcleave/ofxOMXPlayer/releases).


## Usage

Currently a keyboard and a mouse has to be used in order to do the mapping with ofxPiMapper.


### Modes

PiMapper has 4 modes:

1. Presentation mode
2. Texture mapping mode
3. Surface editing mode
4. Source assignment mode

You can access these modes by pressing 1, 2, 3 or 4 respectively.


#### Presentation mode

This mode is activated once the application starts up. It does not show anything else except the final projection mapping as it was saved previously.


#### Texture mapping mode

In this mode you can adjust the texture coordinates of the surface you have selected in the surface editing mode.


#### Surface editing mode

Here you can select, move and distort the surfaces you have created.


#### Source assignment mode

After you select a surface in surface editing mode, activate this mode to be able to choose a source for the surface. Afterwards you might want to go to the texture mapping mode to adjust texture coordinates.


### Other shortcuts

These other shortcuts that you can use while using the example app. 

Key | Function
:--- | :---
1 | Presentation mode
2 | Texture editing mode
3 | Projection mapping mode, use this to select a surface first
4 | Source selection mode
c | Show info
t | Add triangle surface
q | Add quad surface
x | Add hexagon surface
g | Add grid warp surface
a | duplicate selected surface
o | Scale surface up
i | Scale surface down
p | toggle perspective warping (quad surfaces only)
v | add columns to grid surface (grid warp surfaces only)
b | remove columns from grid surface (grid warp surfaces only)
n | add rows to grid surface (grid warp surfaces only)
m | remove rows from grid surface (grid warp surfaces only)
. | select next surface (projection mapping mode only)
, | select previous surface (projection mapping mode only)
k | select next vertex
l | select previous vertex
h | Move selected surface one layer up
j | Move selected surface one layer down
s | Save composition
y | Hide/show layer panel
z | Undo
rbt | Reboot (Raspberry Pi only)
sdn | Shutdown (Raspberry Pi only)
new | Clear composition (remove all surfaces)
ext | Exit application and return to command line
d | Delete surface.
w | Toggle pause for video sources (texture and projection mapping modes)
5 | Select next source (no need to use the source selection interface)
8 | Move selection Up
9 | Move selection Down
7 | Move selection Left
0 | Move selection Right
If no surface is selected in the projection mapping mode, all surfaces are moved.

Dont know if this works already:

\/ | Toggle 1px/10px steps for keyboard moves on Raspberry Pi
