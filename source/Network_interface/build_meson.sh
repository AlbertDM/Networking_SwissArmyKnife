#!/bin/bash

# meson compile
# meson setup --wipe
meson setup --reconfigure build
meson setup build
cd build
ninja
