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

### 1.2. Set up auto login

Edit the `inittab` file of your system.

```bash
sudo nano /etc/inittab
```

Replace the line `1:2345:respawn:/sbin/getty 115200 tty1` with the one below.

```bash
1:2345:respawn:/bin/login -f pi tty1 /dev/tty1 2>&1
```

### 1.3. Create a startup script

Execute the following commands one by one.

```bash
cd /home/pi
touch startup.sh
chmod a+x startup.sh
```

Open `startup.sh` in a text editor.

```bash
nano startup.sh
```

Copy and paste the following lines there.

```bash
#!/bin/bash

echo "Checking SSH connection...";
if [ -z "$SSH_CONNECTION" ]; then
  echo "No SSH connection, launching scripts.";

  # Launch the ofxPiMapper example compiled binary fullscreen
  /home/pi/openFrameworks/addons/ofxPiMapper/example/bin/example -f
else
  echo "SSH connection, nothing to be launched.";
fi
```

### 1.4. Launch `startup.sh` on auto login

Open `.bashrc` in a text editor.

```bash
cd /home/pi
sudo nano .bashrc
```

At the end of the `.bashrc` file add the path to the `startup.sh` file.

```bash
/home/pi/startup.sh
```

Restart your Pi and your application should be launched automatically.

### 1.5. Preventing the screen from going blank

It might happen that the screen goes blank as the system tries to save energy as there is no mouse or keyboard connected. To avoid this from happening, open `rc.local` in a text editor.

```bash
sudo nano /etc/rc.local
```

Add the following just **BEFORE** the `exit 0` line.

```bash
sh -c 'setterm -blank 0 -powersave off -powerdown 0 < /dev/console > /dev/console 2>&1'
```

