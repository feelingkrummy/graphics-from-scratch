#pragma once

#include <stdint.h>

#include "array.h"

void draw_line(CanvasPoint p0, CanvasPoint p1, Color col);
void draw_wireframe_triangle(CanvasPoint p0, CanvasPoint p1, CanvasPoint p2, Color col);
void draw_filled_triangle(CanvasPoint p0, CanvasPoint p1, CanvasPoint p2, Color col);
// void draw_shaded_triangle(CanvasPoint p0, CanvasPoint p1, CanvasPoint p2, Color col);
