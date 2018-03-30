# Basic Example

This is a very basic example. It shows how to use ofxPiMapper addon with it's integrated functionality. You can map images and videos with this. ofxPiMapper takes care of loading and saving your composition.

For now you have to put your sources under `bin/data/sources`. There are two directories: `images` and `videos`. As you may expect, put images in the `images` folder and videos in the `videos` one. 

The addon is made so that you have to pass the keyboard and mouse events to it. It is because in this way you can gain more control over how it behaves. If you do not pass the keyboard and mouse events, ofxPiMapper reads the configuration file from `data/ofxpimapper.xml` and continues working from there. It just starts up, loads the configuration and displays the composition util the application quits. 
