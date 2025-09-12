#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "vec.h"
#include "color.h"
#include "draw.h"
#include "canvas.h"

#define V_W 1.0
#define V_H 1.0

#define VIEWPORT_D 1.0

static Point viewport_to_canvas(double x, double y) {
	return (Point){
		.x = x*(C_W/V_W),
		.y = y*(C_H/V_H),
	};
}

static Point project_vertex(Vec3 v) {
	return viewport_to_canvas(v.x * VIEWPORT_D/ v.z, v.y * VIEWPORT_D / v.z);
}

static const Vec3 cube_verts[] = {
	{ 1,  1,  1},
	{-1,  1,  1},
	{-1, -1,  1},
	{ 1, -1,  1},
	{ 1,  1, -1},
	{-1,  1, -1},
	{-1, -1, -1},
	{ 1, -1, -1},
};
// const int64_t cube_verts_len = sizeof(cube_verts)/sizeof(Vec3); 

static const Triangle cube_trigs[] = {
	{ 0, 1, 2, RED },
	{ 0, 2, 3, RED },
	{ 4, 0, 3, GREEN },
	{ 4, 3, 7, GREEN },
	{ 5, 4, 7, BLUE },
	{ 5, 7, 6, BLUE },
	{ 1, 5, 6, YELLOW },
	{ 1, 6, 2, YELLOW },
	{ 4, 5, 1, MAGENTA },
	{ 4, 1, 0, MAGENTA },
	{ 2, 6, 7, CYAN },
	{ 2, 7, 3, CYAN },
};
// const int64_t cube_trigs_len = sizeof(cube_trigs)/sizeof(Triangle);

typedef struct DoubleArray {
	int64_t len, cap;
	double* ptr;
} DoubleArray;

static DoubleArray create_double_array(int64_t cap) {
	DoubleArray new = {0};
	assert(cap >= 0);
	printf("create_double_array: %ld\n", cap);
	// new.ptr = calloc(cap, sizeof(double));
	new.ptr = malloc(cap*sizeof(double));
	new.cap = cap;
	new.len = 0;
	return new;
}

static void delete_double_array(DoubleArray *a) {
	assert(a->ptr);
	if (a->ptr != nullptr) {
		free(a->ptr);
		a->ptr = nullptr;
	}
	a->cap = 0;
	a->len = 0;
}

static DoubleArray concatenate_double_arrays(DoubleArray first, DoubleArray second) {
	DoubleArray new = {0};
	size_t elem_size = sizeof *(new.ptr);
	new.cap = first.len + second.len;
	new.len = new.cap;
	new.ptr = calloc(new.cap, elem_size);
	memcpy(new.ptr, first.ptr, first.len*elem_size);
	memcpy(new.ptr + first.len, second.ptr, second.len*elem_size);
	return new;
}

typedef struct Int64Array {
	int64_t len, cap;
	int64_t* ptr;
} Int64Array;

static Int64Array create_int64_array(int64_t cap) {
	Int64Array new = {0};
	assert(cap >= 0);
	printf("create_int64_array: %ld\n", cap);
	new.ptr = calloc(cap, sizeof(*new.ptr));
	new.cap = cap;
	new.len = 0;
	return new;
}

static void delete_int64_array(Int64Array *a) {
	assert(a->ptr);
	if (a->ptr != nullptr) {
		free(a->ptr);
		a->ptr = nullptr;
	}
	a->cap = 0;
	a->len = 0;
}

static Int64Array concatenate_int64_arrays(Int64Array first, Int64Array second) {
	Int64Array new = {0};
	size_t elem_size = sizeof *(new.ptr);
	new.cap = first.len + second.len;
	new.len = new.cap;
	new.ptr = calloc(new.cap, elem_size);
	memcpy(new.ptr, first.ptr, first.len*elem_size);
	memcpy(new.ptr + first.len, second.ptr, second.len*elem_size);
	return new;
}

static void swap_points(Point *a, Point *b) {
	Point t = *a;
	*a = *b;
	*b = t;
}

static void swap_double(double *a, double *b) {
	double t = *a;
	*a = *b;
	*b = t;
}

