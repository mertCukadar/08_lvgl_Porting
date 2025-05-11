#include "waveshare_rgb_lcd_port.h"
#include "lvgl.h"
#include <stdio.h>

#define BMP180_ADDR 0x77
#define BMP180_REG_CONTROL 0xF4
#define BMP180_CMD_READ_TEMP 0x2E
#define BMP180_REG_OUT_MSB 0xF6

lv_label_t *label;



void app_main()
{
    waveshare_esp32_s3_rgb_lcd_init();
    lvgl_port_lock(-1);

    // Basit bir label oluştur
    label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Temp: -- °C");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    lvgl_port_unlock();

    while (1) {
        int16_t raw_temp = bmp180_read_raw_temperature();
        float approx_temp = raw_temp / 340.0 + 36.53;  // Yaklaşık değer

        ESP_LOGI("BMP180", "Raw: %d  Temp: %.2f", raw_temp, approx_temp);

        // Ekranda güncelleme yap
        if (lvgl_port_lock(-1)) {
            char buf[32];
            snprintf(buf, sizeof(buf), "Temp: %.2f °C", approx_temp);
            lv_label_set_text(label, buf);
            lvgl_port_unlock();
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
