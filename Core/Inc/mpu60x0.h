#pragma once
#include <stdbool.h>
#define MPU_ADDR           (0x68 << 1)

#define MPU_SMPLRT_DIV     0x19
#define MPU_CONFIG         0x1A
#define MPU_GYRO_CONFIG    0x1B
#define MPU_ACCEL_CONFIG   0x1C
#define MPU_PWR_MGMT_1     0x6B
#define MPU_WHO_AM_I       0x75
#define MPU_GYRO_XOUT_H    0x43

bool   MPU60x0_Init(void);
void   MPU60x0_ReadGyro(int16_t g[3]);
float  MPU_RAW2DPS(int16_t raw);
