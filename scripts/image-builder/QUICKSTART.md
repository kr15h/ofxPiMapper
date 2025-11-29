# Quick Start: Building ofxPiMapper Raspberry Pi Images

This guide will help you build a ready-to-use Raspberry Pi disk image for ofxPiMapper in just a few commands.

## TL;DR - Fastest Method

### Using Docker (Recommended - Works on Linux, macOS, Windows)

```bash
cd scripts/image-builder
./build-with-docker.sh
```

**That's it!** The image will be in `scripts/image-builder/output/`

---

## Methods Comparison

| Method | Best For | Time | Difficulty |
|--------|----------|------|-----------|
| **Docker** | Everyone, cross-platform | ~2 hours | ⭐ Easy |
| **Native Linux** | Linux users, customization | ~2 hours | ⭐⭐ Medium |
| **GitHub Actions** | Automated builds, releases | ~2-3 hours | ⭐ Easy |

---

## Method 1: Docker Build (Recommended)

**Advantages:**
- Works on Linux, macOS, and Windows
- No need to install dependencies manually
- Consistent build environment

**Requirements:**
- Docker Desktop installed
- 10GB+ free disk space
- Stable internet connection

**Steps:**

```bash
# 1. Navigate to the image builder directory
cd scripts/image-builder

# 2. Run the Docker build script
./build-with-docker.sh

# 3. Wait for completion (1-3 hours)
# The script will:
#   - Download Raspberry Pi OS
#   - Install and compile openFrameworks
#   - Compile ofxPiMapper
#   - Configure system for autostart
#   - Create compressed image

# 4. Find your image
ls -lh output/
# You should see: ofxpimapper-rpi4-YYYYMMDD.img.zip
```

---

## Method 2: Native Linux Build

**Requirements:**
- Ubuntu 20.04+ or Debian 11+ (x86_64)
- sudo access
- 10GB+ free disk space

**Steps:**

```bash
# 1. Install dependencies
sudo apt-get update
sudo apt-get install -y \
  qemu-user-static \
  binfmt-support \
  kpartx \
  parted \
  wget \
  xz-utils \
  zip

# 2. Navigate to image builder
cd scripts/image-builder

# 3. Run build script as root
sudo ./build-image.sh

# 4. Wait for completion
# Output will be in: output/ofxpimapper-rpi4-YYYYMMDD.img.zip
```

---

## Method 3: GitHub Actions (Automated)

**Best for:** Creating official releases, automated builds

**Steps:**

1. Fork or have write access to the repository
2. Go to GitHub Actions tab
3. Select "Build Raspberry Pi Image" workflow
4. Click "Run workflow"
5. Enter version (e.g., `v1.0.0`)
6. Check "Create GitHub release" if desired
7. Wait for completion
8. Download from Artifacts or Releases page

---

## After Building: Using Your Image

### 1. Extract the Image

```bash
cd scripts/image-builder/output
unzip ofxpimapper-rpi4-*.img.zip
```

### 2. Flash to SD Card

**Option A: Using Raspberry Pi Imager (Easiest)**

