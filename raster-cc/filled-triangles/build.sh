#!/bin/sh

set -e
gcc -o gfx -lm main.cc canvas.cc draw.cc
