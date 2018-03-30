# FBO Sources Example

This example shows how to use custom (FBO) source functionality with ofxPiMapper. Below you can see a list of custom sources and feel free to add your own via pull requests!

- ScanlineSource
- SlideShowSource

To build your own source, one should start by extending the `FboSource` class. When the source is ready, it should be instantiated in the `ofApp` class and passed via `mapper.registerFboSource(...source)` function before the `mapper.setup()` call. This will make the source name to appear under **FBO Sources** category in the source selection mode.

Look at the source code of the custom sources to understand how to build one, but essentially it is extending the `FboSource` class of `ofxPiMapper` and overriding the `setup()`, `update()` and `draw()` functions. 

In the `setup()` function you should set a name for your custom source.

```
name = "Name Your Source";
```

Then you should set the dimensions of your source by using the `allocate()` function.

```
allocate(500, 500);
```

In the `draw()` of your custom `FboSource` you should decide whether you want the previous frame to be cleared from the gfx buffer or not. If you want to draw a fresh frame, use the `ofClear()` function.

```
ofClear(0); // Clear with black
```
