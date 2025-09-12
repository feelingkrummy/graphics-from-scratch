#!/bin/sh
set -e
gcc -g -o gfx --std=c23 -lm main.c canvas.c vec.c draw.c
