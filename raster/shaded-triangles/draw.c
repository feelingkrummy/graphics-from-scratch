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

static void swap_double(double *a, double *b) {
	double t = *a;
	*a = *b;
	*b = t;
}

static DoubleArray interpolate(double i0, double d0, double i1, double d1) {
	DoubleArray values = {0};
	if (i0 == i1) {
		values.ptr = calloc(1, sizeof *(values.ptr));
		values.cap = 1;
		values.len = 1;
		values.ptr[0] = d0;
		return values;
	}

	int64_t n = (int64_t)(i1-i0+1);
	values.ptr = calloc(n, sizeof *(values.ptr));
	values.cap = n;
	values.len = 0;

	double a = (double)(d1 - d0) / (double)(i1 - i0);
	double d = (double)d0;

	for (int64_t i = i0; i <= i1; i++) {
		values.ptr[i - (int64_t)round(i0)] = d;
		values.len += 1;
		d = d + a;
	}
	
	return values;
}

static DoubleArray concatenate_arrays(DoubleArray first, DoubleArray second) {
	DoubleArray new = {0};
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
		DoubleArray ys = interpolate(p0.x, p0.y, p1.x, p1.y);
		for (int64_t x = p0.x; x <= p1.x; x++) {
			put_pixel(x, round(ys.ptr[x-(int64_t)p0.x]), col);
		}
	} else {
		if (p0.y > p1.y) {
			swap(&p0, &p1);
		}
		DoubleArray xs = interpolate(p0.y, p0.x, p1.y, p1.x);
		for (int64_t y = p0.y; y <= p1.y; y++) {
			put_pixel(round(xs.ptr[y-(int64_t)p0.y]), y, col);
		}

	}
}

void draw_wireframe_triangle(Triangle t, Color col) {
	draw_line(t.p[0], t.p[1], col);
	draw_line(t.p[1], t.p[2], col);
	draw_line(t.p[2], t.p[0], col);
}

void draw_filled_triangle(Triangle t, Color col) {
	if (t.p[1].y < t.p[0].y) swap(&t.p[0], &t.p[1]);
	if (t.p[2].y < t.p[0].y) swap(&t.p[2], &t.p[0]);
	if (t.p[2].y < t.p[1].y) swap(&t.p[2], &t.p[1]);

	DoubleArray x01 = interpolate(t.p[0].y, t.p[0].x, t.p[1].y, t.p[1].x);
	DoubleArray x12 = interpolate(t.p[1].y, t.p[1].x, t.p[2].y, t.p[2].x);
	DoubleArray x02 = interpolate(t.p[0].y, t.p[0].x, t.p[2].y, t.p[2].x);

	// Remove Last Item
	x01.len -= 1;
	x01.ptr[x01.len] = 0;

	// concatenate arrays
	DoubleArray x012 = concatenate_arrays(x01, x12);

	int64_t m = x012.len/2;
	DoubleArray x_left, x_right;
	if (x02.ptr[m] < x012.ptr[m]) {
		x_left = x02;
		x_right = x012;
	} else {
		x_left = x012;
		x_right = x02;
	}

	for (int64_t y = t.p[0].y; y <= t.p[2].y; y++) {
		for (int64_t x = round(x_left.ptr[y-(int64_t)t.p[0].y]); x <= round(x_right.ptr[y-(int64_t)t.p[0].y]); x++) {
			printf("Drawing %5ld X %5ld ... \r", x, y);
			put_pixel(round(x), round(y), col);
		}
	}
	printf("\n");
}

void draw_shaded_triangle(Triangle t, Color col) {
	if (t.p[1].y < t.p[0].y) {
		swap(&t.p[0], &t.p[1]);
		swap_double(&t.hue[0], &t.hue[1]);
	}
	if (t.p[2].y < t.p[0].y) {
		swap(&t.p[2], &t.p[0]);
		swap_double(&t.hue[2], &t.hue[0]);
	}
	if (t.p[2].y < t.p[1].y) {
		swap(&t.p[2], &t.p[1]);
		swap_double(&t.hue[2], &t.hue[1]);
	}

	DoubleArray x01 = interpolate(t.p[0].y, t.p[0].x, t.p[1].y, t.p[1].x);
	DoubleArray h01 = interpolate(t.p[0].y, t.hue[0], t.p[1].y, t.hue[1]);

	DoubleArray x12 = interpolate(t.p[1].y, t.p[1].x, t.p[2].y, t.p[2].x);
	DoubleArray h12 = interpolate(t.p[1].y, t.hue[1], t.p[2].y, t.hue[2]);

	DoubleArray x02 = interpolate(t.p[0].y, t.p[0].x, t.p[2].y, t.p[2].x);
	DoubleArray h02 = interpolate(t.p[0].y, t.hue[0], t.p[2].y, t.hue[2]);

	// Remove Last Item
	x01.len -= 1;
	x01.ptr[x01.len] = 0;

	h01.len -= 1;
	h01.ptr[h01.len] = 0;

	// concatenate arrays
	DoubleArray x012 = concatenate_arrays(x01, x12);
	DoubleArray h012 = concatenate_arrays(h01, h12);

	int64_t m = x012.len/2;
	DoubleArray x_left, x_right, h_left, h_right;
	if (x02.ptr[m] < x012.ptr[m]) {
		x_left = x02;
		x_right = x012;

		h_left = h02;
		h_right = h012;
	} else {
		x_left = x012;
		x_right = x02;

		h_left = h012;
		h_right = h02;
	}

	for (int64_t y = t.p[0].y; y <= t.p[2].y; y++) {
		double x_l = round(x_left.ptr[y-(int64_t)t.p[0].y]);
		double x_r = round(x_right.ptr[y-(int64_t)t.p[0].y]);

		DoubleArray h_segment = interpolate(x_l, h_left.ptr[y - (int64_t)t.p[0].y], x_r, h_right.ptr[y-(int64_t)t.p[0].y]);

		for (int64_t x = x_l; x <= x_r; x++) {
			printf("Drawing %5ld X %5ld ... \r", x, y);
			Color shaded = {
				.r = round(col.r*h_segment.ptr[x-(int64_t)x_l]),
				.g = round(col.g*h_segment.ptr[x-(int64_t)x_l]),
				.b = round(col.b*h_segment.ptr[x-(int64_t)x_l])
			};
			put_pixel(round(x), round(y), shaded);
		}
	}
	printf("\n");
}
