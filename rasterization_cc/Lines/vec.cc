#include <math.h>

#include "vec.h"

Vec2 operator+(Vec2& lhs, Vec2& rhs) {
	return {
		lhs.x + rhs.x,
		lhs.y + rhs.y
	};
}

Vec2 operator-(Vec2& lhs, Vec2& rhs) {
	return {
		lhs.x - rhs.x,
		lhs.y - rhs.y
	};
}

Vec2 operator*(Vec2& v, double s) {
	return {
		v.x * s,
		v.y * s
	};
}

Vec2 operator*(double s, Vec2& v) {
	return {
		v.x * s,
		v.y * s
	};
}

double length(Vec2 v) {
	return sqrt(dot(v, v));
}

double dot(Vec2 a, Vec2 b) {
	return a.x*b.x + a.y*b.y;
}


Vec3 operator+(Vec3& lhs, Vec3& rhs) {
	return {
		lhs.x + rhs.x,
		lhs.y + rhs.y,
		lhs.z + rhs.z
	};
}

Vec3 operator-(Vec3& lhs, Vec3& rhs) {
	return {
		lhs.x - rhs.x,
		lhs.y - rhs.y,
		lhs.z - rhs.z
	};
}

Vec3 operator*(Vec3& v, double s) {
	return {
		v.x * s,
		v.y * s,
		v.z * s
	};
}

Vec3 operator*(double s, Vec3& v) {
	return {
		v.x * s,
		v.y * s,
		v.z * s
	};
}

double length(Vec3 v) {
	return sqrt(dot(v, v));
}

double dot(Vec3 a, Vec3 b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
