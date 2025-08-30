#include <stdio.h>
#include <assert.h>

#include "canvas.h"

static Color screen[SCREEN_WIDTH][SCREEN_HEIGHT] = {0};

void put_pixel(int64_t canvas_x, int64_t canvas_y, Color c) {
	if (canvas_x < -SCREEN_WIDTH/2 || canvas_x >= SCREEN_WIDTH/2) {
		return;
	}
	if (canvas_y < -SCREEN_HEIGHT/2 || canvas_y >= SCREEN_HEIGHT/2) {
		return;
	}
	uint64_t screen_x = canvas_x + SCREEN_WIDTH/2;
	uint64_t screen_y = SCREEN_HEIGHT/2 - canvas_y - 1;
	screen[screen_x][screen_y] = c;
}

void draw_canvas(const char* path) {
	FILE* fd = fopen(path, "w");
	assert(fd);
	fprintf(fd, "P3\n%lu %lu\n255\n", SCREEN_WIDTH, SCREEN_HEIGHT);
	for (int64_t y = 0; y < SCREEN_HEIGHT; y += 1) {
		for (int64_t x = 0; x < SCREEN_WIDTH; x += 1) {
			fprintf(fd, "%d %d %d\n", screen[x][y].r, screen[x][y].g, screen[x][y].b);
		}
	}
	fclose(fd);
}
