#ifndef _CANVAS_H_
#define _CANVAS_H_
#include <stdint.h>

#include "color.h"

#define C_W 600
#define C_H 600

void put_pixel(int64_t canvas_x, int64_t canvas_y, Color col);
void draw_canvas(const char *path);

#endif
