#pragma once

struct Vec2 {
	double x, y;
};
using Point = Vec2;

Vec2 operator+(Vec2& lhs, Vec2& rhs);
Vec2 operator-(Vec2& lhs, Vec2& rhs);
Vec2 operator*(Vec2& v, double s);
Vec2 operator*(double s, Vec2& v);
double length(Vec2 v);
double dot(Vec2 a, Vec2 b);

struct Vec3 {
	double x, y, z;
};

Vec3 operator+(Vec3& lhs, Vec3& rhs);
Vec3 operator-(Vec3& lhs, Vec3& rhs);
Vec3 operator*(Vec3& v, double s);
Vec3 operator*(double s, Vec3& v);
double length(Vec3 v);
double dot(Vec3 a, Vec3 b);
