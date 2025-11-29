#!/bin/bash
set -e

# Install and compile openFrameworks for Raspberry Pi
# This script is designed to run inside the Raspberry Pi image (via QEMU chroot or natively)

OF_VERSION="0.11.2"
OF_ROOT="/home/pi/openFrameworks"

echo "================================"
echo "Installing openFrameworks ${OF_VERSION}"
echo "================================"

# Update package lists
apt-get update

# Install dependencies
echo "Installing build dependencies..."
apt-get install -y \
    build-essential \
    git \
    cmake \
    libasound2-dev \
    libgstreamer1.0-dev \
    libgstreamer-plugins-base1.0-dev \
    gstreamer1.0-libav \
    gstreamer1.0-plugins-bad \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-ugly \
    gstreamer1.0-tools \
    libgles2-mesa-dev \
    libegl1-mesa-dev \
    libglfw3-dev \
    libglu1-mesa-dev \
    libmpg123-dev \
    libopus-dev \
    libpulse-dev \
    libsndfile1-dev \
    libudev-dev \
    libusb-1.0-0-dev \
    libx11-dev \
    libxcursor-dev \
    libxi-dev \
    libxinerama-dev \
    libxrandr-dev \
    libxxf86vm-dev \
    pkg-config \
    freeglut3-dev \
    libcairo2-dev \
    libfreetype6-dev \
    libssl-dev \
    libpugixml-dev \
    libglfw3-dev \
    liburiparser-dev \
    libcurl4-openssl-dev \
    libgtk-3-dev

# For video playback on Raspberry Pi OS (Bullseye and newer)
apt-get install -y \
    libavcodec-dev \
    libavformat-dev \
    libavutil-dev \
    libswscale-dev \
    libavresample-dev

# For USB automount support
apt-get install -y \
    usbmount \
    pmount \
    exfat-fuse \
    exfat-utils \
    ntfs-3g

echo "Downloading openFrameworks ${OF_VERSION}..."
cd /home/pi

# Download openFrameworks for ARM
if [ ! -d "$OF_ROOT" ]; then
    wget -O of.tar.gz "https://github.com/openframeworks/openFrameworks/releases/download/${OF_VERSION}/of_v${OF_VERSION}_linuxarmv6l_release.tar.gz"
    tar -xzf of.tar.gz
    mv of_v${OF_VERSION}_linuxarmv6l_release openFrameworks
    rm of.tar.gz
else
    echo "openFrameworks directory already exists, skipping download"
fi

cd $OF_ROOT

echo "Compiling openFrameworks..."
# Run the install scripts
cd scripts/linux/debian
./install_dependencies.sh -y

cd $OF_ROOT

# Compile openFrameworks core
echo "Compiling openFrameworks core libraries..."
cd libs/openFrameworksCompiled/project
make Release -j$(nproc)

# Test compilation with a simple example
echo "Testing openFrameworks installation..."
cd $OF_ROOT/examples/graphics/polygonExample
make Release -j$(nproc)

# Clean up build artifacts to save space
cd $OF_ROOT
find . -type f -name "*.o" -delete
find . -type f -name "*.a" | grep -v "openFrameworks.a" | xargs rm -f

# Set permissions
chown -R pi:pi $OF_ROOT

echo "================================"
echo "openFrameworks installed successfully!"
echo "================================"
