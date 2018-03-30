# Base Example

This example shows how to use custom (FBO) source functionality with ofxPiMapper. Below you can see a list of custom sources and feel free to add your own via pull requests!

- ScanlineSource
- SlideShowSource

To build your own source, one should start by extending the `FboSource` class. When the source is ready, it should be instantiated in the `ofApp` class and passed via `mapper.registerFboSource(...source)` function before the `mapper.setup()` call. This will make the source name to appear under **FBO Sources** category in the source selection mode.
