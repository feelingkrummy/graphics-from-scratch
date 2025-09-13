#include <stdint.h>
#include <assert.h>

#include "array.h"
#include "canvas.h"

static void swap(CanvasPoint *a, CanvasPoint *b) {
	CanvasPoint temp = *a;
	*a = *b;
	*b = temp;
}

static Array<int64_t> interpolate(int64_t i0, int64_t d0, int64_t i1, int64_t d1) {
	Array<int64_t> result = {0};
	array_create(&result, 32);
	if (i0 == i1) {
		array_append(&result, d0);
		return result;
	}
	double a = (double)(d1-d0)/(double)(i1-i0);
	double d = (double)d0;
	
	for (int64_t i = i0; i <= i1; i++) {
		size_t idx = i - i0;
		array_append(&result, (int64_t)round(d));
		d = d + a;
	}
	return result;
}

void draw_line(CanvasPoint p0, CanvasPoint p1, Color col) {
	if (abs(p1.x-p0.x) > abs(p1.y-p0.y)) {
		if (p0.x > p1.x) {
			swap(&p0, &p1);
		}
		Array<int64_t> ys = interpolate(p0.x, p0.y, p1.x, p1.y);
		for (int64_t x = p0.x; x < p1.x; x++) {
			put_pixel(x, ys[x-p0.x], col);
		}
	} else {
		if (p0.y > p1.y) {
			swap(&p0, &p1);
		}
		Array<int64_t> xs = interpolate(p0.y, p0.x, p1.y, p1.x);
		for (int64_t y = p0.y; y < p1.y; y++) {
			put_pixel(xs[y-p0.y], y, col);
		}
	}
}

void draw_wireframe_triangle(CanvasPoint p0, CanvasPoint p1, CanvasPoint p2, Color col) {
	draw_line(p0, p1, col);
	draw_line(p1, p2, col);
	draw_line(p2, p0, col);
}

void draw_filled_triangle(CanvasPoint p0, CanvasPoint p1, CanvasPoint p2, Color col) {
	if (p1.y < p0.y) swap(&p1, &p0);
	if (p2.y < p0.y) swap(&p2, &p0);
	if (p2.y < p1.y) swap(&p2, &p1);

	Array<int64_t> x01 = interpolate(p0.y, p0.x, p1.y, p1.x);
	Array<int64_t> x12 = interpolate(p1.y, p1.x, p2.y, p2.x);
	Array<int64_t> x02 = interpolate(p0.y, p0.x, p2.y, p2.x);

	x01[--x01.len] = 0;
	Array<int64_t> x012 = array_concatenate(x01, x12);

	int64_t m = floor(x012.len/2);
	Array<int64_t> x_left, x_right = {0};
	if (x02[m] < x012[m]) {
		x_left = x02;
		x_right = x012;
	} else {
		x_left = x012;
		x_right = x02;
	}

	for (int64_t y = p0.y; y <= p2.y; y++) {
		for (int64_t x = x_left[y - p0.y]; x <= x_right[y - p0.y]; x++) {
			put_pixel(x, y, col);
		}
	}
}
