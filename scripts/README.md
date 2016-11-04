#ofxPiMapper Scripts

This directory contains useful scripts to be used to autorun and keep alive your projection mapping application.


## keepalive-example.sh

This script launches and keeps alive the example application. 

1. Copy it to your home directory.
   ```
   cp keepalive-example.sh ~/keepalive-example.sh
   ```
2. Set exec permissions.
   ```
   chmod a+x keepalive-example.sh
   ```
3. Run `crontab -e` and add the following lines to make use of it.
   ```
   @reboot /home/pi/keepalive-example.sh
   * * * * * /home/pi/keepalive-example.sh
   ```


## keepalive-example-camera.sh

This script launches and keeps alive the example-camera application.

1. Copy it to your home directory.
   ```
   cp keepalive-example-camera.sh ~/keepalive-example-camera.sh
   ```
2. Set exec permissions.
   ```
   chmod a+x keepalive-example-camera.sh
   ```
3. Run `crontab -e` and add the following lines to make use of it.
   ```
   @reboot /home/pi/keepalive-example-camera.sh
   * * * * * /home/pi/keepalive-example-camera.sh
   ```
