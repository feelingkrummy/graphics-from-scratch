#!/bin/sh
set -e
gcc -o gfx --std=c23 -lm main.c canvas.c vec3.c
