#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "vec3.h"

typedef enum LightType {
	AMBIENT,
	POINT,
	DIRECTIONAL
} LightType;

typedef struct Light {
	LightType type;
	double intensity;
	union {
		Vec3 position;
		Vec3 direction;
	};
} Light;

#endif
