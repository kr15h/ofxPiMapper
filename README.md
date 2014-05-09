ofxPiMapper
===========

This project is an attempt to create optimized version of an openFrameworks projection mapping addon for the Raspberry Pi. 

Introduction
------------
ofxPiMapper is mainly intended for people who want to use the Raspberry Pi as a cheaper way to create standalone mapping installations. Let's say someone has 10 generative mapping pieces and at last get's an offer to exhibit them in an art or any other kind of gallery. 10 Mac computers? No! PiMapper is here to save you!

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

Dependencies
------------
None so far.

Compatibility
------------
Tested with 0.8.0, 0.8.1

Known issues
------------
None so far.

Version history
------------

### Version 0.1 (2014-05-09):
First usable version. For now there is a triangle surface class that you can use to map an ofTexture object. 
 - Added triangle surface
 - Added simple example
