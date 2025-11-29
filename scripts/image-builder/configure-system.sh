#!/bin/bash
set -e

# Configure Raspberry Pi system for ofxPiMapper
# Optimizes settings for projection mapping performance

echo "================================"
echo "Configuring system for ofxPiMapper"
echo "================================"

# Configuration variables
HOSTNAME="ofxpimapper"
GPU_MEM=256
OFXPIMAPPER_PROJECT="/home/pi/openFrameworks/addons/ofxPiMapper/example_basic"
USB_MOUNT_BASE="/media/usb"

# Set hostname
echo "Setting hostname to ${HOSTNAME}..."
echo "$HOSTNAME" > /etc/hostname
sed -i "s/127.0.1.1.*/127.0.1.1\t${HOSTNAME}/g" /etc/hosts

# Configure GPU memory
echo "Configuring GPU memory (${GPU_MEM}MB)..."
if ! grep -q "gpu_mem=" /boot/config.txt; then
    echo "gpu_mem=${GPU_MEM}" >> /boot/config.txt
else
    sed -i "s/gpu_mem=.*/gpu_mem=${GPU_MEM}/g" /boot/config.txt
fi

# Disable overscan for exact pixel mapping
if ! grep -q "disable_overscan=1" /boot/config.txt; then
    echo "disable_overscan=1" >> /boot/config.txt
fi

# Force HDMI output (even if no display detected at boot)
if ! grep -q "hdmi_force_hotplug=1" /boot/config.txt; then
    echo "hdmi_force_hotplug=1" >> /boot/config.txt
fi

# Set HDMI mode to 1080p 60Hz by default
if ! grep -q "hdmi_group=2" /boot/config.txt; then
    echo "hdmi_group=2" >> /boot/config.txt
fi
if ! grep -q "hdmi_mode=82" /boot/config.txt; then
    echo "hdmi_mode=82" >> /boot/config.txt
fi

# Enable hardware video decoding
if ! grep -q "dtoverlay=vc4-kms-v3d" /boot/config.txt; then
    echo "dtoverlay=vc4-kms-v3d" >> /boot/config.txt
fi

# Reduce boot time by disabling unnecessary services
echo "Optimizing boot time..."
systemctl disable bluetooth.service || true
systemctl disable hciuart.service || true
systemctl disable avahi-daemon.service || true
systemctl disable triggerhappy.service || true

# Configure CPU governor for performance
echo "Setting CPU governor to performance..."
if ! grep -q "cpufrequtils" /etc/modules; then
    echo "cpufrequtils" >> /etc/modules
fi
apt-get install -y cpufrequtils
echo 'GOVERNOR="performance"' > /etc/default/cpufrequtils

# Configure USB automount
echo "Configuring USB automount..."
mkdir -p /media/usb0
mkdir -p /media/usb1

# Create udev rules for USB automount
cat > /etc/udev/rules.d/99-usb-automount.rules << 'EOF'
# Automatically mount USB drives
ACTION=="add", KERNEL=="sd[a-z][0-9]", SUBSYSTEMS=="usb", RUN+="/usr/local/bin/usb-mount.sh add %k"
ACTION=="remove", KERNEL=="sd[a-z][0-9]", SUBSYSTEMS=="usb", RUN+="/usr/local/bin/usb-mount.sh remove %k"
EOF

# Create USB mount helper script
cat > /usr/local/bin/usb-mount.sh << 'EOF'
#!/bin/bash
ACTION=$1
DEVICE=$2

case "$ACTION" in
    add)
        # Find next available mount point
        for i in {0..7}; do
            if [ ! -d "/media/usb${i}" ]; then
                mkdir -p "/media/usb${i}"
            fi
            if ! mountpoint -q "/media/usb${i}"; then
                MOUNT_POINT="/media/usb${i}"
                break
            fi
        done

        # Mount the device
        if [ -n "$MOUNT_POINT" ]; then
            mount -o uid=pi,gid=pi,umask=000 "/dev/${DEVICE}" "$MOUNT_POINT"
            logger "USB device ${DEVICE} mounted at ${MOUNT_POINT}"
        fi
        ;;
    remove)
        # Unmount if mounted
        for i in {0..7}; do
            if mountpoint -q "/media/usb${i}"; then
                if mount | grep "/dev/${DEVICE}" | grep -q "/media/usb${i}"; then
                    umount "/media/usb${i}"
                    logger "USB device ${DEVICE} unmounted from /media/usb${i}"
                fi
            fi
        done
        ;;
esac
EOF

chmod +x /usr/local/bin/usb-mount.sh

# Configure audio output
echo "Configuring audio..."
# Set default audio output to HDMI
amixer cset numid=3 2 || true  # 0=auto, 1=headphones, 2=HDMI

# Create directory for media sources
mkdir -p /home/pi/media/videos
mkdir -p /home/pi/media/images

# Set default ALSA configuration for low latency
cat > /home/pi/.asoundrc << 'EOF'
pcm.!default {
    type hw
    card 0
}

ctl.!default {
    type hw
    card 0
}
EOF

chown pi:pi /home/pi/.asoundrc

# Disable screen blanking
if ! grep -q "consoleblank=0" /boot/cmdline.txt; then
    sed -i 's/$/ consoleblank=0/' /boot/cmdline.txt
fi

# Set locale and timezone (default to UTC)
echo "Configuring locale and timezone..."
locale-gen en_US.UTF-8
update-locale LANG=en_US.UTF-8

# Create welcome message
cat > /etc/motd << 'EOF'
 ___  _____ __  __ _
/ _ \|  ___\ \/ /| |_ __ ___   __ _ _ __
| | | | |_   \  / | | '_ ` _ \ / _` | '_ \
| |_| |  _|  /  \ | | | | | | | (_| | |_) |
\___/|_|   /_/\_\|_|_| |_| |_|\__,_| .__/
                                    |_|

ofxPiMapper Projection Mapping System
=====================================

Default credentials:
  Username: pi
  Password: raspberry

IMPORTANT: Change the default password using 'passwd'

Useful commands:
  - systemctl status ofxpimapper  : Check application status
  - systemctl stop ofxpimapper    : Stop projection mapping
  - systemctl start ofxpimapper   : Start projection mapping
  - journalctl -u ofxpimapper -f  : View live logs

Media directories:
  - /home/pi/media/videos/  : Place video files here
  - /home/pi/media/images/  : Place image files here
  - /media/usb*/            : USB drive mount points

Documentation: https://github.com/kr15h/ofxPiMapper
Support: https://ofxpimapper.com

EOF

# Set proper permissions
chown -R pi:pi /home/pi/media

echo "================================"
echo "System configuration complete!"
echo "================================"
echo "Configured:"
echo "  - Hostname: $HOSTNAME"
echo "  - GPU Memory: ${GPU_MEM}MB"
echo "  - HDMI: 1080p 60Hz forced"
echo "  - CPU Governor: Performance"
echo "  - USB Automount: Enabled"
echo "  - Screen Blanking: Disabled"
echo "================================"
