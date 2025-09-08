#ifndef WIDGET_H
#define WIDGET_H

#include "event.h"

typedef struct Widget Widget;

typedef enum {
    WIDGET_TYPE_LABEL,
    WIDGET_TYPE_BUTTON,
    WIDGET_TYPE_ENTRY,
} WidgetType;

typedef enum {
    WIDGET_ANCHOR_TOP_LEFT,
    WIDGET_ANCHOR_TOP_MID,
    WIDGET_ANCHOR_TOP_RIGHT,
    WIDGET_ANCHOR_LEFT_MID,
    WIDGET_ANCHOR_CENTER,
    WIDGET_ANCHOR_RIGHT_MID,
    WIDGET_ANCHOR_BOTTOM_LEFT,
    WIDGET_ANCHOR_BOTTOM_MID,
    WIDGET_ANCHOR_BOTTOM_RIGHT,
} WidgetAnchor;

typedef struct {
    char *text;
} LabelData;

typedef struct {
    char *text;
} ButtonData;

typedef struct {
    char *buffer;
    int cursor;
} EntryData;

typedef struct Widget {
    int id;
    int x;
    int y;
    int width;
    int height;
    WidgetType type;
    WidgetAnchor anchor;
    char *name;
    union {
        LabelData label;
        ButtonData button;
        EntryData entry;
    } data;
    WidgetEventListener *event_listeners;
} Widget;

extern int WIDGET_ID;

// Functions

// Widget Rendring Functions

void screen_render_widget(Widget *);

void screen_render_widgets(Widget *, int);

void screen_render_label(Widget *);

void screen_render_button(Widget *);

void screen_render_entry(Widget *);

// Widget Init Functions

Widget *screen_widget_new(WidgetType);

Widget *screen_widget_new_label(char *);

Widget *screen_widget_new_button(char *);

Widget *screen_widget_new_entry();

// Widget Method Functions

//// Widget

void screen_widget_get_widget_top_left(Widget *, int *, int *);

int screen_widget_get_id(Widget *);

char *screen_widget_get_name(Widget *);

char *screen_widget_get_name_dup(Widget *);

void screen_widget_set_name(Widget *, char *);

//// Label

char *screen_widget_label_get_text(Widget *);

void screen_widget_label_set_text(Widget *, char *);

//// Button

char *screen_widget_button_get_text(Widget *);

void screen_widget_button_set_text(Widget *, char *);

//// Entry

char *screen_widget_entry_get_text(Widget *);

char *screen_widget_entry_get_text_dup(Widget *);

void screen_widget_entry_set_text(Widget *, char *);

int screen_widget_entry_get_cursor(Widget *);

void screen_widget_entry_set_cursor(Widget *, int);

void screen_widget_entry_move_cursor_left(Widget *);

void screen_widget_entry_move_cursor_right(Widget *);

#endif
