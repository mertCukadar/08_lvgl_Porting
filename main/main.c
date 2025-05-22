#include "waveshare_rgb_lcd_port.h"
#include "lvgl.h"
#include "i2c_port.h"
#include <stdio.h>
#include "ui/ui.h"

lv_label_t *label;

void app_main()
{
    waveshare_esp32_s3_rgb_lcd_init();
    lvgl_port_lock(-1);

    ui_init(); // <-- SADECE BURADA BİR KEZ ÇAĞIR!

    lvgl_port_unlock();

    while (1) {
        int16_t raw_temp = bmp180_read_raw_temperature();
        float approx_temp = raw_temp / 340.0 + 36.53;

        ESP_LOGI("BMP180", "Raw: %d  Temp: %.2f", raw_temp, approx_temp);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

