#pragma once

#include "color.h"

#define C_H 600
#define C_W 600

struct CanvasPoint {
	int64_t x, y;
};

void clear_canvas(Color c);
void put_pixel(int64_t canvas_x, int64_t canvas_y, Color col);
void draw_canvas(const char *path);
