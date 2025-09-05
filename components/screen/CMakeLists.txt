idf_component_register(
    SRCS "screen.c" "text/text.c" "text/font_default.c"
    INCLUDE_DIRS "." "../../include/"
    REQUIRES ssd1306
)
