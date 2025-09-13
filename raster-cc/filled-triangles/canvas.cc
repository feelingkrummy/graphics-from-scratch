#include <stdint.h>
#include <assert.h>
#include <stdio.h>

#include "canvas.h"
#include "color.h"

static Color canvas[C_W][C_H] = {0};

void clear_canvas(Color c) {
	for (int64_t x = 0; x < C_W; x++) {
		for (int64_t y = 0; y < C_H; y++) {
			canvas[x][y] = c;
		}
	}
}

void put_pixel(int64_t canvas_x, int64_t canvas_y, Color col) {
	if (canvas_x < -C_W/2 || canvas_x >= C_W/2) {
		return;
	}
	if (canvas_y < -C_H/2 || canvas_y >= C_H/2) {
		return;
	}
	uint64_t screen_x = canvas_x + C_W/2;
	uint64_t screen_y = C_H/2 - canvas_y - 1;
	canvas[screen_x][screen_y] = col;
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
