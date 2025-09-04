#ifndef _COLOR_H_
#define _COLOR_H_

typedef struct Color {
	uint8_t r, g, b, a;
} Color;

#define WHITE (Color){255, 255, 255}
#define BLACK (Color){0, 0, 0}

#endif
