#ifndef _COLOR_H_
#define _COLOR_H_

typedef struct Color {
	uint8_t r, g, b, a;
} Color;

#define WHITE (Color){255, 255, 255}
#define BLACK (Color){0, 0, 0}
#define RED (Color){255, 0, 0}
#define GREEN (Color){0, 255, 0}
#define BLUE (Color){0, 0, 255}

#endif
