#pragma once

struct Color {
	uint8_t r, g, b, a;
};

#define WHITE (Color){255, 255, 255, 0}
#define BLACK (Color){0, 0, 0, 0}

#define RED (Color){255, 0, 0, 0}
#define GREEN (Color){0, 255, 0, 0}
#define BLUE (Color){0, 0, 255, 0}
#define YELLOW (Color){255, 255, 0, 0}
#define MAGENTA (Color){255, 0, 255, 0}
#define CYAN (Color){0, 255, 255, 0}
