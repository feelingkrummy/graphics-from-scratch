#pragma once

#include <stdint.h>

#include "array.h"

void swap(CanvasPoint *a, CanvasPoint *b);
Array<int64_t> interpolate(int64_t i0, int64_t d0, int64_t i1, int64_t d1);
void draw_line(CanvasPoint p0, CanvasPoint p1, Color col);
