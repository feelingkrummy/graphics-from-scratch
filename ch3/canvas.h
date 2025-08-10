#ifndef _CANVAS_H_
#define _CANVAS_H_

#define C_W 600
#define C_H 600

void put_pixel(int64_t c_x, int64_t c_y, Color col);
void draw_canvas(const char *path);

#endif
