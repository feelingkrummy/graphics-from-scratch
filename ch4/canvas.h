#ifndef _CANVAS_H_
#define _CANVAS_H_

#define C_W 600
#define C_H 600

void put_pixel(int64_t x, int64_t y, Color col);
void draw_canvas(const char *path);

#endif
