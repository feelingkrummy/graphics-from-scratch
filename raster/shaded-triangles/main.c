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

	Triangle t = {
		.p = {
			{-200,-250},
			{200, 50},
			{20, 250},
		},
		.hue = {
			0.5,
			0.0,
			1.0
		}
	};

	// draw_filled_triangle(t, (Color){0,255,0});
	// draw_wireframe_triangle(t, BLACK);
	draw_shaded_triangle(t, (Color){0, 255, 0});

	draw_canvas("canvas.ppm");

	return 0;
}
