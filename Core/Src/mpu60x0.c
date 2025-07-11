#include "stm32f4xx_hal.h"
#include "mpu60x0.h"

extern I2C_HandleTypeDef hi2c1;

static HAL_StatusTypeDef mpu_write(uint8_t reg, uint8_t data)
{
    return HAL_I2C_Mem_Write(&hi2c1, MPU_ADDR, reg,
                              I2C_MEMADD_SIZE_8BIT, &data, 1, HAL_MAX_DELAY);
}

static HAL_StatusTypeDef mpu_read(uint8_t reg, uint8_t *buf, uint8_t len)
{
    return HAL_I2C_Mem_Read(&hi2c1, MPU_ADDR, reg,
                             I2C_MEMADD_SIZE_8BIT, buf, len, HAL_MAX_DELAY);
}

bool MPU60x0_Init(void)
{
    uint8_t who;
    if (mpu_read(MPU_WHO_AM_I, &who, 1) != HAL_OK || (who & 0x7E) != 0x68)
        return false;                       /* bus or chip failure */

    /* Wake up, choose X-axis gyro as clock source (best stability) */
    mpu_write(MPU_PWR_MGMT_1, 0x01);

    /* ±2000 °/s full-scale (FS_SEL = 3) */
    mpu_write(MPU_GYRO_CONFIG, 0x18);

    /* ±2 g accel full-scale (AFS_SEL = 0) – change if you need accel */
    mpu_write(MPU_ACCEL_CONFIG, 0x00);

    /* Optional: set sample-rate divider.  0 → 1 kHz gyro output */
    mpu_write(MPU_SMPLRT_DIV, 0x07);        /* 125 Hz */

    /* Disable all digital-low-pass filters for now */
    mpu_write(MPU_CONFIG, 0x00);

    return true;
}

void MPU60x0_ReadGyro(int16_t g[3])
{
    uint8_t raw[6];
    mpu_read(MPU_GYRO_XOUT_H, raw, 6);

    g[0] = (int16_t)(raw[0] << 8 | raw[1]);   /* X */
    g[1] = (int16_t)(raw[2] << 8 | raw[3]);   /* Y */
    g[2] = (int16_t)(raw[4] << 8 | raw[5]);   /* Z */
}

float MPU_RAW2DPS(int16_t raw)
{
    /* For FS = ±2000 °/s → LSB sensitivity 16.4 LSB/°/s */
    return (float)raw / 16.4f;
}
