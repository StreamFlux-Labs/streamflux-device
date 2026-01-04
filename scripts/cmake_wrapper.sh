#!/bin/bash
# scripts/cmake_wrapper.sh

IMAGE_NAME="luckfox-compiler:1.0"
BUILD_DIR="build_arm"

if [ -f /.dockerenv ]; then
    exec "$@"
else
    echo "[Wrapper] Detected Host environment. Running inside Docker..."
    
    docker run --rm -it \
        -u $(id -u):$(id -g) \
        -v "$(pwd):/workspace" \
        -w /workspace/$BUILD_DIR \
        $IMAGE_NAME \
        /bin/bash -c "$*"
fi