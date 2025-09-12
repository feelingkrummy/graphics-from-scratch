#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "canvas.h"
#include "draw.h"

int main(void) {
	printf("Lines\n");

	clear_canvas(WHITE);
	
	CanvasPoint p0 = {-200, -100};
	CanvasPoint p1 = {240, 120};
	draw_line(p0, p1, BLACK);

	p0 = {-50, -200};
	p1 = {60, 240};
	draw_line(p0, p1, BLACK);

	draw_canvas("result.ppm");
}
