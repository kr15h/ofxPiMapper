![Pi Mapper Logo](piMapperLogo.jpg)

ofxPiMapper
===========

This project is an attempt to create optimized version of an openFrameworks projection mapping addon for the Raspberry Pi. It is also my master thesis project at Aalto University, School of Arts, Design and Architecture (Helsinki Media Lab).

ofxPiMapper is mainly for people who want to use the Raspberry Pi as a cheaper way to create standalone mapping installations. Let's say someone has 10 generative mapping pieces and gets an offer to exhibit them in an art gallery, museum or any other kind of place. 10 Mac computers? No! PiMapper is here to save you!

The addon itself is intended to be flexible as the separate components of it can be reusable. The main example of the addon can be used as a standalone application for experimenting, testing as well as production state of a project. If you need to save memory and processing power, reusing ofxPiMapper classes without adding the GUI layer can help you.

As ofxPiMapper is optimized for the Pi, there is no doubt that it will run smoothly on other machines. It has been tested on OS X so far.

Development
-----------

As the projects gets a bit more popular, I see that people want to add missing features. I have a whole bunch of features that I want to add in future releases, but right now I'm trying to understand how to keep it more or less organized.

Currently I have decided to use [A successful Git branching model](http://nvie.com/posts/a-successful-git-branching-model/) by [Vincent Driessen](https://twitter.com/nvie), so read this article and I do not doubt that it will help you with other Git related projects.

I'm trying to organize the project by adding future release version milestones and assigning specific issues as TODO items to them. If you notice something strange or see that there is something that can be done in a better way, don't hesitate and add an issue.

As of Release 0.2.0 some refractoring has been done (thanks [aspeteRakete](https://github.com/aspeteRakete)), namespaces have been added and we are thinking about introducing a code style for this project. Still improving on the overal structure.

Licence
-------
ofxPiMapper is distributed under the [MIT License](https://en.wikipedia.org/wiki/MIT_License).

Installation
------------
If you don't have a clue on how to set up your Pi - go to the [Raspberry Pi website](http://www.raspberrypi.org/downloads/) and follow the instructions there. I have been using Raspbian so far as well as [Satellite CCRMA](https://ccrma.stanford.edu/~eberdahl/satellite/) without problems.

Another thing you need is a working [openFrameworks](http://openframeworks.cc) installation. Follow [this guide](http://openframeworks.cc/setup/raspberrypi/Raspberry-Pi-Getting-Started.html) to set it up.

Clone this into your `openFrameworks/addons` folder. If your openFrameworks installation on the Pi resides in the home directory, you have to type the following in the terminal:

```bash
cd ~/openFrameworks/addons
git clone https://github.com/kr15h/ofxPiMapper.git
```

Before moving on, make sure that you have all the dependencies installed. Refer to the **Dependencies** section to see what you need. 

To test the addon, you will have to compile and run it:

```bash
cd ~/openFrameworks/addons/ofxPiMapper/example
make
```

After it compiles, run it with either `make run` or `./bin/example`

It will take a while first, but once it runs, press 1, 2, 3 and 4 keys to switch between modes of the software. Switch to mode 3 at first to select a surface. Afterwards you will be able to edit the texture mapping of it in mode 2 and choose a source in mode 4. Mode 1 is the presentation mode. It is activated on start by default.

Usage
-----

I'm thinking on a more clever design that would not require keyboard so much, maybe. Now the example application acts as a wrapper for the ofxPiMapper addon and anyone can re-map keyboard keys by modifying the app code.

###Modes

PiMapper has 4 modes:

1. Presentation mode
2. Texture mapping mode
3. Surface editing mode
4. Source assignment mode

You can access these modes by pressing 1, 2, 3 or 4 respectively.

####Presentation mode

This mode is activated once the application starts up. It does not show anything else except the final projection mapping as it was saved previously.

####Texture mapping mode

In this mode you can adjust the texture coordinates of the surface you have selected in the surface editing mode.

####Surface editing mode

Here you can select, move and distort the surfaces you have created.

####Source assignment mode

After you select a surface in surface editing mode, activate this mode to be able to choose a source for the surface. Afterwards you might want to go to the texture mapping mode to adjust texture coordinates.

###Other shortcuts

These other shortcuts that you can use while using the example app. Remember that you can assign your own by editing the app.cpp file.

Key | Function
:--- | :---
i | Show info
n | Add triangle surface
q | Add quad surface
r | Add random triangle surface
f | Toggle fullscreen
s | Save composition
BACKSPACE | Delete surface

Dependencies
------------
 - ofxGui 
 - ofxXmlSettings
 - [ofxIO](https://github.com/bakercp/ofxIO)
 - [ofxOMXPlayer](https://github.com/jvcleave/ofxOMXPlayer)

To install dependencies, `cd` into `openFrameworks/addons` directory and execute the following:

```
git clone https://github.com/jvcleave/ofxOMXPlayer.git
... many lines inbetween
git clone https://github.com/bakercp/ofxIO.git
... many lines here as well
```

And you are good to go!

Compatibility
------------
Tested with 0.8.1 - 0.8.4 (OS X and Raspbian)

Known issues
------------
Keyboard and mouse input is being lost sometimes on the Raspberry Pi. Not sure how and why. Probably because of bad drivers and it seems that Raspberry Pi keyboard and mouse code in openFrameworks is not quite ready yet. Some claim that the following commands solves the issue:

```
sudo apt-get update && sudo apt-get dist-upgrade  
sudo rpi-update
```

[ofxOMXPlayer](https://github.com/jvcleave/ofxOMXPlayer) has an issue, it throws an error when compiling:

```
fatal error: libavcodec/opt.h: No such file or directory
```

To fix that, create a file `opt.h` in `addons/ofxOMXPlayer/libs/ffmpeg/libavcodec/` with the following contents: 

**opt.h**

```
#ifndef AVCODEC_OPT_H
#define AVCODEC_OPT_H
#include "libavcodec/version.h"
#if FF_API_OPT_H
#include "libavutil/opt.h"
#endif
#endif // AVCODEC_OPT_H
```
   
More about this issue [here](https://github.com/jvcleave/ofxOMXPlayer/issues/34). 

Version history
---------------
###TODO
A short wishlist for the next releases:

 - Refined directoryWatcher mechanism, source lists should react on added and removed files
 - OSC remote control module
 - Even better structure

### Version 0.2.0 (2014-10-18):
 - Added logo (thanks [Irina Spicaka](http://irina.spicaka.info/))
 - Added perspective warping for quad surfaces (thanks [aspeteRakete](https://github.com/aspeteRakete))
 - Added namespaces
 - Replaced ofxUI with ofxGui
 - Added media server (thanks [aspeteRakete](https://github.com/aspeteRakete))
 - Added source types and reworked all relevant classes to support them instead of ofTexture directly
 - Added video source (based on [ofxOMXPlayer](https://github.com/jvcleave/ofxOMXPlayer))

### Version 0.1.4 (2014-07-10):
 - Added fbo texture example
 - Replaced the main example with the fbo texture one
 - Added simple quad surface
 - Fixed a couple of bugs
 - Introduced new branching model
 - Added joint snapping
 - Improved README

### Version 0.1.3 (2014-05-16):
 - Added sources view (for selected surface)
 - Added possibility to select image sources
 - Save and load surfaces with image sources
 - Joint and surface movement using arrow keys
 - Added fullscreen toggle
 - Adjusted the example to work with new changes

### Version 0.1.2 (2014-05-12):
Restructured GUI mechanism for flexibility later.
 - Added possibility to add multiple surfaces
 - Add GUI for surface manager instead per surface
 - Ability to select and drag whole surfaces as well as select/deselect surfaces

### Version 0.1.1 (2014-05-10):
Added simple GUI with joints. Updated the example application so that it allows the user to do texture mapping, projection mapping and enter presentation mode.

### Version 0.1 (2014-05-09):
First usable version. For now there is a triangle surface class that you can use to map an ofTexture object. 
 - Added triangle surface
 - Added simple example
