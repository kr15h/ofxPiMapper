# Base Example

This example demonstrates basic functionality of ofxPiMapper.

- Adding and editing mapping surfaces
- Texture cropping
- Video and image source
- Generative FBO sources
- Default keyboard shortcuts

Click once to enter projection mapping mode. Then click and click to do the mapping. The `src/CrossSource` and `src/CustomSource` classes are custom FBO source examples. You can re-use them as starting points for your own generative, data-driven or interactive sources.

There should be no problem compiling this on the Raspberry Pi. On other systems supporting **make** one should change the `addons.make` file and remove the `ofxOMXPlayer` line. For Mac OS with openFrameworks 0.9.8, delete the `ofxGui` files that are marked red from the project pane under `addons/ofxGui`.
