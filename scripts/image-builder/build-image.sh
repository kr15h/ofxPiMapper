#!/bin/bash
set -e

# Build ofxPiMapper Raspberry Pi Disk Image
# This script creates a complete ready-to-use Raspberry Pi image with ofxPiMapper

# Configuration
RPI_OS_VERSION="${RPI_OS_VERSION:-2024-11-19}"
RPI_OS_URL="${RPI_OS_URL:-https://downloads.raspberrypi.org/raspios_lite_arm64/images/raspios_lite_arm64-${RPI_OS_VERSION}/}"
RPI_OS_IMAGE="${RPI_OS_IMAGE:-2024-11-19-raspios-bookworm-arm64-lite.img}"
RPI_OS_ZIP="${RPI_OS_ZIP:-${RPI_OS_IMAGE}.xz}"

OUTPUT_DIR="${OUTPUT_DIR:-output}"
BUILD_DIR="${BUILD_DIR:-build}"
IMAGE_SIZE="${IMAGE_SIZE:-8G}"
FINAL_IMAGE_NAME="${FINAL_IMAGE_NAME:-ofxpimapper-rpi4-$(date +%Y%m%d).img}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

log_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

log_warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check if running as root
if [ "$EUID" -ne 0 ]; then
    log_error "This script must be run as root or with sudo"
    exit 1
fi

# Check dependencies
log_info "Checking dependencies..."
REQUIRED_TOOLS="qemu-arm-static kpartx wget xz parted"
MISSING_TOOLS=""

for tool in $REQUIRED_TOOLS; do
    if ! command -v $tool &> /dev/null; then
        MISSING_TOOLS="$MISSING_TOOLS $tool"
    fi
done

if [ -n "$MISSING_TOOLS" ]; then
    log_error "Missing required tools:$MISSING_TOOLS"
    log_info "Install with: apt-get install qemu-user-static kpartx wget xz-utils parted"
    exit 1
fi

# Create directories
log_info "Creating build directories..."
mkdir -p "$BUILD_DIR"
mkdir -p "$OUTPUT_DIR"

# Download Raspberry Pi OS image
log_info "Downloading Raspberry Pi OS image..."
cd "$BUILD_DIR"

if [ ! -f "$RPI_OS_ZIP" ]; then
    log_info "Downloading from ${RPI_OS_URL}${RPI_OS_ZIP}..."
    wget "${RPI_OS_URL}${RPI_OS_ZIP}" -O "$RPI_OS_ZIP"
else
    log_info "Image already downloaded, skipping..."
fi

# Extract image
if [ ! -f "$RPI_OS_IMAGE" ]; then
    log_info "Extracting image..."
    xz -d -k "$RPI_OS_ZIP"
    # Rename to expected name if different
    EXTRACTED_IMAGE=$(ls *.img | head -n 1)
    if [ "$EXTRACTED_IMAGE" != "$RPI_OS_IMAGE" ]; then
        mv "$EXTRACTED_IMAGE" "$RPI_OS_IMAGE"
    fi
else
    log_info "Image already extracted, skipping..."
fi

# Expand image to have space for compilation
log_info "Expanding image to ${IMAGE_SIZE}..."
dd if=/dev/zero bs=1M count=4096 >> "$RPI_OS_IMAGE"

# Resize partition
log_info "Resizing root partition..."
parted "$RPI_OS_IMAGE" resizepart 2 100% --script || true

# Set up loop device
log_info "Setting up loop device..."
LOOP_DEVICE=$(losetup -f --show "$RPI_OS_IMAGE")
log_info "Loop device: $LOOP_DEVICE"

# Map partitions
log_info "Mapping partitions..."
kpartx -av "$LOOP_DEVICE"

# Get partition device names
BOOT_PART="/dev/mapper/$(basename ${LOOP_DEVICE})p1"
ROOT_PART="/dev/mapper/$(basename ${LOOP_DEVICE})p2"

# Wait for devices to be ready
sleep 2

# Resize filesystem
log_info "Resizing root filesystem..."
e2fsck -f -y "$ROOT_PART" || true
resize2fs "$ROOT_PART"

# Mount partitions
MOUNT_DIR="$BUILD_DIR/mnt"
mkdir -p "$MOUNT_DIR"

log_info "Mounting root partition..."
mount "$ROOT_PART" "$MOUNT_DIR"

log_info "Mounting boot partition..."
mkdir -p "$MOUNT_DIR/boot"
mount "$BOOT_PART" "$MOUNT_DIR/boot"

