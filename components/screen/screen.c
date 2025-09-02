#include <math.h>
#include <stdbool.h>
#include "ssd1306/ssd1306.h"
#include "screen/screen.h"

bool SCREEN_FG = true;
bool SCREEN_BG = false;

void screen_init() {
    ssd1306_init();
}

void screen_deinit() {
    ssd1306_deinit();
}

void screen_switch_color() {
    SCREEN_FG = !SCREEN_FG;
    SCREEN_BG = !SCREEN_BG;
}

void screen_reset_color() {
    SCREEN_FG = true;
    SCREEN_BG = false;
}

void screen_clear() {
    ssd1306_clear();
}

void screen_fill() {
    ssd1306_fill();
}

void screen_update() {
    ssd1306_update_screen();
}

// drawing functions

void screen_draw_pixel(int x, int y, bool on) {
    ssd1306_draw_pixel(x, y, on ? SCREEN_FG : SCREEN_BG);
}

void screen_draw_line(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (abs(dx) > abs(dy)) {
        if (x1 > x2) {
            int tmp;
            tmp = x1; x1 = x2; x2 = tmp;
            tmp = y1; y1 = y2; y2 = tmp;
            dx = x2 - x1; dy = y2 - y1;
        }
        double m = (double)dy / (double)dx;
        for (int x = x1; x <= x2; x++) {
            int y = (int)(m * (x - x1) + y1 + 0.5);
            screen_draw_pixel(x, y, true);
        }
    } else {
        if (y1 > y2) {
            int tmp;
            tmp = x1; x1 = x2; x2 = tmp;
            tmp = y1; y1 = y2; y2 = tmp;
            dx = x2 - x1; dy = y2 - y1;
        }
        double m_inv = (double)dx / (double)dy;
        for (int y = y1; y <= y2; y++) {
            int x = (int)(m_inv * (y - y1) + x1 + 0.5);
            screen_draw_pixel(x, y, true);
        }
    }
}

void screen_draw_wline(int x1, int y1, int x2, int y2, int width) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    double len = sqrt(dx*dx + dy*dy);
    double px = -(double)dy / len;
    double py =  (double)dx / len;
    int half = width / 2;

    for (int w = -half; w <= half; w++) {
        int ox = (int)round(px*w);
        int oy = (int)round(py*w);
        screen_draw_line(x1 + ox, y1 + oy, x2 + ox, y2 + oy);
    }
}

void screen_draw_rectangle(int x, int y, int width, int height, bool fill) {
    if (fill)
        screen_draw_rectangle_filled(x, y, width, height);
    else
        screen_draw_rectangle_hollow(x, y, width, height);
}

void screen_draw_rectangle_hollow(int x, int y, int width, int height) {
    int _x = x, _y = y;
    for (;_x<x+width;_x++) {
        screen_draw_pixel(_x, y, true);
        screen_draw_pixel(_x, y+height-1, true);
    }
    for (;_y<y+height;_y++) {
        screen_draw_pixel(x, _y, true);
        screen_draw_pixel(x+width, _y, true);
    }
}

void screen_draw_rectangle_filled(int x, int y, int width, int height) {
    int _x, _y = y;
    for (;_y<y+height;_y++) {
        for (_x=x;_x<x+width;_x++) {
            screen_draw_pixel(_x, _y, true);
        }
    }
}

void screen_draw_circle(int x, int y, int r, bool fill) {
    int i, j;
    double d;
    for (i=y-r-1; i<y+r+1; i++) {
        for (j=x-r-1; j<x+r+1; j++) {
            d = sqrt(pow(x - j, 2) + pow(y - i, 2));
            if (fill) {
                if (d <= (double)r)
                    screen_draw_pixel(j, i, true);
            } else {
                if (fabs(d-r) <= 0.5)
                    screen_draw_pixel(j, i, true);
            }
        }
    }
}

void screen_draw_circle_hollow(int x, int y, int r) {
    screen_draw_circle(x, y, r, false);
}

void screen_draw_circle_filled(int x, int y, int r) {
    screen_draw_circle(x, y, r, true);
}

