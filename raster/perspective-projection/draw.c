#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "vec.h"
#include "color.h"
#include "draw.h"
#include "canvas.h"

static void swap(Point *a, Point *b) {
	Point t = *a;
	*a = *b;
	*b = t;
}

static Int64Array interpolate(int64_t i0, int64_t d0, int64_t i1, int64_t d1) {
	Int64Array values = {0};
	if (i0 == i1) {
		values.ptr = calloc(1, sizeof *(values.ptr));
		values.cap = 1;
		values.len = 1;
		values.ptr[0] = d0;
		return values;
	}

	int64_t n = i1-i0+1;
	values.ptr = calloc(n, sizeof *(values.ptr));
	values.cap = n;
	values.len = 0;

	double a = (double)(d1 - d0) / (double)(i1 - i0);
	double d = (double)d0;

	for (int64_t i = i0; i <= i1; i++) {
		values.ptr[i - i0] = round(d);
		values.len += 1;
		d = d + a;
	}
	
	return values;
}

static Int64Array concatenate_arrays(Int64Array first, Int64Array second) {
	Int64Array new = {0};
	size_t elem_size = sizeof *(new.ptr);
	new.cap = first.len + second.len;
	new.len = new.cap;
	new.ptr = calloc(new.cap, elem_size);
	memcpy(new.ptr, first.ptr, first.len*elem_size);
	memcpy(new.ptr + first.len, second.ptr, second.len*elem_size);
	return new;
}

void draw_line(Point p0, Point p1, Color col) {
	if (abs(p1.x - p0.x) > abs(p1.y - p0.y)) {
		if (p0.x > p1.x) {
			swap(&p0, &p1);
		}
		Int64Array ys = interpolate(p0.x, p0.y, p1.x, p1.y);
		for (int64_t x = p0.x; x <= p1.x; x++) {
			put_pixel(x, ys.ptr[x-(int64_t)p0.x], col);
		}
	} else {
		if (p0.y > p1.y) {
			swap(&p0, &p1);
		}
		Int64Array xs = interpolate(p0.y, p0.x, p1.y, p1.x);
		for (int64_t y = p0.y; y <= p1.y; y++) {
			put_pixel(xs.ptr[y-(int64_t)p0.y], y, col);
		}

	}
}

void draw_wireframe_triangle(Point p0, Point p1, Point p2, Color col) {
	draw_line(p0, p1, col);
	draw_line(p1, p2, col);
	draw_line(p2, p0, col);
}

void draw_filled_triangle(Point p0, Point p1, Point p2, Color col) {
	if (p1.y < p0.y) swap(&p0, &p1);
	if (p2.y < p0.y) swap(&p2, &p0);
	if (p2.y < p1.y) swap(&p2, &p1);

	Int64Array x01 = interpolate(p0.y, p0.x, p1.y, p1.x);
	Int64Array x12 = interpolate(p1.y, p1.x, p2.y, p2.x);
	Int64Array x02 = interpolate(p0.y, p0.x, p2.y, p2.x);

	x01.len -= 1;
	x01.ptr[x01.len] = 0;

	// concatenate arrays
	Int64Array x012 = concatenate_arrays(x01, x12);

	int64_t m = x012.len/2;
	Int64Array x_left, x_right;
	if (x02.ptr[m] < x012.ptr[m]) {
		x_left = x02;
		x_right = x012;
	} else {
		x_left = x012;
		x_right = x02;
	}

	for (int64_t y = p0.y; y <= p2.y; y++) {
		for (int64_t x = x_left.ptr[y-(int64_t)p0.y]; x <= x_right.ptr[y-(int64_t)p0.y]; x++) {
			printf("Drawing %5ld X %5ld ... \r", x, y);
			put_pixel(x, y, col);
		}
	}
	printf("\n");
}
