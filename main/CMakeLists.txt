file(GLOB_RECURSE UI_SOURCES "ui/*.c")

idf_component_register(
    SRCS "i2c_port.c" "waveshare_rgb_lcd_port.c" "main.c" "lvgl_port.c" "i2c_port.c" ${UI_SOURCES}
    INCLUDE_DIRS ".")

idf_component_get_property(lvgl_lib lvgl__lvgl COMPONENT_LIB)
target_compile_options(${lvgl_lib} PRIVATE -Wno-format)
