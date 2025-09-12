#include <stdio.h>

#include "vec.h"
#include "canvas.h"
#include "draw.h"

struct Mat3x3 {
	double e[3][3];
};

int main(void) {
	// Scene
	const ModelInstance objects[] = {
		{
			.type = CUBE,
			.data = get_model_data(CUBE),
			.pos = {-1.5, 0, 7},
		},
		{
			.type = CUBE,
			.data = get_model_data(CUBE),
			.pos = {1.25, 2, 7.5},
		}
	};
	const int64_t objects_len = sizeof(objects)/sizeof(*objects);

	// Start
	printf("Rasterizer\n");
	clear_canvas(BLACK);

	// Do stuff
	// printf("objects_len : %ld\n", objects_len);
	for (int64_t i = 0; i < objects_len; i += 1) {
		render_object(&objects[i]);
	}

	// Wrap Up
	draw_canvas("result.ppm");
	printf("Done!\n");
	return 0;
}
