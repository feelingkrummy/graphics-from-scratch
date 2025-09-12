#ifndef _DRAW_H_
#define _DRAW_H_

#include <stdint.h>

#include "vec.h"
#include "color.h"

typedef struct Int64Array {
	int64_t len, cap;
	int64_t* ptr;
} Int64Array;

void draw_line(Point p0, Point p1, Color col);
void draw_wireframe_triangle(Point p0, Point p1, Point p2, Color col);
void draw_filled_triangle(Point p0, Point p1, Point p2, Color col);

#endif
