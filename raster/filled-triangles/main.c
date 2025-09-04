#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "canvas.h"
#include "vec.h"
#include "draw.h"

int main(void) {
	printf("Rasterizer\n");

	for (int64_t y = -C_H/2; y < C_H/2; y += 1) {
		for (int64_t x = -C_W/2; x < C_W/2; x += 1) {
			put_pixel(x, y, WHITE);
		}
	}

	Point p0 = {-200,-250};
	Point p1 = {200, 50};
	Point p2 = {20, 250};
	draw_filled_triangle(p0, p1, p2, (Color){0,255,0});
	draw_wireframe_triangle(p0, p1, p2, BLACK);

	draw_canvas("canvas.ppm");

	return 0;
}
