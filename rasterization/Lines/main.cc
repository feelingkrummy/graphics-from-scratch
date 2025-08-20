#include <stdio.h>
#include <math.h>
#include <vector>

#include "types.h"
#include "canvas.h"
#include "vec.h"


std::vector<double> interpolate(int64_t i0, int64_t d0, int64_t i1, int64_t d1) {
	if (i0 == i1) {
		std::vector<double> values = {static_cast<double>(d0)};
		return values;
	}

	std::vector<double> values(32);
	printf("(%ld, %ld), (%ld, %ld)\n", i0, d0, i1, d1);
	double a = static_cast<double>(d1 - d0) / static_cast<double>(i1 - i0);
	double d = d0;
	printf("a = %lf, d0 = %lf\n", a, d);

	for (int64_t i = i0; i <= i1; i += 1) {
		values.push_back(d);
		d += a;
	}
	printf("Len : %ld\n", values.size());
	return values;
}

void draw_line(Point p0, Point p1, Color c) {
	if ( abs(p1.x - p0.x) > abs(p1.y - p0.y) ) {
		if (p0.x > p1.x) {
			Point t = p1;
			p1 = p0;
			p0 = t;
		}
		std::vector<double> y_values = interpolate(p0.x, p0.y, p1.x, p1.y);
		for (int64_t x = p0.x; x <= p1.x; x += 1) {
			printf("%ld, %ld\n", x, static_cast<int64_t>(y_values[x-p0.x]));
			put_pixel(x, y_values[x-p0.x], c);
		}
	} else {
		if (p0.y > p1.y) {
			Point t = p1;
			p1 = p0;
			p0 = t;
		}
		std::vector<double> x_values = interpolate(p0.y, p0.x, p1.y, p1.x);
		for (int64_t y = p0.y; y <= p1.y; y += 1) {
			printf("%ld, %ld\n", static_cast<int64_t>(x_values[y-p0.y]), y);
			put_pixel(x_values[y-p0.y], y, c);
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

	Point p0 = {-200,-100};
	Point p1 = {240, 120};
	draw_line(p0, p1, BLACK);

	p0 = {-50,-200};
	printf("%lf, %lf\n", p0.x, p0.y);
	p1 = {60, 240};
	printf("%lf, %lf\n", p1.x, p1.y);
	draw_line(p0, p1, BLACK);

	draw_canvas("canvas.ppm");

	return 0;
}
