#include <malloc.h>
#include "screen/ui/widget.h"
#include "screen/ui/event.h"

// Functions

void screen_widget_add_event_listener(Widget *widget, WidgetEventType type, void (*handler)(WidgetEvent *event, void *userdata), void *userdata) {
    WidgetEventListener *event_listener = malloc(sizeof(WidgetEventListener));
    event_listener->type = type;
    event_listener->handler = handler;
    event_listener->userdata = userdata;
    event_listener->next = widget->event_listeners;
    widget->event_listeners = event_listener;
}

void screen_widget_dispatch_event(Widget *widget, WidgetEvent *event) {
    WidgetEventListener *event_listener = malloc(sizeof(WidgetEventListener));
    event_listener = widget->event_listeners;
    while (1) {
        if (event_listener == NULL)
            return;
        if (event_listener->type == event->type)
            return event_listener->handler(event, event_listener->userdata);
        event_listener = event_listener->next;
    }
}

// Default Event Listenes

