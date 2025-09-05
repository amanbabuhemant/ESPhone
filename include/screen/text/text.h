#ifndef TEXT_H
#define TEXT_H

typedef struct {
    int *drawpoints;
    int strokes;
} Character;

typedef enum {
    FONT_DEFAULT,
} Font;

typedef enum {
    TEXT_A_REGULAR,
    TEXT_A_BOLD,
} TextAttribute;


extern Font TEXT_FONT;
extern TextAttribute TEXT_ATTRIBUTE;
extern int CURSOR_POS_X, CURSOR_POS_Y;
extern int TEXT_FONT_SIZE;
extern int TEXT_FONT_WEIGHT;
extern int TEXT_SPACING;
extern int TEXT_TAB_SIZE;


// font functions

void screen_change_font(Font);

void screen_reset_font();

void screen_set_font_size(int);

int screen_get_font_size();

void screen_set_font_weight(int);

int screen_get_font_weight();

// cursor functions

void screen_move_cursor(int, int);

// text functions

void screen_text_attrset(TextAttribute);

void screen_text_attrrst();

void screen_set_text_spacing(int);

int screen_get_text_spacing();

void screen_set_tab_size(int);

int screen_get_tab_size();

void screen_draw_character(Character);

void screen_draw_char(char);

void screen_draw_wchar(char, int);

void screen_draw_string(char *);

void screen_draw_wstring(char *, int);

Character screen_get_character(char, Font);

int screen_get_character_width(Character);

int screen_get_char_width(char, Font);

int screen_get_string_width(char *, Font);

#endif
