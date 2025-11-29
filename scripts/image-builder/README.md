# Raspberry Pi Disk Image Builder for ofxPiMapper

This directory contains scripts and configurations for building prebuilt Raspberry Pi disk images for ofxPiMapper that work with Raspberry Pi 4 and newer models.

## Overview

The image builder creates a ready-to-use Raspberry Pi OS image with:
- Raspberry Pi OS Lite (latest 64-bit for Pi 4/5 support)
- Compiled openFrameworks 0.11.2
- ofxPiMapper example_basic precompiled
- All dependencies (ofxOMXPlayer, ofxJSON)
- Autostart configuration via systemd
- USB media support for videos and images
- Optimized settings for projection mapping

## Prerequisites

### On Linux (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install -y \
    qemu-user-static \
    binfmt-support \
    parted \
    kpartx \
    wget \
    zip \
    dosfstools \
    qemu-utils \
    git
```

### On macOS

```bash
brew install qemu
```

### Using Docker (Recommended - Cross-Platform)

Docker is the recommended method as it provides a consistent build environment:

```bash
# Install Docker from https://docs.docker.com/get-docker/
```

## Build Methods

### Method 1: Using Packer (Recommended)

Packer automates the entire image building process.

#### Install Packer

```bash
# Linux/macOS
wget https://releases.hashicorp.com/packer/1.10.0/packer_1.10.0_linux_amd64.zip
unzip packer_1.10.0_linux_amd64.zip
sudo mv packer /usr/local/bin/
```

#### Build the Image

```bash
cd scripts/image-builder
packer build raspberry-pi.pkr.hcl
```

The output will be `output/ofxpimapper-rpi4-<version>.img.zip`

### Method 2: Using pi-gen (Official Raspberry Pi Builder)

For more customization, use the official pi-gen tool:

```bash
cd scripts/image-builder
./build-with-pigen.sh
```

### Method 3: Manual Build with QEMU

For development and testing:

```bash
cd scripts/image-builder
sudo ./build-manual.sh
```

## Build Process Details

### Stage 1: Base System
1. Downloads latest Raspberry Pi OS Lite 64-bit image
2. Expands the image to 8GB for compilation space
3. Mounts the image using loopback device
4. Sets up QEMU ARM emulation for chroot

### Stage 2: Dependencies
1. Updates system packages
2. Installs build tools and libraries
3. Clones and compiles openFrameworks 0.11.2
4. Installs ofxPiMapper dependencies:
   - ofxOMXPlayer (for video playback)
   - ofxJSON (for remote control)

### Stage 3: Application
1. Copies ofxPiMapper source code
2. Compiles example_basic application
3. Optimizes binary for Pi 4/5

### Stage 4: Configuration
1. Installs systemd service for autostart
2. Configures USB automount for media
3. Sets hostname to `ofxpimapper`
4. Enables GPU memory split (256MB for graphics)
5. Disables unnecessary services
6. Optimizes boot time

### Stage 5: Finalization
1. Cleans up build artifacts
2. Shrinks image to minimal size
3. Compresses to ZIP format

## Configuration Files

- `raspberry-pi.pkr.hcl` - Packer configuration for automated builds
- `install-openframeworks.sh` - Script to install and compile openFrameworks
- `install-ofxpimapper.sh` - Script to install and compile ofxPiMapper
- `configure-system.sh` - System configuration and optimization
- `ofxpimapper.service` - Systemd service for autostart
- `build-with-pigen.sh` - Wrapper for pi-gen method
- `build-manual.sh` - Manual build script

## Using the Prebuilt Image

1. Download the `.img.zip` file
2. Extract the `.img` file
3. Flash to SD card using:
   - **Raspberry Pi Imager** (recommended)
   - **balenaEtcher**
   - `dd` command: `sudo dd if=ofxpimapper.img of=/dev/sdX bs=4M status=progress`

4. Insert SD card into Raspberry Pi 4/5 and power on
5. ofxPiMapper will start automatically on boot

## USB Media Support

Place media files on a FAT32/exFAT formatted USB drive:

```
/videos/
  ├── video1.mp4
  ├── video2.mov
  └── video3.mkv
/images/
  ├── image1.jpg
  ├── image2.png
  └── image3.jpg
```

Insert the USB drive before boot, and media will be automatically loaded.

## Customization

### Change Default Project

Edit `configure-system.sh` and modify the `OFXPIMAPPER_PROJECT` variable:

```bash
OFXPIMAPPER_PROJECT="/home/pi/openFrameworks/addons/ofxPiMapper/example_basic"
```

### Adjust GPU Memory

Edit `configure-system.sh` and modify:

```bash
GPU_MEM=256  # Increase for larger projections
```

### Add Custom Scripts

Place scripts in `custom-scripts/` directory - they will be copied to `/home/pi/scripts/`

## GitHub Actions Integration

Automated builds can be triggered via GitHub Actions. See `.github/workflows/build-rpi-image.yml`

```bash
# Trigger manual build
gh workflow run build-rpi-image.yml
```

## Troubleshooting

### Build Fails with "Cannot execute binary"
- Ensure `qemu-user-static` is installed and binfmt is configured
- Run: `sudo systemctl restart systemd-binfmt.service`

### Not Enough Space During Build
- Increase `IMAGE_SIZE` in the build script (default: 8G)
- Ensure host system has at least 10GB free space

### Image Won't Boot on Pi 4
- Verify you're using 64-bit Raspberry Pi OS
- Check that bootloader is up to date on the Pi
- Update config.txt settings for Pi 4 compatibility

### ofxPiMapper Doesn't Start on Boot
- Check logs: `journalctl -u ofxpimapper.service`
- Verify the service is enabled: `systemctl status ofxpimapper.service`

## Performance Optimizations

The image includes several optimizations for projection mapping:

1. **GPU Memory**: 256MB allocated for graphics
2. **CPU Governor**: Performance mode enabled
3. **Boot Optimization**: Disabled unnecessary services
4. **Video Codec**: Hardware-accelerated H.264 decoding
5. **Display**: Force 1080p HDMI output by default

## Security Notes

**Default Credentials:**
- Username: `pi`
- Password: `raspberry`

**⚠️ Change the default password after first boot!**

```bash
passwd
```

## Support

For issues with the image builder:
- Open an issue at: https://github.com/kr15h/ofxPiMapper/issues
- Tag with `disk-image` label

## License

Same as ofxPiMapper - MIT License
