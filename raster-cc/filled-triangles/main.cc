#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "canvas.h"
#include "draw.h"

int main(void) {
	printf("Filled Triangles\n");

	clear_canvas(WHITE);
	
	CanvasPoint p0 = {-200, -250};
	CanvasPoint p1 = {200, 50};
	CanvasPoint p2 = {20, 250};
	draw_filled_triangle(p0, p1, p2, GREEN);
	draw_wireframe_triangle(p0, p1, p2, BLACK);

	draw_canvas("result.ppm");
}
