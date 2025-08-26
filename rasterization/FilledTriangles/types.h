#pragma once

#include <stdint.h>

struct Points {
	int64_t x, y;
};

struct Color {
	uint8_t r,g,b;
};

constexpr Color WHITE = {255, 255, 255};
constexpr Color BLACK = {0, 0, 0};
