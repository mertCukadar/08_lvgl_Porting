#ifndef __I2C_PORT_H
#define __I2C_PORT_H

#pragma once

#include "waveshare_rgb_lcd_port.h"

#define I2C_MASTER_SCL_IO 19         // SCL pin
#define I2C_MASTER_SDA_IO 18         // SDA pin
#define I2C_MASTER_NUM I2C_NUM_0     // I2C port numarası
#define I2C_MASTER_FREQ_HZ 100000    // I2C frekansı 100kHz
#define MPU6050_ADDR 0x68            // MPU6050 I2C adresi


#define BMP180_ADDR 0x77
#define BMP180_REG_CONTROL 0xF4
#define BMP180_CMD_READ_TEMP 0x2E
#define BMP180_REG_OUT_MSB 0xF6

#define MPU6050_ADDR 0x68

esp_err_t i2c_master_init();


int16_t bmp180_read_raw_temperature();

void mpu6050_read_raw_gyroscope(int16_t *gx, int16_t *gy, int16_t *gz);
void mpu6050_read_raw_accelerometer(int16_t *ax, int16_t *ay, int16_t *az);
void mpu6050_check_ack();
#endif // __I2C_PORT_H