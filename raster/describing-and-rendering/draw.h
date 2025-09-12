#ifndef _DRAW_H_
#define _DRAW_H_

#include <stdint.h>

#include "vec.h"
#include "color.h"

typedef struct Triangle {
	int64_t p[3];
	Color col;
} Triangle;

typedef enum ModelType {
	NONE,
	CUBE,
} ModelType;

typedef struct ModelData {
	Vec3 *verts;
	int64_t verts_len;
	Triangle *trigs;
	int64_t trigs_len;
} ModelData;

typedef struct ModelInstance {
	ModelType type;
	ModelData data;
	Vec3 pos;
} ModelInstance;

ModelData get_model_data(ModelType type);
// ModelInstance create_model_instance(ModelType type, Vec3 pos);

void draw_line(Point p0, Point p1, Color col);
// void draw_wireframe_triangle(Triangle t, Color col);
// void draw_filled_triangle(Triangle t, Color col);
// void draw_shaded_triangle(Triangle t, Color col);

void render_object(const ModelInstance* inst);


#endif
