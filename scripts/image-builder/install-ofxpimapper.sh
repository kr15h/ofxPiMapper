#!/bin/bash
set -e

# Install and compile ofxPiMapper for Raspberry Pi
# This script is designed to run inside the Raspberry Pi image (via QEMU chroot or natively)

OF_ROOT="/home/pi/openFrameworks"
ADDONS_DIR="$OF_ROOT/addons"
OFXPIMAPPER_DIR="$ADDONS_DIR/ofxPiMapper"

echo "================================"
echo "Installing ofxPiMapper"
echo "================================"

# Ensure openFrameworks is installed
if [ ! -d "$OF_ROOT" ]; then
    echo "Error: openFrameworks not found at $OF_ROOT"
    echo "Please run install-openframeworks.sh first"
    exit 1
fi

cd $ADDONS_DIR

# Clone ofxPiMapper if not already present
if [ ! -d "$OFXPIMAPPER_DIR" ]; then
    echo "Cloning ofxPiMapper..."
    git clone https://github.com/kr15h/ofxPiMapper.git
else
    echo "ofxPiMapper directory already exists"
fi

# Clone dependencies
echo "Installing ofxPiMapper dependencies..."

# ofxOMXPlayer (for Raspberry Pi video playback)
if [ ! -d "$ADDONS_DIR/ofxOMXPlayer" ]; then
    echo "Cloning ofxOMXPlayer..."
    cd $ADDONS_DIR
    git clone https://github.com/jvcleave/ofxOMXPlayer.git
    cd ofxOMXPlayer
    # Use the 0.9.0-compatible release
    git checkout 0.9.0-compatible
else
    echo "ofxOMXPlayer already exists"
fi

# ofxJSON (for remote control functionality)
if [ ! -d "$ADDONS_DIR/ofxJSON" ]; then
    echo "Cloning ofxJSON..."
    cd $ADDONS_DIR
    git clone https://github.com/jeffcrouse/ofxJSON.git
else
    echo "ofxJSON already exists"
fi

# Compile ofxPiMapper example_basic
echo "Compiling ofxPiMapper example_basic..."
cd $OFXPIMAPPER_DIR/example_basic

# Use the correct addons.make for Raspberry Pi
if [ -f "addons.make.rpi" ]; then
    cp addons.make.rpi addons.make
fi

# Compile with optimization
make Release -j$(nproc)

# Verify the binary was created
if [ ! -f "bin/example_basic" ]; then
    echo "Error: Failed to compile example_basic"
    exit 1
fi

echo "Testing compiled binary..."
# Just check if it's executable and can show help
file bin/example_basic

# Create a directory for user projects
mkdir -p /home/pi/ofxPiMapper-projects

# Clean up build artifacts to save space
echo "Cleaning up build artifacts..."
cd $OFXPIMAPPER_DIR
find . -type f -name "*.o" -delete

# Set proper permissions
chown -R pi:pi $ADDONS_DIR
chown -R pi:pi /home/pi/ofxPiMapper-projects

echo "================================"
echo "ofxPiMapper installed successfully!"
echo "Binary location: $OFXPIMAPPER_DIR/example_basic/bin/example_basic"
echo "================================"
