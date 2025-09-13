#pragma once

struct Vec2 {
	union {
		struct { double x, y; };
		double e[2];
	};

	double& operator[] (size_t idx) {
		return e[idx];
	};

	const double& operator[] (size_t idx) const {
		return e[idx];
	}
};

Vec2 operator+(Vec2 lhs, Vec2 rhs);
Vec2 operator-(Vec2 lhs, Vec2 rhs);
Vec2 operator*(double lhs, Vec2 rhs);
Vec2 operator*(Vec2 lhs, double rhs);
double dot(Vec2 a, Vec2 b);
double len(Vec2 a);

struct Vec3 {
	union {
		struct { double x, y, z; };
		double e[3];
	};

	double& operator[] (size_t idx) {
		return e[idx];
	};

	const double& operator[] (size_t idx) const {
		return e[idx];
	}
};

Vec3 operator+(Vec3 lhs, Vec3 rhs);
Vec3 operator-(Vec3 lhs, Vec3 rhs);
Vec3 operator*(double lhs, Vec3 rhs);
Vec3 operator*(Vec3 lhs, double rhs);
double dot(Vec3 a, Vec3 b);
double len(Vec3 a);
