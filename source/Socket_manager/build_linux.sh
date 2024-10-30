#!/bin/bash

# Ensure script exits on any command failure
set -e

# Create build directory if not exists
mkdir -p build

# Configure and compile
meson setup --buildtype=release build
meson compile -C build

# Run the compiled executable
./build/socket_manager

