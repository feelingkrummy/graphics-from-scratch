#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "canvas.h"
#include "vec.h"
#include "draw.h"

#define V_W 1.0
#define V_H 1.0

#define VIEWPORT_D 1.0

Point viewport_to_canvas(double x, double y) {
	return (Point){
		.x = x*(C_W/V_W),
		.y = y*(C_H/V_H),
	};
}

Point project_vertex(Vec3 v) {
	return viewport_to_canvas(v.x * VIEWPORT_D/ v.z, v.y * VIEWPORT_D / v.z);
}

int main(void) {

	clear_canvas(BLACK);

	// The four "front" vertices
	Vec3 vAf = {-2, -0.5, 5};
	Vec3 vBf = {-2,  0.5, 5};
	Vec3 vCf = {-1,  0.5, 5};
	Vec3 vDf = {-1, -0.5, 5};

	// The four "back" vertices
	Vec3 vAb = {-2, -0.5, 6};
	Vec3 vBb = {-2,  0.5, 6};
	Vec3 vCb = {-1,  0.5, 6};
	Vec3 vDb = {-1, -0.5, 6};

	// The front face
	draw_line(project_vertex(vAf), project_vertex(vBf), BLUE);
	draw_line(project_vertex(vBf), project_vertex(vCf), BLUE);
	draw_line(project_vertex(vCf), project_vertex(vDf), BLUE);
	draw_line(project_vertex(vDf), project_vertex(vAf), BLUE);
	
	// The back face
	draw_line(project_vertex(vAb), project_vertex(vBb), RED);
	draw_line(project_vertex(vBb), project_vertex(vCb), RED);
	draw_line(project_vertex(vCb), project_vertex(vDb), RED);
	draw_line(project_vertex(vDb), project_vertex(vAb), RED);
	
	// The front-to-back edges
	draw_line(project_vertex(vAf), project_vertex(vAb), GREEN);
	draw_line(project_vertex(vBf), project_vertex(vBb), GREEN);
	draw_line(project_vertex(vCf), project_vertex(vCb), GREEN);
	draw_line(project_vertex(vDf), project_vertex(vDb), GREEN);

	draw_canvas("canvas.ppm");

	return 0;
}
