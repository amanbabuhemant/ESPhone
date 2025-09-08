idf_component_register(
    SRCS "screen.c"
    SRCS "text/text.c" "text/font_default.c"
    SRCS "ui/widget.c" "ui/event.c"
    INCLUDE_DIRS "." "../../include/"
    REQUIRES ssd1306
)
