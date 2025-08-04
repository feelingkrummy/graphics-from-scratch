#ifndef _CANVAS_H_
#define _CANVAS_H_

#define C_W 1280u
#define C_H 720u

void put_pixel(uint64_t c_x, uint64_t c_y, Color col);
void draw_canvas(const char *path);

#endif
