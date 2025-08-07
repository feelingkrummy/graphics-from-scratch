#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "types.h"
#include "canvas.h"

const double V_w = 1.0; // This implies a square image, try setting to 16:9
const double V_h = 1.0;
const double proj_plane_d = 1.0;
const Sphere spheres[] = {
	{
		.center = {0, -1, 3},
		.radius = 1,
		.color = {255, 0, 0}
	},
	{
		.center = {2, 0, 4},
		.radius = 1,
		.color = {0, 0, 255}
	},
	{
		.center = {-2, 0, 4},
		.radius = 1,
		.color = {0, 255, 0}
	}
};
const uint64_t spheres_len = sizeof(spheres)/sizeof(Sphere);

Vec3 canvas_to_viewport(double x, double y) {
	return (Vec3){
		.x = x*V_w/C_W,
		.y = y*V_h/C_H,
		.z = proj_plane_d
	};
}

typedef struct IntersectResult {
	double t1, t2;
} IntersectResult;

IntersectResult intersect_ray_sphere(Vec3 origin, Vec3 direction, Sphere s) {
	double r = s.radius;
	Vec3 CO = vec3_sub(origin, s.center);
	
	double a = vec3_dot(direction, direction);
	double b = 2.0*vec3_dot(CO, direction);
	double c = vec3_dot(CO, CO) - r*r;

	double discriminant = b*b - 4*a*c;
	if (discriminant < 0) {
		return (IntersectResult){INFINITY, INFINITY};
	}

	return (IntersectResult){
		.t1 = (-b + sqrt(discriminant))/(2*a),
		.t2 = (-b - sqrt(discriminant))/(2*a)
	};
}

Color trace_ray(Vec3 origin, Vec3 direction, double t_min, double t_max) {
	double closest_t = INFINITY;
	Sphere closest_sphere = {0};
	int result_found = 0;
	for (int i = 0; i < spheres_len; i += 1) {
		IntersectResult t = intersect_ray_sphere(origin, direction, spheres[i]);
		if ( t.t1 > t_min && t.t1 < t_max && t.t1 < closest_t ) {
			closest_t = t.t1;
			closest_sphere = spheres[i];
			result_found = 1;
		}
		if ( t.t2 > t_min && t.t2 < t_max && t.t2 < closest_t ) {
			closest_t = t.t1;
			closest_sphere = spheres[i];
			result_found = 1;
		}
	}
	if (!result_found) {
		return WHITE;
	}
	return closest_sphere.color;
}

int main(void) {

	Vec3 origin = {
		.x = 0,
		.y = 0,
		.z = 0
	};

	printf("Sphere len : %d\n", spheres_len);
	printf("Starting loop ... \n");

	for (int64_t x = -C_W/2; x < C_W/2; x += 1) {
		for (int64_t y = -C_H/2; y < C_H/2; y += 1) {
			printf("Checking %6ld X %6ld ... \r", x, y);
			Vec3 D = canvas_to_viewport(x, y);
			Color col = trace_ray(origin, D, 1, INFINITY);
			put_pixel(x, y, col);
		}
	}

	printf("\nWriting to file ... \n");
	draw_canvas("canvas.ppm");
}
