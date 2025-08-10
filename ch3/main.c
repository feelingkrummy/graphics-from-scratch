#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "types.h"
#include "canvas.h"
#include "light.h"

const double V_w = 1.0; // This implies a square image
const double V_h = 1.0;
const double proj_plane_d = 1.0;

const Sphere spheres[] = {
	{
		.center = {0, -1, 3},
		.radius = 1,
		.color = {255, 0, 0}, // Red
		.specular = 500
	},
	{
		.center = {2, 0, 4},
		.radius = 1,
		.color = {0, 0, 255}, // Blue
		.specular = 500
	},
	{
		.center = {-2, 0, 4},
		.radius = 1,
		.color = {0, 255, 0}, // Green
		.specular = 10
	},
	{
		.center = {0, -5001, 0},
		.radius = 5000,
		.color = {255, 255, 0}, // Yellow
		.specular = 1000
	}
};
const uint64_t spheres_len = sizeof(spheres)/sizeof(Sphere);

const Light lights[] = {
	{
		.type = AMBIENT,
		.intensity = 0.2
	},
	{
		.type = POINT,
		.intensity = 0.6,
		.position = {2, 1, 0}
	},
	{
		.type = DIRECTIONAL,
		.intensity = 0.2,
		.direction = {1, 4, 4}
	}
};
const uint64_t lights_len = sizeof(lights)/sizeof(Light);

double clamp(double val, double low, double high) {
	if ( val < low ) {
		return low;
	}
	if ( val > high ) {
		return high;
	}
	return val;
}

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

double compute_lighting(Vec3 point, Vec3 norm, Vec3 view, double specular_exp) {
	double intensity = 0.0;
	Vec3 light_ray = {0};
	for (int i = 0; i < lights_len; i += 1) {
		const Light *light = &lights[i];

		if (light->type == AMBIENT) {
			intensity += light->intensity;
		} else {
			if (light->type == POINT) {
				light_ray = vec3_sub(light->position, point);
			} else {
				light_ray = light->direction;
			}

			// Diffuse
			double norm_dot_light = vec3_dot(norm, light_ray);
			if (norm_dot_light > 0) {
				intensity += light->intensity *
					(norm_dot_light/(vec3_len(norm) * vec3_len(light_ray)));
			}

			// Specular
			if (specular_exp != -1.0) {
				Vec3 R = vec3_sub(vec3_scale(norm, 2.0*norm_dot_light), light_ray);
				double r_dot_v = vec3_dot(R, view);
				if (r_dot_v > 0) {
					intensity += light->intensity * pow(r_dot_v/(vec3_len(R) * vec3_len(view)), specular_exp);
				}
			}
		}
	}
	return intensity;
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
			closest_t = t.t2;
			closest_sphere = spheres[i];
			result_found = 1;
		}
	}
	if (!result_found) {
		return WHITE;
	}

	Vec3 point = vec3_add(origin, vec3_scale(direction, closest_t));
	Vec3 norm = vec3_sub(point, closest_sphere.center);
	norm = vec3_scale(norm, 1.0/vec3_len(norm));

	Vec3 view = vec3_scale(direction, -1);

	return (Color){
		.r = clamp(closest_sphere.color.r * compute_lighting(point, norm, view, closest_sphere.specular), 0, 255),
		.g = clamp(closest_sphere.color.g * compute_lighting(point, norm, view, closest_sphere.specular), 0, 255),
		.b = clamp(closest_sphere.color.b * compute_lighting(point, norm, view, closest_sphere.specular), 0, 255)
	};
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
