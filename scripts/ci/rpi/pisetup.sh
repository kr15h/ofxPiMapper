#!/bin/bash

echo "Hello! Me is pisetup.sh script."

pwd

cd /home/pi/openFrameworks/addons
git clone --depth=1 https://github.com/jeffcrouse/ofxJSON.git

if [ -e "ofxOMXPlayer" ]; then
    rm -rf ofxOMXPlayer
fi

git clone https://github.com/kr15h/ofxOMXPlayerLite.git
mv ofxOMXPlayerLite ofxOMXPlayer

cd ofxPiMapper/example_basic
make -j$(nproc)

echo "Setting hostname."
echo "opm" > /etc/hostname
cat /etc/hostname

echo "Setting up to run on boot."
crontab -l > mycron
echo "@reboot /home/pi/openFrameworks/addons/ofxPiMapper/example_basic/bin/example_basic" >> mycron
crontab mycron
rm mycron

echo "Done!"
