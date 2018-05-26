# Gamepad Example

This example demonstrates how to use SDL2 with ofxPiMapper in order to use gamepad for mapping. Below is what you have to do.

## Install SDL2

```
sudo apt-get update
sudo apt-get -y install libsdl2-dev
```

In order to compile the example, one has to add extra compiler flags (see `config.make`). 

```
PROJECT_LDFLAGS += -I/usr/include/SDL2 -lSDL2
```

What it does is the following: `-I/usr/include/SDL2` includes SDL2, `-lSDL2` links our program against it.

**Note:** This is tested on Raspberry Pi so far. 

## Define Game Controller

On each system a speciffic controller will have a different GUID. When `example_gamepad` is launched, it reads connected USB game controllers.

```
Joystick INIT success
Joystick num axes: 2
Joystick ID: 0
Joystick Name: usb gamepad
Joystick GUID: 030000001008000001e5000010010000
```

Use this to add another config block in `controllers.xml`


