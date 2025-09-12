#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "canvas.h"
#include "vec.h"

typedef struct Int64Array {
	int64_t len, cap;
	int64_t* ptr;
} Int64Array;

Int64Array interpolate(int64_t i0, int64_t d0, int64_t i1, int64_t d1) {
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

void swap(Point *a, Point *b) {
	Point t = *a;
	*a = *b;
	*b = t;
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

int main(void) {
	printf("Rasterizer\n");

	for (int64_t y = -C_H/2; y < C_H/2; y += 1) {
		for (int64_t x = -C_W/2; x < C_W/2; x += 1) {
			put_pixel(x, y, WHITE);
		}
	}

	Point p0 = {-200,-100};
	Point p1 = {240, 120};
	draw_line(p0, p1, BLACK);

	p0 = (Point){-50,-200};
	p1 = (Point){60, 240};
	draw_line(p0, p1, BLACK);

	draw_canvas("canvas.ppm");

	return 0;
}
