#include <stdint.h>
#include <assert.h>

#include "array.h"
#include "canvas.h"

static void swap(CanvasPoint *a, CanvasPoint *b) {
	CanvasPoint temp = *a;
	*a = *b;
	*b = temp;
}

static uint8_t clamp_color_value(double a) {
	if ( a > 255 ) {
		return 255;
	}
	if ( a < 0 ) {
		return 0;
	}
	return (uint8_t)round(a);
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

static Array<double> interpolate(double i0, double d0, double i1, double d1) {
	Array<double> result = {0};
	array_create(&result, 32);
	if (i0 == i1) {
		array_append(&result, d0);
		return result;
	}
	double a = (d1-d0)/(i1-i0);
	double d = d0;
	
	int64_t i0_rounded = (int64_t)round(i0);
	for (int64_t i = i0_rounded; i <= i1; i++) {
		size_t idx = i - i0_rounded;
		array_append(&result, d);
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

	array_destroy(&x01);
	array_destroy(&x12);
	array_destroy(&x02);
	array_destroy(&x012);
}

void draw_shaded_triangle(CanvasPoint p0, CanvasPoint p1, CanvasPoint p2, Color col) {
	if (p1.y < p0.y) swap(&p1, &p0);
	if (p2.y < p0.y) swap(&p2, &p0);
	if (p2.y < p1.y) swap(&p2, &p1);

	Array<int64_t> x01 = interpolate(p0.y, p0.x, p1.y, p1.x);
	Array<double> h01 = interpolate((double)p0.y, p0.hue, (double)p1.y, p1.hue);

	Array<int64_t> x12 = interpolate(p1.y, p1.x, p2.y, p2.x);
	Array<double> h12 = interpolate((double)p1.y, p1.hue, (double)p2.y, p2.hue);

	Array<int64_t> x02 = interpolate(p0.y, p0.x, p2.y, p2.x);
	Array<double> h02 = interpolate((double)p0.y, p0.hue, (double)p2.y, p2.hue);

	x01[--x01.len] = 0;
	Array<int64_t> x012 = array_concatenate(x01, x12);

	h01[--h01.len] = 0;
	Array<double> h012 = array_concatenate(h01, h12);

	int64_t m = floor(x012.len/2);
	Array<int64_t> x_left, x_right = {0};
	Array<double> h_left, h_right = {0};
	if (x02[m] < x012[m]) {
		x_left = x02;
		h_left = h02;

		x_right = x012;
		h_right = h012;
	} else {
		x_left = x012;
		h_left = h012;

		x_right = x02;
		h_right = h02;
	}

	for (int64_t y = p0.y; y <= p2.y; y++) {
		double x_l = (double)x_left[y - p0.y];
		double x_r = (double)x_right[y - p0.y];

		Array<double> h_segment = interpolate(x_l, h_left[y-p0.y], x_r, h_right[y-p0.y]);

		for (int64_t x = x_l; x <= x_r; x++) {
			Color shaded = {
				.r = clamp_color_value(col.r*h_segment[x-x_l]),
				.g = clamp_color_value(col.g*h_segment[x-x_l]),
				.b = clamp_color_value(col.b*h_segment[x-x_l]),
			};
			put_pixel(x, y, shaded);
		}
	}

	array_destroy(&x01);
	array_destroy(&h01);

	array_destroy(&x12);
	array_destroy(&h12);

	array_destroy(&x02);
	array_destroy(&h02);

	array_destroy(&x012);
	array_destroy(&h012);
}
