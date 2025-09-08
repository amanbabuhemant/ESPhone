#include <malloc.h>
#include <string.h>
#include "screen/screen.h"
#include "screen/text/text.h"
#include "screen/ui/widget.h"

#include "symbols.c"

int WIDGET_ID = 0;

// Functions

// Widget Rendring Functions

void screen_render_widget(Widget *widget) {
    switch (widget->type) {
        case WIDGET_TYPE_LABEL:
            screen_render_label(widget);
            break;
        case WIDGET_TYPE_BUTTON:
            screen_render_button(widget);
            break;
        case WIDGET_TYPE_ENTRY:
            screen_render_entry(widget);
            break;
    }
}

void screen_render_widgets(Widget *widgets, int count) {
    for (int i=0; i<count; i++) {
        screen_render_widget(&widgets[i]);
    }
}

void screen_render_label(Widget *label) {
    int x, y;
    screen_widget_get_widget_top_left(label, &x, &y);
    screen_move_cursor(x+1, y+1);
    screen_set_font_size(label->height-2);
    screen_draw_string(label->data.label.text);
}

void screen_render_button(Widget *button) {
    int x, y;
    screen_widget_get_widget_top_left(button, &x, &y);
    screen_draw_rectangle_hollow(x, y, button->width, button->height);
    screen_set_font_size(button->height - 4);
    screen_move_cursor(x+1, y+1);
    screen_draw_string(button->data.button.text);
}

void screen_render_entry(Widget *entry) {
    int x, y;
    screen_widget_get_widget_top_left(entry, &x, &y);
    screen_draw_rectangle_hollow(x, y, entry->width, entry->height);
    if (entry->data.entry.buffer == NULL)
        return;
    screen_set_font_size(entry->height - 4);
    screen_move_cursor(x+1, y+1);
    int cw, offset, c = entry->data.entry.cursor;
    char *before_cursor, *after_cursor;
    before_cursor = strdup(entry->data.entry.buffer);
    after_cursor = strdup(entry->data.entry.buffer);
    before_cursor[c] = '\0';
    after_cursor = &after_cursor[c];
    screen_draw_string(before_cursor);
    offset = screen_get_string_width(before_cursor, TEXT_FONT) + x;
    screen_move_cursor(offset + TEXT_SPACING, y+1);
    screen_draw_character(symbol_entry_cursor);
    cw = screen_get_character_width(symbol_entry_cursor);
    screen_move_cursor(offset + TEXT_SPACING + cw + TEXT_SPACING + 1, y+1);
    screen_draw_string(after_cursor);
}

// Widget Init Functions

Widget *screen_widget_new(WidgetType type) {
    Widget *widget = malloc(sizeof(Widget));
    WIDGET_ID++;
    widget->id = WIDGET_ID;
    widget->x = 0;
    widget->y = 0;
    widget->width = 32;
    widget->height = 12;
    widget->anchor = WIDGET_ANCHOR_TOP_LEFT;
    widget->type = type;
    widget->name = strdup("widget");
    return widget;
}

Widget *screen_widget_new_label(char *text) {
    Widget *widget = screen_widget_new(WIDGET_TYPE_LABEL);
    widget->data.label.text = strdup(text);
    widget->name = strdup("label");
    return widget;
}

Widget *screen_widget_new_button(char *text) {
    Widget *widget = screen_widget_new(WIDGET_TYPE_BUTTON);
    widget->data.button.text = strdup(text);
    widget->name = strdup("button");
    return widget;
}

Widget *screen_widget_new_entry() {
    Widget *widget = screen_widget_new(WIDGET_TYPE_ENTRY);
    widget->name = strdup("entry");
    widget->data.entry.buffer = strdup("");
    widget->data.entry.cursor = 0;
    return widget;
}

// Widget Method Functions

//// Widget

void screen_widget_get_widget_top_left(Widget *widget, int *x, int *y) {
    int w = widget->width;
    int h = widget->height;
    int hw = w / 2;
    int hh = h / 2;

    *x = widget->x;
    *y = widget->y;

    switch (widget->anchor) {
        case WIDGET_ANCHOR_TOP_LEFT:
            return;
        case WIDGET_ANCHOR_TOP_MID:
            *x = widget->x - hw;
            return;
        case WIDGET_ANCHOR_TOP_RIGHT:
            *x = widget->x - w;
            return;
        case WIDGET_ANCHOR_LEFT_MID:
            *y = widget->y - hh;
            return;
        case WIDGET_ANCHOR_CENTER:
            *x = widget->x - hw;
            *y = widget->y - hh;
            return;
        case WIDGET_ANCHOR_RIGHT_MID:
            *x = widget->x - w;
            *y = widget->y - hh;
            return;
        case WIDGET_ANCHOR_BOTTOM_LEFT:
            *y = widget->y - h;
            return;
        case WIDGET_ANCHOR_BOTTOM_MID:
            *x = widget->x - hw;
            *y = widget->y - h;
            return;
        case WIDGET_ANCHOR_BOTTOM_RIGHT:
            *x = widget->x - w;
            *y = widget->y - h;
            return;
    }
}

int screen_widget_get_id(Widget *widget) {
    return widget->id;
}

char *screen_widget_get_name(Widget *widget) {
    if (widget->name == NULL)
        return "";
    return widget->name;
}

char *screen_widget_get_name_dup(Widget *widget) {
    if (widget->name == NULL)
        return "";
    char *name = strdup(widget->name);
    return name;
}

void screen_widget_set_name(Widget *widget, char *name) {
    free(widget->name);
    widget->name = strdup(name);
}

//// Label

char *screen_widget_label_get_text(Widget *label) {
    if (label->data.label.text == NULL)
        return "";
    return label->data.label.text;
}

void screen_widget_label_set_text(Widget *label, char *text) {
    free(label->data.label.text);
    label->data.label.text = strdup(text);
}

//// Button

char *screen_widget_button_get_text(Widget *button) {
    if (button->data.button.text == NULL)
        return "";
    return button->data.label.text;
}

void screen_widget_button_set_text(Widget *button, char *text) {
    free(button->data.button.text);
    button->data.button.text = strdup(text);
}

//// Entry

char *screen_widget_entry_get_text(Widget *entry) {
    return entry->data.entry.buffer;
}

char *screen_widget_entry_get_text_dup(Widget *entry) {
    if (entry->data.entry.buffer == NULL)
        return "";
    return strdup(entry->data.entry.buffer);
}

void screen_widget_entry_set_text(Widget *entry, char *text) {
    free(entry->data.entry.buffer);
    entry->data.entry.buffer = strdup(text);
}

int screen_widget_entry_get_cursor(Widget *entry) {
    return entry->data.entry.cursor;
}

void screen_widget_entry_set_cursor(Widget *entry, int pos) {
    int l = strlen(screen_widget_entry_get_text(entry));
    if (pos < 0)
        pos = 0;
    if (pos > l)
        pos = l;
}

void screen_widget_entry_move_cursor_left(Widget *entry) {
    if (entry->data.entry.cursor > 0)
        entry->data.entry.cursor -= 1;
}

void screen_widget_entry_move_cursor_right(Widget *entry) {
    int l = strlen(screen_widget_entry_get_text(entry));
    if (entry->data.entry.cursor < l)
        entry->data.entry.cursor += 1;
}
