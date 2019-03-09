#!/bin/bash

OFX_DIR="ofx"

cd /home/pi/${OFX_DIR}/addons/ofxPiMapper/example_basic/bin/data/sources

# Create temp dirs for default sources
mkdir videos_temp
mkdir images_temp

# Move default sources to temp dirs
mv videos/gene* videos_temp/
mv images/gene* images_temp/

# Delete non-default sources
rm videos/*
rm images/*

# Move default sources back
mv videos_temp/* videos/
mv images_temp/* images/

# Clean temp dirs
rmdir videos_temp
rmdir images_temp

# Copy valid video sources
cp /media/usb*/*.mp4 videos/
cp /media/usb*/*.mov videos/
cp /media/usb*/*.mkv videos/

# Copy valid image source
cp /media/usb*/*.jpg images/
cp /media/usb*/*.jpeg images/
cp /media/usb*/*.png images/

# Finally, launch mapper
/home/pi/${OFX_DIR}/addons/ofxPiMapper/example_basic/bin/example_basic
