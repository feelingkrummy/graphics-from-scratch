#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>

#include "types.h"

const double V_w, V_h, d = 1;

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
