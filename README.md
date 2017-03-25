# ofxPiMapper

[![Build status](https://ci.appveyor.com/api/projects/status/github/kr15h/ofxPiMapper?branch=master&svg=true&passingText=vs-passing&failingText=vs-failing&pendingText=vs-pending)](https://ci.appveyor.com/project/kr15h/ofxPiMapper/branch/master)
[![Build Status](https://travis-ci.org/kr15h/ofxPiMapper.svg?branch=master)](https://travis-ci.org/kr15h/ofxPiMapper)
[![Join the chat at https://gitter.im/kr15h/ofxPiMapper](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/kr15h/ofxPiMapper?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

OfxPiMapper is there for people who want to use the Raspberry Pi to create standalone projection mapping installations and beyond. Say someone has 10 generative mapping pieces and gets an offer to exhibit them in an art gallery, museum or similar space. Ten expensive computers? No! OfxPiMapper is here to save you!

Make sure you use the `stable` branch if you downloaded openFrameworks from the [openFrameworks website](http://openframeworks.cc). The `master` branch aligns with the current `master` branch of the [openFrameworks GitHub repository](https://github.com/openframeworks/openframeworks).

The project started as master's thesis project by [Krisjanis Rijnieks](https://rijnieks.com) at the [Helsinki Media Lab](https://medialab.aalto.fi/). Currently undergoing changes. Expect the API to be incompatible with your projects from the past or present-day.


## Features

The following is a list of key features ofxPiMapper has.

 - **Open Source**  
   You can use ofxPiMapper free of charge, the only requirement being adding reference to the authors of the project somewhere. Consult the [LICENSE.md](LICENSE.md) file.
 - **Simple User Interface**  
   The user interface of ofxPiMapper has been designed by keeping in mind that there is only one screen, a keyboard and a mouse.
 - **Out of the Box**  
   You can use the example project for simple projection mapping projects with image or video sources out of the box.
 - **Customizable**  
   Use ofxPiMapper as an addon and enjoy the power of custom generative sources by extending the `FboSource` class. 
 - **Undoable**  
   Since version 0.2.3 ofxPiMapper supports undo. 
 - **Nerd Remote Control via SSH (not working at the moment)**
   All the functions can be triggered by using the keyboard and via SSH CLI connection. See [SSH Remote Control](#ssh-remote-control) section to learn more.
 - **More to Come**  
   Expect more conventional projection mapping software features to be implemented.


## Running the Example

You can use the example application of the addon for simple projection mapping projects where static images or videos have to be projection mapped. 

1. Put your own sources in the `example/bin/data/sources` directory.

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

If you are having problems with audio playback, here are two steps for you. Before you do these, make sure audio of your video file works. Use [HandBrake](https://handbrake.fr/) for encoding, use the "Fast 720p30" or "Fast 1080p30" preset.

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


## Using as an Addon

OfxPiMapper features FBO sources that allow you to create generative openFrameworks patches to be used with ofxPiMapper. Extend the `FboSource` class, override `setup()`, `update()` and `draw()` methods and then create an instance of your custom source to add it to your ofxPiMapper object.

Reuse the `example` app by copying it to your `apps` directory.

```bash
cp -R openFrameworks/addons/ofxPiMapper/example openFrameworks/apps/myApps/
cd openFrameworks/apps/myApps
mv example myOfxPiMapperApp
```


## Licence

ofxPiMapper is distributed under the [MIT License](https://en.wikipedia.org/wiki/MIT_License). See the [LICENSE](LICENSE.md) file for further details.


## Installation

To set up your Raspberry Pi, go to the [Raspberry Pi website](http://www.raspberrypi.org/downloads/) and follow the instructions there.

Another thing you need is a working [openFrameworks](http://openframeworks.cc) installation. Follow the guide to set up your Raspberry Pi.
 
 - [Raspberry Pi oF Setup Guide](http://openframeworks.cc/setup/raspberrypi/Raspberry-Pi-Getting-Started.html)

Clone this (the ofxPiMapper) repository into your `openFrameworks/addons` folder. If your openFrameworks installation on the Pi resides in the home directory, you have to type the following in the terminal:

```bash
cd ~/openFrameworks/addons
git clone https://github.com/kr15h/ofxPiMapper.git
```


## Dependencies

- ofxGui
- ofxXmlSettings


## Usage

Right now a keyboard and a mouse has to be used in order to do the mapping with ofxPiMapper. It is possible to define your own shortcuts by making your own app and using ofxPiMapper as an addon.

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
i | Show info
t | Add triangle surface
q | Add quad surface
g | Add grid warp surface
d | duplicate surface
\+ | Scale surface up
\- | Scale surface down
p | toggle perspective warping (quad surfaces only)
] | add columns to grid surface (grid warp surfaces only)
[ | remove columns from grid surface (grid warp surfaces only)
} | add rows to grid surface (grid warp surfaces only)
{ | remove rows from grid surface (grid warp surfaces only)
. | select next surface (projection mapping mode only)
, | select previous surface (projection mapping mode only)
\> | select next vertex
\< | select previous vertex
0 | Move selected surface one layer up
9 | Move selected surface one layer down
s | Save composition
l | Hide/show layer panel
z | Undo
x | Reboot (Raspberry Pi only)
c | Shutdown (Raspberry Pi only)
BACKSPACE ('\' via SSH) | Delete surface.
SPACE | Toggle pause for video sources (texture and projection mapping modes)
TAB | Select next source (no need to use the source selection interface)
Arrow keys | Move selection. If no surface is selected in the projection mapping mode, all surfaces are moved.
