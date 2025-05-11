#include "i2c_port.h"
#include "driver/i2c.h"
#include "esp_log.h"



int16_t bmp180_read_raw_temperature() {
    uint8_t data[2];

   
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (BMP180_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, BMP180_REG_CONTROL, true);
    i2c_master_write_byte(cmd, BMP180_CMD_READ_TEMP, true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);

    vTaskDelay(pdMS_TO_TICKS(5)); 

  
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (BMP180_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, BMP180_REG_OUT_MSB, true);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (BMP180_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, data, 2, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);

    // Verileri birleştir
    int16_t raw_temp = (data[0] << 8) | data[1];
    return raw_temp;
}


void mpu6050_check_ack(){
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd); // ← Eksikti
    i2c_master_write_byte(cmd, (MPU6050_ADDR << 1) | I2C_MASTER_WRITE, true); // ← READ yerine WRITE

    ESP_LOGI("I2C", "MPU6050 ACK check");
    printf("MPU ADDR: 0x%X\n", (MPU6050_ADDR << 1) | I2C_MASTER_WRITE);

    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);

    if (ret == ESP_OK) {
        ESP_LOGI("I2C", "ACK received");
    } else {
        ESP_LOGE("I2C", "No ACK received");
    }
}


