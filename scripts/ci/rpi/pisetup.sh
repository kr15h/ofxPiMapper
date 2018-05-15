#!/bin/bash

echo "Hello! Me is pisetup.sh script."

sudo apt-get -yq install usbmount dosfstools exfat-fuse exfat-utils

pwd
df -h

cd /home/pi/openFrameworks/addons/ofxPiMapper/example_basic
make -j$(nproc)

echo "Setting hostname."
echo "opm" > /etc/hostname
cat /etc/hostname

echo "Setting up to run on boot."
crontab -l > mycron
echo "@reboot /home/pi/openFrameworks/addons/ofxPiMapper/example_basic/bin/example_basic" >> mycron
crontab mycron
rm mycron

echo "RPi setup done!"
