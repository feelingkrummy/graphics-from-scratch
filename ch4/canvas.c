#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "types.h"
#include "canvas.h"

Color canvas[C_W][C_H] = {0};

void put_pixel(int64_t c_x, int64_t c_y, Color col) {
	int64_t s_x, s_y = 0;
	if ( c_x < -C_W/2 && c_x >= C_W/2 ) {
		return;
	}
	if ( c_y < -C_H/2 && c_y >= C_H/2 ) {
		return;
	}
	s_x = C_W/2 + c_x;
	s_y = C_H/2 - c_y - 1;
	if ( !(s_x < 600 && s_y < 600) ) {
		fprintf(stderr, "(%ld, %ld) => (%ld, %ld)\n", c_x, c_y, s_x, s_y);
		assert(0);
	}
	if (c_y >= C_H/2-1 || s_y == 0 || s_y >= 599 ) {
		fprintf(stderr, "(%ld, %ld) => (%ld, %ld) with {%d, %d, %d}\n", c_x, c_y, s_x, s_y,
				col.r, col.g, col.b);
	}
	canvas[s_x][s_y] = col;
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
