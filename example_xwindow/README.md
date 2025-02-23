# X Window Example

This example is very delicate. Here are some issues:

- Cross Platform: Since this uses `ofGstUtils` (gstreamer), it will not work on windows. It wouldn't too hard to try and extend this to use a different OF [video backend](https://github.com/openframeworks/openFrameworks/tree/master/libs/openFrameworks/video) one
- Messing with the X Window too much; Resize and Fullscreen. Its fine if you don't mess with it after it starts.

This example also removes any sources that no longer exist. I bet it'll be frustrating to setup as the whole source is removed if the x window isn't found deleting any mapping progress. Read the logs to see what is going on with the capture status.

There is no audio and no keyboard or mouse event passing. The idea is that those things will come from the X Window itself.

Enjoy! :)

![Demo](xwindow.gif)

Since my desktop uses wayland I tricked mozilla and the example to start in the same session using:

`WAYLAND_DISPLAY= XDG_SESSION_TYPE=x11 DISPLAY=:0 firefox-esr`

&

`WAYLAND_DISPLAY= XDG_SESSION_TYPE=x11 DISPLAY=:0 ./example_xwindow`

