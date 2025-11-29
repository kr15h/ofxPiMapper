#!/bin/bash
set -e

# Install ofxPiMapper systemd service for autostart
# This script should be run as root or with sudo

echo "================================"
echo "Installing ofxPiMapper systemd service"
echo "================================"

# Check if running as root
if [ "$EUID" -ne 0 ]; then
    echo "This script must be run as root or with sudo"
    exit 1
fi

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Copy systemd service file
echo "Installing systemd service..."
cp "$SCRIPT_DIR/ofxpimapper.service" /etc/systemd/system/

# Copy media loader script
echo "Installing media loader script..."
cp "$SCRIPT_DIR/load-media.sh" /usr/local/bin/
chmod +x /usr/local/bin/load-media.sh

# Reload systemd
echo "Reloading systemd daemon..."
systemctl daemon-reload

# Enable the service (will start on boot)
echo "Enabling ofxpimapper service..."
systemctl enable ofxpimapper.service

# Check if X server is required
echo "Configuring X server for auto-login..."

# Install minimal X server if not present
apt-get update
apt-get install -y xserver-xorg xinit x11-xserver-utils

# Configure auto-login for pi user
mkdir -p /etc/systemd/system/getty@tty1.service.d
cat > /etc/systemd/system/getty@tty1.service.d/autologin.conf << EOF
[Service]
ExecStart=
ExecStart=-/sbin/agetty --autologin pi --noclear %I \$TERM
EOF

# Create .xinitrc for pi user to start X without window manager
cat > /home/pi/.xinitrc << 'EOF'
#!/bin/sh
# Disable screen saver and power management
xset s off
xset -dpms
xset s noblank

# Set black background
xsetroot -solid black

# Keep X server running
while true; do
    sleep 3600
done
EOF

chown pi:pi /home/pi/.xinitrc
chmod +x /home/pi/.xinitrc

# Configure pi user's bash profile to start X on login to tty1
if ! grep -q "startx" /home/pi/.bash_profile 2>/dev/null; then
    cat >> /home/pi/.bash_profile << 'EOF'

# Start X server on tty1
if [ -z "$DISPLAY" ] && [ "$(tty)" = "/dev/tty1" ]; then
    startx
fi
EOF
    chown pi:pi /home/pi/.bash_profile
fi

echo "================================"
echo "ofxPiMapper service installed successfully!"
echo "================================"
echo ""
echo "Service status:"
systemctl status ofxpimapper.service --no-pager || true
echo ""
echo "Useful commands:"
echo "  systemctl start ofxpimapper   - Start the service now"
echo "  systemctl stop ofxpimapper    - Stop the service"
echo "  systemctl restart ofxpimapper - Restart the service"
echo "  systemctl status ofxpimapper  - Check service status"
echo "  journalctl -u ofxpimapper -f  - View live logs"
echo ""
echo "The service is enabled and will start automatically on boot."
echo "Reboot to test autostart functionality."
