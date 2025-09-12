#include <stdint.h>
#include <assert.h>

#include "array.h"
#include "canvas.h"

void swap(CanvasPoint *a, CanvasPoint *b) {
	CanvasPoint temp = *a;
	*a = *b;
	*b = temp;
}

Array<int64_t> interpolate(int64_t i0, int64_t d0, int64_t i1, int64_t d1) {
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