static DoubleArray interpolate_double(double i0, double d0, double i1, double d1) {
	DoubleArray values = {0};
	if (i0 == i1) {
		values = create_double_array(1);
		values.len = 1;
		values.ptr[0] = d0;
		return values;
	}

	int64_t n = (int64_t)(i1-i0+1);
	values = create_double_array(n);

	double a = (double)(d1 - d0) / (double)(i1 - i0);
	double d = (double)d0;

	for (int64_t i = i0; i <= i1; i++) {
		size_t idx = i - (int64_t)i0;
		// the segfault is here, however, the problem is my frivilous converting
		// between double and int64_t eventually you get a rounding error and that's no good
		values.ptr[idx] = d;
		values.len += 1;
		d = d + a;
	}
	
	return values;
}

static Int64Array interpolate_int64(int64_t i0, int64_t d0, int64_t i1, int64_t d1) {
	Int64Array values = {0};
	if (i0 == i1) {
		values = create_int64_array(1);
		values.len = 1;
		values.ptr[0] = d0;
		return values;
	}

	int64_t n = (int64_t)(i1-i0+1);
	values = create_int64_array(n);

	double a = (double)(d1 - d0) / (double)(i1 - i0);
	double d = (double)d0;

	for (int64_t i = i0; i <= i1; i++) {
		size_t idx = i - (int64_t)i0;
		// the segfault is here, however, the problem is my frivilous converting
		// between int64_t and int64_t_t eventually you get a rounding error and that's no good
		values.ptr[idx] = round(d);
		values.len += 1;
		d = d + a;
	}
	
	return values;
}

ModelData get_model_data(ModelType type) {
	switch(type) {
		case CUBE:
			return (ModelData){
				.verts = (Vec3*)cube_verts,
				.verts_len = sizeof(cube_verts)/sizeof(Vec3),
				.trigs = (Triangle*)cube_trigs,
				.trigs_len = sizeof(cube_trigs)/sizeof(Triangle),
			};
		default:
			return (ModelData){
				.verts = nullptr,
				.verts_len = 0,
				.trigs = nullptr,
				.trigs_len = 0,
			};
	}
}

void draw_line(Point p0, Point p1, Color col) {
	if (fabs(p1.x - p0.x) > fabs(p1.y - p0.y)) {
		if (p0.x > p1.x) {
			swap_points(&p0, &p1);
		}
		Int64Array ys = interpolate_int64(p0.x, p0.y, p1.x, p1.y);
		for (int64_t x = p0.x; x <= p1.x; x++) {
			size_t idx = x - (int64_t)p0.x;
			put_pixel(x, round(ys.ptr[idx]), col);
		}
		delete_int64_array(&ys);
	} else {
		if (p0.y > p1.y) {
			swap_points(&p0, &p1);
		}
		Int64Array xs = interpolate_int64(p0.y, p0.x, p1.y, p1.x);
		for (int64_t y = p0.y; y <= p1.y; y++) {
			size_t idx = y - (int64_t)p0.y;
			put_pixel(round(xs.ptr[idx]), y, col);
		}
		delete_int64_array(&xs);
	}
}

void draw_wireframe_triangle(Point p0, Point p1, Point p2, Color col) {
	draw_line(p0, p1, col);
	draw_line(p1, p2, col);
	draw_line(p2, p0, col);
}

void draw_filled_triangle(Point p0, Point p1, Point p2, Color col) {
	if (p1.y < p0.y) swap_points(&p0, &p1);
	if (p2.y < p0.y) swap_points(&p2, &p0);
	if (p2.y < p1.y) swap_points(&p2, &p1);

	Int64Array x01 = interpolate_int64(p0.y, p0.x, p1.y, p1.x);
	Int64Array x12 = interpolate_int64(p1.y, p1.x, p2.y, p2.x);
	Int64Array x02 = interpolate_int64(p0.y, p0.x, p2.y, p2.x);

	// Remove Last Item
	x01.len -= 1;
	x01.ptr[x01.len] = 0;

	// concatenate arrays
	Int64Array x012 = concatenate_int64_arrays(x01, x12);

	int64_t m = x012.len/2;
	Int64Array x_left, x_right;
	if (x02.ptr[m] < x012.ptr[m]) {
		x_left = x02;
		x_right = x012;
	} else {
		x_left = x012;
		x_right = x02;
	}

	for (int64_t y = p0.y; y <= p2.y; y++) {
		size_t idx = y-(int64_t)p0.y; 
		for (int64_t x = round(x_left.ptr[idx]); x <= round(x_right.ptr[idx]); x++) {
			put_pixel(round(x), round(y), col);
		}
	}

	delete_int64_array(&x01);
	delete_int64_array(&x12);
	delete_int64_array(&x02);
	delete_int64_array(&x012);
}

