#include "screen/text/text.h"
#include "font_default.c"

extern void screen_draw_wline(int, int, int, int, int);

const Character CHARACTER_UNKNOWN = {(int[]){
    0, 0, 50, 0,
    50, 0, 50, 100,
    50, 100, 0, 100,
    0, 100, 0, 0,
    0, 0, 50, 100,
    50, 0, 0, 100,
}, .strokes = 6};

Font TEXT_FONT = FONT_DEFAULT;
TextAttribute TEXT_ATTRIBUTE = TEXT_A_REGULAR;
int CURSOR_POS_X = 0, CURSOR_POS_Y = 0;
int TEXT_FONT_SIZE = 12;
int TEXT_FONT_WEIGHT = 1;
int TEXT_SPACING = 1;
int TEXT_TAB_SIZE = 4;


// font functions

void screen_change_font(Font Font) {
    TEXT_FONT = Font;
}

void screen_reset_font() {
    TEXT_FONT = FONT_DEFAULT;
}

void screen_set_font_size(int size) {
    TEXT_FONT_SIZE = size;
}

int screen_get_font_size() {
    return TEXT_FONT_SIZE;
}

void screen_set_font_weight(int weight) {
    TEXT_FONT_WEIGHT = weight;
}

int screen_get_font_weight() {
    return TEXT_FONT_WEIGHT;
}

// cursor functions

void screen_move_cursor(int x, int y) {
    CURSOR_POS_X = x;
    CURSOR_POS_Y = y;
}

// text functions

void screen_text_attrset(TextAttribute attr) {
    TEXT_ATTRIBUTE = attr;
}

void screen_text_attrrst() {
    TEXT_ATTRIBUTE = TEXT_A_REGULAR;
}

void screen_set_text_spacing(int spacing) {
    TEXT_SPACING = spacing;
}

int screen_get_text_spacing() {
    return TEXT_SPACING;
}

void screen_set_tab_size(int size) {
    TEXT_SPACING = size;
}

int screen_get_tab_size() {
    return TEXT_SPACING;
}

void screen_draw_character(Character character) {
    int x = CURSOR_POS_X + TEXT_SPACING, y = CURSOR_POS_Y + TEXT_SPACING;
    int x1, y1, x2, y2;
    int dpl = character.strokes * 4;
    
    for (int i=0; i<dpl; i+=4) {
        x1 = x + (character.drawpoints[i+0]*TEXT_FONT_SIZE)/100;
        y1 = y + (character.drawpoints[i+1]*TEXT_FONT_SIZE)/100;
        x2 = x + (character.drawpoints[i+2]*TEXT_FONT_SIZE)/100;
        y2 = y + (character.drawpoints[i+3]*TEXT_FONT_SIZE)/100;

        screen_draw_wline(x1, y1, x2, y2, TEXT_FONT_WEIGHT);
    }
}

void screen_draw_char(char ch) {

    if (ch == '\0') {
        return;
    }
    if (ch == '\r') {
        return;
    }
    if (ch == ' ') {
        CURSOR_POS_X = CURSOR_POS_X + (2*TEXT_SPACING);
        return;
    }
    if (ch == '\n') {
        CURSOR_POS_Y = CURSOR_POS_Y + (2*TEXT_SPACING) + TEXT_FONT_SIZE;
        return;
    }
    if (ch == '\t') {
        for (int i=0; i<TEXT_TAB_SIZE; i++)
            screen_draw_char(' ');
        return;
    }

    Character character = screen_get_character(ch, TEXT_FONT);
    int char_width = screen_get_char_width(ch, TEXT_FONT);
    screen_draw_character(character);
    screen_move_cursor(CURSOR_POS_X+char_width+TEXT_SPACING+TEXT_SPACING, CURSOR_POS_Y);
}

void screen_draw_wchar(char ch, int weight) {
    int ow = screen_get_font_weight();
    screen_set_font_weight(weight);
    screen_draw_char(ch);
    screen_set_font_weight(ow);
}

void screen_draw_string(char *str) {
    int l = 0;
    int sx = CURSOR_POS_X;
    char ch;
    while(str[l] != '\0')l++;
    for (int i=0; i<l; i++) {
        ch = str[i];
        if (ch == '\r')
            CURSOR_POS_X = sx;
        if (ch == '\n')
            CURSOR_POS_X = sx;
        screen_draw_char(ch);
    }
}

void screen_draw_wstring(char *str, int weight) {
    int ow = screen_get_font_weight();
    screen_set_font_weight(weight);
    screen_draw_string(str);
    screen_set_font_weight(ow);
}

Character screen_get_character(char ch, Font font) {
    Character character;
    switch (font) {
        case FONT_DEFAULT:
            character = font_default[(int)ch];
            if (character.strokes) return character;
    }
    return CHARACTER_UNKNOWN;
}

int screen_get_character_width(Character character) {
    int mx = 0, l = character.strokes * 4, x;
    for (int i=0; i<l; i++, i++) {
        x = character.drawpoints[i];
        if (x > mx) mx = x;
    }
    return (mx*TEXT_FONT_SIZE)/100;
}

int screen_get_char_width(char ch, Font font) {
    Character character = screen_get_character(ch, font);
    return screen_get_character_width(character);
}

int screen_get_string_width(char *str, Font font) {
    int w=0, l=0;
    while(str[l] != '\0')l++;
    for (int i=0; i<l; i++)
        w += screen_get_char_width(str[i], font);
    return w;
}


