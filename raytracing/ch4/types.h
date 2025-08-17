#ifndef _TYPES_H_
#define _TYPES_H_

#include "vec3.h"

typedef struct Color {
	uint8_t r, g, b;
} Color;

#define WHITE (Color){255, 255, 255}
#define BLACK (Color){0, 0, 0}

typedef struct Sphere {
	Vec3 center;
	double radius;
	Color color;
	double specular;
	double reflective;
} Sphere;

#endif
