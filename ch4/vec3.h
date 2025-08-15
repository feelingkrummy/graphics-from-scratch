#ifndef _VEC3_H_
#define _VEC3_H_

typedef struct Vec3 {
	double x, y, z;
} Vec3;

Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
double vec3_dot(Vec3 a, Vec3 b);
double vec3_len(Vec3 a);
Vec3 vec3_scale(Vec3 a, double s);

#endif
