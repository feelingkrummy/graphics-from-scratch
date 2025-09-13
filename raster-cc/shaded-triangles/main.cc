#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "canvas.h"
#include "draw.h"

int main(void) {
	printf("Shaded Triangles\n");

	clear_canvas(WHITE);
	
	CanvasPoint p0 = {-200, -250, 0.5};
	CanvasPoint p1 = {200, 50, 0.0};
	CanvasPoint p2 = {20, 250, 1.0};
	draw_shaded_triangle(p0, p1, p2, GREEN);

	draw_canvas("result.ppm");
}
