#!/bin/bash

# Ensure script exits on any command failure
set -e

# Create build directory if not exists
mkdir -p build

# Configure and compile with MinGW
meson setup --cross-file cross_file.txt build
meson compile -C build

# Run the compiled executable
./build/socket_manager.exe

