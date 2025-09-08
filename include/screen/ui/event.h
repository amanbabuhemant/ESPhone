#ifndef EVENT_H
#define EVENT_H

typedef struct Widget Widget;

typedef enum {
    WIDGET_EVENT_CLICX,
    WIDGET_EVENT_KEYPRESS,
    WIDGET_EVENT_FOCUS,
    WIDGET_EVENT_BLUR,
    WIDGET_EVENT_CHANGE,
} WidgetEventType;

typedef struct {
    WidgetEventType type;
    Widget *widget;
    void *data;
} WidgetEvent;

typedef struct WidgetEventListener {
    WidgetEventType type;
    void (*handler)(WidgetEvent *, void *);
    void *userdata;
    struct WidgetEventListener *next;
} WidgetEventListener;

// Functions

void screen_widget_add_event_listener(Widget *, WidgetEventType, void (*)(WidgetEvent *, void *), void *);

void screen_widget_dispatch_event(Widget *, WidgetEvent *);

// Default Event Listenes

#endif
