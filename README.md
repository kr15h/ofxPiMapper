ofxPiMapper
===========

This project is an attempt to create optimized version of an openFrameworks projection mapping addon for the Raspberry Pi. 

ofxPiMapper is mainly intended for people who want to use the Raspberry Pi as a cheaper way to create standalone mapping installations. Let's say someone has 10 generative mapping pieces and at last get's an offer to exhibit them in an art or any other kind of gallery. 10 Mac computers? No! PiMapper is here to save you!

The addon itself is intended to be flexible as the separate components of it can be reusable. Use the full version of it to set up your mapping and then switch to no-gui version once everything is set up to save processor power and memory.

As ofxPiMapper is optimized for the Pi, there is no doubt that it will run smoothly on other machines. It has been tested on OS X.

Licence
-------
ofxPiMapper is distributed under the [MIT License](https://en.wikipedia.org/wiki/MIT_License).

Installation
------------
Clone this into your `openFrameworks/addons` folder. If your openFrameworks installation on the Pi resides in the home directory, you have to type the following in the terminal:

```bash
cd ~/openFrameworks/addons
git clone https://github.com/kr15h/ofxPiMapper.git
```

To test the addon, you will have to compile and run it:

```bash
cd ~/openFrameworks/addons/ofxPiMapper/example
make && make run
```

It will take a while first, but once it runs, press 1, 2, 3 and 4 keys to switch between modes of the software. Switch to mode 3 at first to select a surface. Afterwards you will be able to edit the texture mapping of it in mode 2 and choose a source in mode 4. Mode 1 is the presentation mode. It is activated on start by default.

Dependencies
------------
[ofxUI](https://github.com/rezaali/ofxUI) - will be replaced with custom solution as it consumes a lot of processing power.  
ofxXmlSettings

Compatibility
------------
Tested with 0.8.0, 0.8.1 (OS X and Raspbian)

Known issues
------------
When launching the example with `make run` keyboard and mouse input is being lost sometimes. Executing the example directly by using `./bin/example` might solve the problem. Not sure how and why.

Version history
------------

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
