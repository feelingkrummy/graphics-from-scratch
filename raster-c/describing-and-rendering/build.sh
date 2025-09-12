#!/bin/sh
set -e
gcc -fsanitize=address -g -o gfx --std=c23 -lm main.c canvas.c vec.c draw.c
# clang -fsanitize=address -g -fno-omit-frame-pointer -o gfx --std=c23 -lm main.c canvas.c vec.c draw.c
