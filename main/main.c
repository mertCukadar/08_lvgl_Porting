#include "waveshare_rgb_lcd_port.h"
#include "lvgl.h"
#include "i2c_port.h"
#include <stdio.h>

void app_main()
{
 
    // LCD ve LVGL başlatma
    waveshare_esp32_s3_rgb_lcd_init();

    while (1) {
        // MPU6050 bağlantısını kontrol et
        mpu6050_check_ack();

        // Eğer ekrana bir şey çizeceksen:
        if (lvgl_port_lock(0)) {  // kilidi dene (0 timeout = hemen dene)
            // lvgl API ile ekran güncellemeleri yapılabilir burada
            // Örneğin: lv_label_set_text(my_label, "Bağlantı OK");

            lvgl_port_unlock();  // kilidi serbest bırak
        }

        vTaskDelay(pdMS_TO_TICKS(1000)); // 1 saniye bekle
    }
}
