#ifndef __I2C_PORT_H
#define __I2C_PORT_H

#pragma once

#include "waveshare_rgb_lcd_port.h"

uint16_t bmp180_read_raw_temperature();

void mpu6050_read_raw_gyroscope(int16_t *gx, int16_t *gy, int16_t *gz);
void mpu6050_read_raw_accelerometer(int16_t *ax, int16_t *ay, int16_t *az);

#endif // __I2C_PORT_H