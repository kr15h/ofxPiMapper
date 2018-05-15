#!/bin/bash

echo "Begin prepare-script.sh"

echo "Installing extra packages."
sudo apt-get -yq install usbmount dosfstools exfat-fuse exfat-utils

echo "Setting hostname."
echo "opm" > /etc/hostname
cat /etc/hostname

echo "Setting up to run on boot."
crontab -l > mycron
echo "@reboot /home/pi/openFrameworks/addons/ofxPiMapper/example_basic/bin/example_basic" >> mycron
crontab mycron
rm mycron

echo "End prepare-script.sh"