1. Download [Raspberry Pi Imager](https://www.raspberrypi.com/software/)
2. Open Raspberry Pi Imager
3. Click "Choose OS" → "Use custom"
4. Select your `.img` file
5. Choose your SD card
6. Click "Write"

**Option B: Using balenaEtcher**

1. Download [balenaEtcher](https://www.balena.io/etcher/)
2. Select your `.img` file
3. Select your SD card
4. Click "Flash!"

**Option C: Using `dd` (Linux/macOS)**

```bash
# Find your SD card device
lsblk  # or diskutil list on macOS

# Flash the image (replace /dev/sdX with your SD card)
sudo dd if=ofxpimapper-rpi4-*.img of=/dev/sdX bs=4M status=progress conv=fsync

# Eject safely
sudo eject /dev/sdX
```

### 3. First Boot

1. Insert SD card into Raspberry Pi 4 or 5
2. Connect HDMI display
3. Connect keyboard (optional, for configuration)
4. Power on
5. **ofxPiMapper starts automatically!**

### 4. Default Login

- **Username:** `pi`
- **Password:** `raspberry`

**⚠️ IMPORTANT:** Change password on first login:
```bash
passwd
```

---

## Customization Before Building

### Change Default Project

Edit `configure-system.sh` around line 11:

```bash
OFXPIMAPPER_PROJECT="/home/pi/openFrameworks/addons/ofxPiMapper/example_basic"
```

Change to your custom project path.

### Adjust GPU Memory

Edit `configure-system.sh` around line 10:

```bash
GPU_MEM=256  # Increase for higher resolution projections
```

### Add Custom Media

Place default media files in:
```bash
scripts/image-builder/custom-media/
├── videos/
│   └── default-video.mp4
└── images/
    └── default-image.jpg
```

Then modify `install-ofxpimapper.sh` to copy these files.

---

## Build Configuration Options

Set environment variables before running build scripts:

```bash
# Custom image size (default: 8G)
export IMAGE_SIZE=12G

# Custom output directory (default: output)
export OUTPUT_DIR=/path/to/output

# Custom image name
export FINAL_IMAGE_NAME=my-custom-image.img

# Then run build
sudo -E ./build-image.sh
```

---

## Troubleshooting

### Build Fails with "Cannot execute binary file"

**Problem:** QEMU ARM emulation not set up correctly

**Solution:**
```bash
sudo systemctl restart systemd-binfmt.service
sudo update-binfmts --enable qemu-arm
```

### "Not enough space" Error

**Problem:** Image or disk too small

**Solution:**
```bash
export IMAGE_SIZE=12G  # Increase from default 8G
sudo -E ./build-image.sh
```

### Docker: Permission Denied

**Problem:** Docker needs privileged mode for mounting

**Solution:** The script already uses `--privileged` flag. Ensure Docker daemon is running:
```bash
sudo systemctl start docker
```

### Image Won't Boot on Pi

**Checklist:**
- ✅ Using Raspberry Pi 4 or 5 (not Pi 3 or older)
- ✅ SD card is 16GB or larger
- ✅ SD card is properly flashed
- ✅ Power supply is 5V 3A+ (official recommended)
- ✅ HDMI cable is connected before power on

### ofxPiMapper Doesn't Start

**Check logs:**
```bash
# SSH into the Pi
ssh pi@ofxpimapper.local

# Check service status
systemctl status ofxpimapper

# View logs
journalctl -u ofxpimapper -f
```

---

## Performance Tips

The image is pre-configured for optimal projection mapping:

- ✅ GPU Memory: 256MB
- ✅ CPU Governor: Performance mode
- ✅ Boot optimization: Disabled unnecessary services
- ✅ HDMI: Forced output, no blanking
- ✅ Hardware video decoding: Enabled

**To tweak performance after deployment:**

```bash
# Increase GPU memory (edit /boot/config.txt)
gpu_mem=512

# Check CPU frequency
vcgencmd measure_clock arm

# Monitor temperature
vcgencmd measure_temp
```

---

## Advanced: Custom Builds

### Building for Different openFrameworks Versions

Edit `install-openframeworks.sh` line 7:

```bash
OF_VERSION="0.12.0"  # Change version
```

### Adding Custom Addons

Edit `install-ofxpimapper.sh` and add:

```bash
# Clone custom addon
cd $ADDONS_DIR
git clone https://github.com/user/ofxCustomAddon.git
```

### Pre-install Custom Software

Create `custom-install.sh` in `scripts/image-builder/`:

```bash
#!/bin/bash
apt-get install -y your-package
```

Then modify `build-image.sh` to run it in chroot.

---

## Next Steps

1. **Test the image** on a Raspberry Pi 4/5
2. **Create projection mappings** using the ofxPiMapper interface
3. **Add your media** via USB drive or network
4. **Share your work** with the community!

## Resources

- [ofxPiMapper GitHub](https://github.com/kr15h/ofxPiMapper)
- [ofxPiMapper Website](https://ofxpimapper.com)
- [openFrameworks](https://openframeworks.cc)
- [Raspberry Pi Documentation](https://www.raspberrypi.com/documentation/)

---

## Getting Help

**Issues with building:**
- Open an issue: https://github.com/kr15h/ofxPiMapper/issues
- Tag with `disk-image` label

**Issues with ofxPiMapper:**
- Check existing issues
- Join the community discussions

---

**Happy Mapping! 🎨**
