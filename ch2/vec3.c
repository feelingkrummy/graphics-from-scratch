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
