#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "types.h"
#include "canvas.h"

Color canvas[C_W][C_H] = {0};

void put_pixel(int64_t x, int64_t y, Color col) {
	if ( x < 0 || x >= C_W ) {
		return;
	}
	if ( y < 0 || y >= C_H ) {
		return;
	}
	canvas[x][y] = col;
	return;
}

void draw_canvas(const char *path) {
	FILE* fd = fopen(path, "w");
	assert(fd);
	fprintf(fd, "P3\n%lu %lu\n255\n", C_W, C_H);
	for (int64_t y = 0; y < C_H; y += 1) {
		for (int64_t x = 0; x < C_W; x += 1) {
			fprintf(fd, "%d %d %d\n", canvas[x][y].r, canvas[x][y].g, canvas[x][y].b);
		}
	}
	fclose(fd);
}
