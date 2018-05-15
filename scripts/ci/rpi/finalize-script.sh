#!/bin/bash

echo "Finalizing OPM RPi image."

cd /home/pi/openFrameworks/addons/ofxPiMapper/example_basic
make -j $(nproc)

echo "Inastalling extra packages."
sudo apt-get -yq install usbmount dosfstools exfat-fuse exfat-utils

echo "Setting hostname."
echo "opm" > /etc/hostname
cat /etc/hostname

echo "Setting up to run on boot."
crontab -l > mycron
echo "@reboot /home/pi/openFrameworks/addons/ofxPiMapper/example_basic/bin/example_basic" >> mycron
crontab mycron
rm mycron

echo "OPM RPi image setup done!"