# Set up chroot environment
log_info "Setting up chroot environment..."
cp /usr/bin/qemu-arm-static "$MOUNT_DIR/usr/bin/"
mount --bind /dev "$MOUNT_DIR/dev"
mount --bind /proc "$MOUNT_DIR/proc"
mount --bind /sys "$MOUNT_DIR/sys"
mount --bind /dev/pts "$MOUNT_DIR/dev/pts"

# Copy installation scripts into image
log_info "Copying installation scripts..."
mkdir -p "$MOUNT_DIR/tmp/ofxpimapper-setup"
cp "$SCRIPT_DIR"/*.sh "$MOUNT_DIR/tmp/ofxpimapper-setup/"
cp "$SCRIPT_DIR"/*.service "$MOUNT_DIR/tmp/ofxpimapper-setup/" 2>/dev/null || true

# Enable networking in chroot
echo "nameserver 8.8.8.8" > "$MOUNT_DIR/etc/resolv.conf"

# Run installation scripts in chroot
log_info "Installing openFrameworks in chroot..."
chroot "$MOUNT_DIR" /bin/bash -c "cd /tmp/ofxpimapper-setup && bash install-openframeworks.sh"

log_info "Installing ofxPiMapper in chroot..."
chroot "$MOUNT_DIR" /bin/bash -c "cd /tmp/ofxpimapper-setup && bash install-ofxpimapper.sh"

log_info "Configuring system in chroot..."
chroot "$MOUNT_DIR" /bin/bash -c "cd /tmp/ofxpimapper-setup && bash configure-system.sh"

log_info "Installing systemd service in chroot..."
chroot "$MOUNT_DIR" /bin/bash -c "cd /tmp/ofxpimapper-setup && bash install-service.sh"

# Clean up
log_info "Cleaning up build artifacts..."
chroot "$MOUNT_DIR" /bin/bash -c "apt-get clean"
chroot "$MOUNT_DIR" /bin/bash -c "rm -rf /tmp/ofxpimapper-setup"
chroot "$MOUNT_DIR" /bin/bash -c "rm -rf /var/cache/apt/archives/*.deb"
chroot "$MOUNT_DIR" /bin/bash -c "rm -rf /home/pi/.cache"

# Unmount everything
log_info "Unmounting filesystems..."
sync
umount "$MOUNT_DIR/dev/pts" || true
umount "$MOUNT_DIR/dev" || true
umount "$MOUNT_DIR/proc" || true
umount "$MOUNT_DIR/sys" || true
umount "$MOUNT_DIR/boot" || true
umount "$MOUNT_DIR" || true

# Remove loop device mappings
log_info "Removing loop device mappings..."
kpartx -d "$LOOP_DEVICE"
losetup -d "$LOOP_DEVICE"

# Shrink image (optional - removes unused space)
log_info "Shrinking image..."
# This step can be skipped if you want to keep the extra space
# truncate -s $(parted -s "$RPI_OS_IMAGE" unit B print | grep "Disk /" | awk '{print $3}' | sed 's/B//') "$RPI_OS_IMAGE"

# Copy to output directory
log_info "Copying image to output directory..."
cp "$RPI_OS_IMAGE" "../$OUTPUT_DIR/$FINAL_IMAGE_NAME"

# Compress image
log_info "Compressing image..."
cd "../$OUTPUT_DIR"
zip "${FINAL_IMAGE_NAME}.zip" "$FINAL_IMAGE_NAME"

# Generate checksums
log_info "Generating checksums..."
sha256sum "$FINAL_IMAGE_NAME" > "${FINAL_IMAGE_NAME}.sha256"
sha256sum "${FINAL_IMAGE_NAME}.zip" > "${FINAL_IMAGE_NAME}.zip.sha256"

log_info "================================"
log_info "Build complete!"
log_info "================================"
log_info "Output image: $OUTPUT_DIR/$FINAL_IMAGE_NAME"
log_info "Compressed: $OUTPUT_DIR/${FINAL_IMAGE_NAME}.zip"
log_info "Size: $(du -h $OUTPUT_DIR/$FINAL_IMAGE_NAME | cut -f1)"
log_info "Compressed size: $(du -h $OUTPUT_DIR/${FINAL_IMAGE_NAME}.zip | cut -f1)"
log_info ""
log_info "To flash to SD card:"
log_info "  unzip ${FINAL_IMAGE_NAME}.zip"
log_info "  sudo dd if=$FINAL_IMAGE_NAME of=/dev/sdX bs=4M status=progress"
log_info "  (replace /dev/sdX with your SD card device)"
