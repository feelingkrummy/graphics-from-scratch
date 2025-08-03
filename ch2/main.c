#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>

#include "types.h"

#define C_W 1280u
#define C_H 720u

#define WHITE (Color){255, 255, 255}

const double V_w, V_h, d = 1;

Color canvas[C_W][C_H] = {0};

void put_pixel(uint64_t c_x, uint64_t c_y, Color col) {
	uint64_t s_x, s_y = 0;
	if ( c_x < -C_W/2 && c_x >= C_W/2 ) {
		return;
	}
	if ( c_y < -C_H/2 && c_y >= C_H/2 ) {
		return;
	}
	s_x = C_W/2 + c_x;
	s_y = C_H/2 - c_y;
	canvas[s_x][s_y] = col;
	return;
}

void draw_canvas(const char *path) {
	FILE* fd = fopen(path, "w");
	assert(fd);
	fprintf(fd, "P3\n%lu %lu\n255\n", C_W, C_H);
	for (uint64_t y = 0; y < C_H; y += 1) {
		for (uint64_t x = 0; x < C_W; x += 1) {
			fprintf(fd, "%d %d %d\n", canvas[x][y].r, canvas[x][y].g, canvas[x][y].b);
		}
	}
	fclose(fd);
}

Vec3 canvas_to_viewport(double x, double y) {
	return (Vec3){
		.x = x*V_w/C_W,
		.y = y*V_h/C_H,
		.z = d
	};
}

Color trace_ray(Vec3 origin, Vec2 direction, double t_min, double t_max) {
	double closest_t = INFINITY;
	double closes_sphere = 0.0;
}

int main(void) {

	Vec3 origin = {
		.x = 0,
		.y = 0,
		.z = 0
	};

	for (uint64_t x = -C_W/2; x < C_W/2; x += 1) {
		for (uint64_t y = -C_H/2; y < C_W/2; y += 1) {
			Vec3 D = canvas_to_viewport(x, y);
			Color col = trace_ray(origin, D, 1, inf);
		}
	}

	draw_canvas("canvas.ppm");
}
