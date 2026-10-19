#ifndef __CALIBRATION_H
#define __CALIBRATION_H

void MPU6050_GyroCalibration(void);
void MPU_GyroCompensate(int16_t *GX, int16_t *GY, int16_t *GZ);

#endif
