#ifndef __MPU60X0_H
#define __MPU60X0_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

#define MPU6050_I2C_ADDR         (0x68 << 1)  // 7-bit address shifted for HAL

// MPU6050 Register Addresses
#define MPU6050_REG_PWR_MGMT_1   0x6B
#define MPU6050_REG_ACCEL_XOUT_H 0x3B
#define MPU6050_REG_GYRO_XOUT_H  0x43

// Data structure for sensor readings
typedef struct {
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;
} MPU6050_Data_t;

HAL_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef MPU6050_Read_All(I2C_HandleTypeDef *hi2c, MPU6050_Data_t *data);

#endif // __MPU60X0_H 