#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"
#include "Delay.h"

#define CALIBRATION_SAMPLES 100

int16_t OffsetX, OffsetY, OffsetZ;

void MPU6050_GyroCalibration(void)
{
	int32_t SumX = 0;
	int32_t SumY = 0;
	int32_t SumZ = 0;
	
	int16_t AX, AY, AZ;
	int16_t GX, GY, GZ;
	uint16_t i;
	for(i=0; i <CALIBRATION_SAMPLES; i++)
	{
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		
		SumX += GX;
		SumY += GY;
		SumZ += GZ;
		
		Delay_ms(10);
		
	}
	OffsetX = SumX / CALIBRATION_SAMPLES;
	OffsetY = SumY / CALIBRATION_SAMPLES;
	OffsetZ = SumZ / CALIBRATION_SAMPLES;
}

void MPU_GyroCompensate(int16_t *GX, int16_t *GY, int16_t *GZ)
{
	*GX -= OffsetX;
	*GY -= OffsetY;
	*GZ -= OffsetZ;
}
