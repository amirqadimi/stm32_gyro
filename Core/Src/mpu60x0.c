#include "mpu60x0.h"

// Wake up the MPU6050 (clear sleep bit)
HAL_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef *hi2c) {
    uint8_t data = 0;
    return HAL_I2C_Mem_Write(hi2c, MPU6050_I2C_ADDR, MPU6050_REG_PWR_MGMT_1, 1, &data, 1, 100);
}

// Read all accel and gyro data
HAL_StatusTypeDef MPU6050_Read_All(I2C_HandleTypeDef *hi2c, MPU6050_Data_t *data) {
    uint8_t buf[14];
    HAL_StatusTypeDef res = HAL_I2C_Mem_Read(hi2c, MPU6050_I2C_ADDR, MPU6050_REG_ACCEL_XOUT_H, 1, buf, 14, 100);
    if (res != HAL_OK) return res;
    data->accel_x = (int16_t)(buf[0] << 8 | buf[1]);
    data->accel_y = (int16_t)(buf[2] << 8 | buf[3]);
    data->accel_z = (int16_t)(buf[4] << 8 | buf[5]);
    // Skipping temperature: buf[6], buf[7]
    data->gyro_x  = (int16_t)(buf[8] << 8 | buf[9]);
    data->gyro_y  = (int16_t)(buf[10] << 8 | buf[11]);
    data->gyro_z  = (int16_t)(buf[12] << 8 | buf[13]);
    return HAL_OK;
} 