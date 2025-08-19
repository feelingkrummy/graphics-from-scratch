#include <stdio.h>

#include "types.h"
#include "canvas.h"
#include "vec.h"

int main(void) {
	printf("Rasterizer\n");

	for (int64_t y = -SCREEN_HEIGHT/2; y < SCREEN_HEIGHT/2; y += 1) {
		for (int64_t x = -SCREEN_WIDTH/2; x < SCREEN_WIDTH/2; x += 1) {
			printf("Processing %6ld X %6ld ... \r", x, y);
			put_pixel(x, y, {0, 0, 255});
		}
	}
	printf("\n");

	draw_canvas("canvas.ppm");

	return 0;
}
