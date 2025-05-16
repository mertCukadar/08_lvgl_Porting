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

    // Create a basic label
    label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Temp: -- °C");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    lvgl_port_unlock();

    while (1) {
        /* May need to change function name to something like 
        i2cPort_bmp180_ReadRawTemperature() 
        because we really do not know where to look for this function. 
        Look: https://aws.github.io/amazon-freertos/202107.00/html2/main/guide_developer_styleguide.html
        Section: " Functions (and function-like macros)" */
        int16_t raw_temp = bmp180_read_raw_temperature();
        float approx_temp = raw_temp / 340.0 + 36.53;  //Approx Value

        ESP_LOGI("BMP180", "Raw: %d  Temp: %.2f", raw_temp, approx_temp);

        //init ui from ui.h
        ui_init();

        // An update on screen
        // if (lvgl_port_lock(-1)) {
        //     char buf[32];
        //     snprintf(buf, sizeof(buf), "Temp: %.2f °C", approx_temp);
        //     lv_label_set_text(label, buf);
        //     lvgl_port_unlock();
        // }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