void draw_shaded_triangle(
		Triangle t,
		Point p0, 
		Point p1,
		Point p2,
		Color col,
		double h0,
		double h1,
		double h2
) {
	if (p1.y < p0.y) {
		swap_points(&p0, &p1);
		swap_double(&h0, &h1);
	}
	if (p2.y < p0.y) {
		swap_points(&p2, &p0);
		swap_double(&h2, &h0);
	}
	if (p2.y < p1.y) {
		swap_points(&p2, &p1);
		swap_double(&h2, &h1);
	}

	Int64Array x01 = interpolate_int64(p0.y, p0.x, p1.y, p1.x);
	DoubleArray h01 = interpolate_double(p0.y, h0, p1.y, h1);

	Int64Array x12 = interpolate_int64(p1.y, p1.x, p2.y, p2.x);
	DoubleArray h12 = interpolate_double(p1.y, h1, p2.y, h2);

	Int64Array x02 = interpolate_int64(p0.y, p0.x, p2.y, p2.x);
	DoubleArray h02 = interpolate_double(p0.y, h0, p2.y, h2);

	// Remove Last Item
	x01.len -= 1;
	x01.ptr[x01.len] = 0;

	h01.len -= 1;
	h01.ptr[h01.len] = 0;

	// concatenate arrays
	Int64Array x012 = concatenate_int64_arrays(x01, x12);
	DoubleArray h012 = concatenate_double_arrays(h01, h12);

	int64_t m = x012.len/2;
	Int64Array x_left, x_right;
	DoubleArray h_left, h_right;
	if (x02.ptr[m] < x012.ptr[m]) {
		x_left = x02;
		x_right = x012;

		h_left = h02;
		h_right = h012;
	} else {
		x_left = x012;
		x_right = x02;

		h_left = h012;
		h_right = h02;
	}

	for (int64_t y = p0.y; y <= p2.y; y++) {
		size_t idx = y-(int64_t)p0.y;
		double x_l = round(x_left.ptr[idx]);
		double x_r = round(x_right.ptr[idx]);

		DoubleArray h_segment = interpolate_double(x_l, h_left.ptr[idx], x_r, h_right.ptr[idx]);

		for (int64_t x = x_l; x <= x_r; x++) {
			Color shaded = {
				.r = round(col.r*h_segment.ptr[x-(int64_t)x_l]),
				.g = round(col.g*h_segment.ptr[x-(int64_t)x_l]),
				.b = round(col.b*h_segment.ptr[x-(int64_t)x_l])
			};
			put_pixel(round(x), round(y), shaded);
		}

		delete_double_array(&h_segment);
	}

	delete_int64_array(&x01);
	delete_double_array(&h01);

	delete_int64_array(&x12);
	delete_double_array(&h12);

	delete_int64_array(&x02);
	delete_double_array(&h02);

	delete_int64_array(&x012);
	delete_double_array(&h012);
}

static void render_triangle(Triangle t, Point *projected, int64_t projected_len) {
	draw_wireframe_triangle(
			projected[t.p[0]],
			projected[t.p[1]],
			projected[t.p[2]],
			t.col
		);
}

void render_object(const ModelInstance* inst) {
	Point projected[2048];
	int64_t projected_len = 0;
	const ModelData* data = &(inst->data);
	for (int64_t v = 0; v < data->verts_len; v++) {
		Vec3 v_prime = vec3_add(data->verts[v], inst->pos);
		projected[projected_len++] = project_vertex(v_prime);
	}

	for (int64_t t = 0; t < data->trigs_len; t++) {
		render_triangle(data->trigs[t], projected, projected_len);
	}
}

/*
ModelInstance create_model_instance(ModelType type, Vec3 pos) {
	return (ModelInstance) {
		.type = type,
		.data = get_model_data(type),
		.pos = pos,
	};
}
*/
