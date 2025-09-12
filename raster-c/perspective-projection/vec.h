#ifndef _VEC3_H_
#define _VEC3_H_

typedef struct Vec2 {
	union{
		struct { double x, y; };
		double e[2];
	};
} Vec2;
typedef Vec2 Point;

Vec2 vec2_add(Vec2 a, Vec2 b);
Vec2 vec2_sub(Vec2 a, Vec2 b);
double vec2_dot(Vec2 a, Vec2 b);
double vec2_len(Vec2 a);
Vec2 vec2_scale(Vec2 a, double s);

typedef struct Vec3 {
	union {
		struct { double x, y, z; };
		double e[3];
	};
} Vec3;

Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
double vec3_dot(Vec3 a, Vec3 b);
double vec3_len(Vec3 a);
Vec3 vec3_scale(Vec3 a, double s);

#endif
