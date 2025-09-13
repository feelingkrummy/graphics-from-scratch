#include "vec.h"

Vec2 operator+(Vec2 lhs, Vec2 rhs) {
	return {
		.x = lhs.x + rhs.x,
		.y = lhs.y + rhs.y,
	};
}

Vec2 operator-(Vec2 lhs, Vec2 rhs) {
	return {
		.x = lhs.x - rhs.x,
		.y = lhs.y - rhs.y,
	};
}

Vec2 operator*(double lhs, Vec2 rhs) {
	return {
		.x = lhs*rhs.x,
		.y = lhs*rhs.y,
	};
}

Vec2 operator*(Vec2 lhs, double rhs) {
	return {
		.x = rhs*lhs.x,
		.y = rhs*lhs.y,
	};
}

double dot(Vec2 a, Vec2 b) {
	return a.x*b.x + a.y*b.y;
}

double len(Vec2 a) {
	return sqrt(dot(a, a));
}

Vec3 operator+(Vec3 lhs, Vec3 rhs) {
	return {
		.x = lhs.x + rhs.x,
		.y = lhs.y + rhs.y,
		.z = lhs.z + rhs.z,
	};
}

Vec3 operator-(Vec3 lhs, Vec3 rhs) {
	return {
		.x = lhs.x - rhs.x,
		.y = lhs.y - rhs.y,
		.z = lhs.z - rhs.z,
	};
}

Vec3 operator*(double lhs, Vec3 rhs) {
	return {
		.x = lhs*rhs.x,
		.y = lhs*rhs.y,
		.z = lhs*rhs.z,
	};
}

Vec3 operator*(Vec3 lhs, double rhs) {
	return {
		.x = rhs*lhs.x,
		.y = rhs*lhs.y,
		.z = rhs*lhs.z,
	};
}

double dot(Vec3 a, Vec3 b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

double len(Vec3 a) {
	return sqrt(dot(a, a));
}
