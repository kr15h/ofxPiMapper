# Frequently Asked Questions

This document might contain answers to your questions regarding ofxPiMapper and life in general.

## 1. How to launch ofxPiMapper on boot?

It depends whether you are using the addon example or are integrating ofxPiMapper into your application. In both cases you will have to run `make` to compile the binary.

### 1.1. Compile

Make sure that you understand whether you are using the example or building your own. Use `cd` to navigate to your project directory on the Raspberry Pi. In case you are using the example, the command to use should be similar to the following.

```bash
cd /home/pi/openFrameworks/addons/ofxPiMapper/example
```

Compile. Run the following command to do that.

```bash
make
```

The compiled binary of the application should appear in the `bin` directory of the project. Run the following command to launch the application.

```bash
/home/pi/openFrameworks/addons/ofxPiMapper/example/bin/example
```

### 1.2. Set up Cron

Cron is a job scheduler on UNIX-like systems. We are going to use the super user crontab to launch ofxPiMapper on boot. Use the following command to edit the crontab.

```bash
sudo crontab -e
```

If using it for the first time, you will be prompted to choose the text editor you want to use. Select "nano". Proceed. Add the following line in the file.

```
@reboot /home/pi/openFrameworks/addons/ofxPiMapper/example/bin/example
```

Hit `ctrl` + `x` to exit. Hit `y` to confirm changes of the file and `enter` to confirm the existing name of the file.

Congratulations! OfxPiMapper should start up after next system reboot.

