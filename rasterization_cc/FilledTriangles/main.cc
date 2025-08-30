#include <stdio.h>
#include <math.h>
#include <vector>

#include "types.h"
#include "canvas.h"
#include "vec.h"

void swap_points(Point& p1, Point& p2) {
	Point temp = p1;
	p1 = p2;
	p2 = temp;
}

std::vector<double> interpolate(int64_t i0, int64_t d0, int64_t i1, int64_t d1) {
	if (i0 == i1) {
		std::vector<double> values = {static_cast<double>(d0)};
		return values;
	}

	std::vector<double> values;
	values.reserve(32);
	double a = static_cast<double>(d1 - d0) / static_cast<double>(i1 - i0);
	double d = d0;

	for (int64_t i = i0; i <= i1; i += 1) {
		values.push_back(d);
		d += a;
	}
	return values;
}

void draw_line(Point p0, Point p1, Color c) {
	if ( abs(p1.x - p0.x) > abs(p1.y - p0.y) ) {
		if (p0.x > p1.x) {
			swap_points(p0, p1);
		}
		std::vector<double> y_values = interpolate(p0.x, p0.y, p1.x, p1.y);
		for (int64_t x = p0.x; x <= p1.x; x += 1) {
			put_pixel(x, y_values[x-p0.x], c);
		}
	} else {
		if (p0.y > p1.y) {
			swap_points(p0, p1);
		}
		std::vector<double> x_values = interpolate(p0.y, p0.x, p1.y, p1.x);
		for (int64_t y = p0.y; y <= p1.y; y += 1) {
			put_pixel(x_values[y-p0.y], y, c);
		}

	}
}

void draw_filled_triangle(Point p0, Point p1, Point p2, Color col) {
	if (p1.y < p0.y) swap_points(p1, p0);
	if (p2.y < p0.y) swap_points(p2, p0);
	if (p2.y < p1.y) swap_points(p2, p1);

	auto x01 = interpolate(p0.y, p0.x, p1.y, p1.x);
	auto x12 = interpolate(p1.y, p1.x, p2.y, p2.x);
	auto x02 = interpolate(p0.y, p0.x, p2.y, p2.x);

	x01.pop_back();
	std::vector<double> x012;
	x012.reserve(x01.size() + x12.size());
	x012.insert(x012.end(), x01.begin(), x01.end());
	x012.insert(x012.end(), x12.begin(), x12.end());

	double m = floor(x012.size() / 2);
	if (x02[m] < x012[m]) {
		auto x_left = x02;
		auto x_right = x012;
		for (int64_t y = p0.y; y <= p2.y; y += 1) {
			for (int64_t x = x_left[y - p0.y]; x <= x_right[y - p0.y]; x += 1) {
				put_pixel(x, y, col);
			}
		}
	} else {
		auto x_left = x012;
		auto x_right = x02;
		for (int64_t y = p0.y; y <= p2.y; y += 1) {
			for (int64_t x = x_left[y - p0.y]; x <= x_right[y - p0.y]; x += 1) {
				put_pixel(x, y, col);
			}
		}
	}
}

int main(void) {
	printf("Rasterizer\n");

	for (int64_t y = -SCREEN_HEIGHT/2; y < SCREEN_HEIGHT/2; y += 1) {
		for (int64_t x = -SCREEN_WIDTH/2; x < SCREEN_WIDTH/2; x += 1) {
			printf("Processing %6ld X %6ld ... \r", x, y);
			put_pixel(x, y, WHITE);
		}
	}
	printf("\n");

	Point p0 = {-200,-250};
	Point p1 = {200,50};
	Point p2 = {20,250};
	draw_filled_triangle(p0, p1, p2, {0,255,0});

	draw_canvas("canvas.ppm");

	return 0;
}
