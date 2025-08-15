#include <math.h>

#include "vec3.h"

Vec3 vec3_add(Vec3 a, Vec3 b) {
	return (Vec3){
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z,
	};
}

Vec3 vec3_sub(Vec3 a, Vec3 b) {
	return (Vec3){
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z,
	};
}

double vec3_dot(Vec3 a, Vec3 b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

double vec3_len(Vec3 a) {
	return sqrt(vec3_dot(a, a));
}

Vec3 vec3_scale(Vec3 a, double s) {
	return (Vec3){
		.x = a.x*s,
		.y = a.y*s,
		.z = a.z*s
	};
}
