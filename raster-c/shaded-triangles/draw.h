#ifndef _DRAW_H_
#define _DRAW_H_

#include <stdint.h>

#include "vec.h"
#include "color.h"

typedef struct DoubleArray {
	int64_t len, cap;
	double* ptr;
} DoubleArray;

typedef struct Triangle {
	Point p[3];
	double hue[3];
} Triangle;

// void draw_line(Point p0, Point p1, Color col);
// void draw_wireframe_triangle(Point p0, Point p1, Point p2, Color col);
// void draw_filled_triangle(Point p0, Point p1, Point p2, Color col);

void draw_line(Point p0, Point p1, Color col);
void draw_wireframe_triangle(Triangle t, Color col);
void draw_filled_triangle(Triangle t, Color col);
void draw_shaded_triangle(Triangle t, Color col);

#endif
