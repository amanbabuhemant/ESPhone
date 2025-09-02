
#ifndef SCREEN_H
#define SCREEN_H

#include <stdbool.h>

extern bool SCREEN_FG;
extern bool SCREEN_BG;

void screen_init();

void screen_deinit();

void screen_switch_color();

void screen_reset_color();

void screen_clear();

void screen_fill();

void screen_update();

// drawing function

void screen_draw_pixel(int, int, bool);

void screen_draw_line(int, int, int, int);

void screen_draw_wline(int, int, int, int, int);

void screen_draw_rectangle(int, int, int, int, bool);

void screen_draw_rectangle_hollow(int, int, int, int);

void screen_draw_rectangle_filled(int, int, int, int);

void screen_draw_circle(int, int, int, bool);

void screen_draw_circle_hollow(int, int, int);

void screen_draw_circle_filled(int, int, int);

#endif
