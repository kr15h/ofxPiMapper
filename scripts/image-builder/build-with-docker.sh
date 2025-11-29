#!/bin/bash
set -e

# Build ofxPiMapper Raspberry Pi image using Docker
# This provides a consistent build environment across different host systems

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
OUTPUT_DIR="${OUTPUT_DIR:-output}"

# Colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

log_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

log_warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

# Create output directory
mkdir -p "$OUTPUT_DIR"

log_info "Building ofxPiMapper Raspberry Pi image using Docker..."

# Check if Docker is available
if ! command -v docker &> /dev/null; then
    log_warn "Docker is not installed. Please install Docker first."
    log_info "Visit: https://docs.docker.com/get-docker/"
    exit 1
fi

# Create Dockerfile for build environment
log_info "Creating Docker build environment..."
cat > "$SCRIPT_DIR/Dockerfile.builder" << 'EOF'
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# Install all required build tools
RUN apt-get update && apt-get install -y \
    qemu-user-static \
    binfmt-support \
    kpartx \
    parted \
    wget \
    xz-utils \
    zip \
    dosfstools \
    e2fsprogs \
    mount \
    git \
    sudo \
    && rm -rf /var/lib/apt/lists/*

# Set up working directory
WORKDIR /build

# Copy build scripts
COPY *.sh /build/
COPY *.service /build/ 2>/dev/null || true

# Make scripts executable
RUN chmod +x /build/*.sh

# Entry point
CMD ["/bin/bash"]
EOF

# Build Docker image
log_info "Building Docker image for ofxPiMapper build environment..."
docker build -t ofxpimapper-builder -f "$SCRIPT_DIR/Dockerfile.builder" "$SCRIPT_DIR"

# Run build in Docker container
log_info "Starting build in Docker container..."
log_warn "This may take 1-3 hours depending on your system..."

docker run --rm \
    --privileged \
    -v "$SCRIPT_DIR:/build" \
    -v "$SCRIPT_DIR/$OUTPUT_DIR:/build/output" \
    -e OUTPUT_DIR=/build/output \
    -e BUILD_DIR=/build/build \
    ofxpimapper-builder \
    /bin/bash -c "cd /build && bash build-image.sh"

log_info "Build complete!"
log_info "Output images are in: $OUTPUT_DIR/"

# Clean up
rm -f "$SCRIPT_DIR/Dockerfile.builder"
