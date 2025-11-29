#!/bin/bash

# Load media files from USB drives into ofxPiMapper source directories
# This script is called before ofxPiMapper starts via systemd

MEDIA_DIR="/home/pi/media"
OFXPIMAPPER_DIR="/home/pi/openFrameworks/addons/ofxPiMapper/example_basic/bin/data/sources"
VIDEOS_DIR="$OFXPIMAPPER_DIR/videos"
IMAGES_DIR="$OFXPIMAPPER_DIR/images"

# Ensure directories exist
mkdir -p "$VIDEOS_DIR"
mkdir -p "$IMAGES_DIR"
mkdir -p "$MEDIA_DIR/videos"
mkdir -p "$MEDIA_DIR/images"

# Function to copy media files
copy_media() {
    local source_dir=$1
    local dest_dir=$2
    local pattern=$3

    if [ -d "$source_dir" ]; then
        find "$source_dir" -maxdepth 1 -type f -iname "$pattern" -exec cp {} "$dest_dir/" \; 2>/dev/null || true
    fi
}

# Copy from local media directory
echo "Loading media from $MEDIA_DIR..."
copy_media "$MEDIA_DIR/videos" "$VIDEOS_DIR" "*.mp4"
copy_media "$MEDIA_DIR/videos" "$VIDEOS_DIR" "*.mov"
copy_media "$MEDIA_DIR/videos" "$VIDEOS_DIR" "*.mkv"
copy_media "$MEDIA_DIR/videos" "$VIDEOS_DIR" "*.avi"
copy_media "$MEDIA_DIR/images" "$IMAGES_DIR" "*.jpg"
copy_media "$MEDIA_DIR/images" "$IMAGES_DIR" "*.jpeg"
copy_media "$MEDIA_DIR/images" "$IMAGES_DIR" "*.png"
copy_media "$MEDIA_DIR/images" "$IMAGES_DIR" "*.gif"

# Check for USB drives and copy media
for usb_mount in /media/usb*; do
    if mountpoint -q "$usb_mount" 2>/dev/null; then
        echo "Found USB drive at $usb_mount"

        # Copy videos from USB
        copy_media "$usb_mount/videos" "$VIDEOS_DIR" "*.mp4"
        copy_media "$usb_mount/videos" "$VIDEOS_DIR" "*.mov"
        copy_media "$usb_mount/videos" "$VIDEOS_DIR" "*.mkv"
        copy_media "$usb_mount/videos" "$VIDEOS_DIR" "*.avi"
        copy_media "$usb_mount" "$VIDEOS_DIR" "*.mp4"
        copy_media "$usb_mount" "$VIDEOS_DIR" "*.mov"
        copy_media "$usb_mount" "$VIDEOS_DIR" "*.mkv"

        # Copy images from USB
        copy_media "$usb_mount/images" "$IMAGES_DIR" "*.jpg"
        copy_media "$usb_mount/images" "$IMAGES_DIR" "*.jpeg"
        copy_media "$usb_mount/images" "$IMAGES_DIR" "*.png"
        copy_media "$usb_mount/images" "$IMAGES_DIR" "*.gif"
        copy_media "$usb_mount" "$IMAGES_DIR" "*.jpg"
        copy_media "$usb_mount" "$IMAGES_DIR" "*.jpeg"
        copy_media "$usb_mount" "$IMAGES_DIR" "*.png"
    fi
done

# Set permissions
chown -R pi:pi "$OFXPIMAPPER_DIR"

echo "Media loading complete"
exit 0
