ofxPiMapper Changelog
===

Version 0.2.5 (2015-10-26)
---
 - Fix bugs related to FBO sources (this release is mainly because of this)
 - Made use of the state pattern, not fully implemented yet
 - Added a couple of missing commands with undo support
 - Changed logo

Version 0.2.4 (2015-05-31)
---
 - Fix RPi compile bug
 
Version 0.2.3 (2015-05-22)
---
 - Add undo functionality

Version 0.2.2 (2014-11-17)
---
 - Remove perspective warping in favour of doing mesh warping first and then adding proper perspective warping as a wrapper of the mesh warp
 - Fixed issue 24 (selected surface FBO source not checked in the sources editor view)
 - Fix OMX player workaround instructions

Version 0.2.1 (2014-11-05)
---
 - Added single instance feature. Now you can use ofxPiMapper as single object for your project.
 - Added FBO source. You can create a custom openFrameworks application for piMapper by extending the FboSource class. Add/register your custom object as source in piMapper and you will be able to select it in the source editor. Source is saved and loaded from the settings as well.
 - Fixed issue #15
 - Added -f (fullscreen) flag for the Raspberry Pi version. Use `./yourApp -f` to launch it fullscreen on start.
 - Added XCode project file to example.

Version 0.2.0 (2014-10-18)
 - Added logo (thanks [Irina Spicaka](http://irina.spicaka.info/))
 - Added perspective warping for quad surfaces (thanks [aspeteRakete](https://github.com/aspeteRakete))
 - Added namespaces
 - Replaced ofxUI with ofxGui
 - Added media server (thanks [aspeteRakete](https://github.com/aspeteRakete))
 - Added source types and reworked all relevant classes to support them instead of ofTexture directly
 - Added video source (based on [ofxOMXPlayer](https://github.com/jvcleave/ofxOMXPlayer))

Version 0.1.4 (2014-07-10)
---
 - Added fbo texture example
 - Replaced the main example with the fbo texture one
 - Added simple quad surface (thanks [sebllll](https://github.com/sebllll))
 - Fixed a couple of bugs
 - Introduced new branching model
 - Added joint snapping
 - Improved README

Version 0.1.3 (2014-05-16)
---
 - Added sources view (for selected surface)
 - Added possibility to select image sources
 - Save and load surfaces with image sources
 - Joint and surface movement using arrow keys
 - Added fullscreen toggle
 - Adjusted the example to work with new changes

Version 0.1.2 (2014-05-12)
---
Restructured GUI mechanism for flexibility later.
 - Added possibility to add multiple surfaces
 - Add GUI for surface manager instead per surface
 - Ability to select and drag whole surfaces as well as select/deselect surfaces

Version 0.1.1 (2014-05-10)
---
Added simple GUI with joints. Updated the example application so that it allows the user to do texture mapping, projection mapping and enter presentation mode.

Version 0.1.0 (2014-05-09)
---
First usable version. For now there is a triangle surface class that you can use to map an ofTexture object. 
 - Added triangle surface
 - Added simple example
