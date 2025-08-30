#pragma once

#include "types.h"

constexpr int64_t SCREEN_WIDTH = 600;
constexpr int64_t SCREEN_HEIGHT = 600;

void put_pixel(int64_t canvas_x, int64_t canvas_y, Color c);
void draw_canvas(const char* path);
