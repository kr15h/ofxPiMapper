#!/bin/bash

echo "Compiling addons."

cd /home/pi/openFrameworks/addons/ofxOMXPlayer/example-basic
make -j $(nproc)

cd /home/pi/openFrameworks/addons/ofxJSON/example_file_read_write
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

echo "Compiling addons done!"
