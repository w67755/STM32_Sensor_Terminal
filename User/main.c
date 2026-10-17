#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "Key.h"


uint8_t ID;
int16_t AX, AY, AZ, GX, GY, GZ;
uint8_t page = 0;


int main(void)
{		
	OLED_Init();
	MPU6050_Init();
	Key_Init();
	
	OLED_ShowString(1, 1, "ACC ID:");
	ID = MPU6050_GetID();
	OLED_ShowHexNum(1, 8, ID, 2);
	

	
		while (1)
{	
    MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
	GX += 15;
	GY += 2;
	GZ += 9;// MPU6050 静止零偏（原始计数）：GX=-15，GY=-2，GZ=-9

    if (page == 0)  // 加速度页
    {
        OLED_ShowString(2, 1, "AX:");
        OLED_ShowChar(2, 4, (AX < 0) ? '-' : '+');
        OLED_ShowNum(2, 5, (AX < 0 ? -AX : AX) / 2048, 1);
        OLED_ShowChar(2, 6, '.');
        OLED_ShowNum(2, 7, ((AX < 0 ? -AX : AX) % 2048) * 100 / 2048, 2);
        OLED_ShowChar(2, 9, 'g');
        OLED_ShowString(2, 10, "   ");  // 清除旧的 dps

        OLED_ShowString(3, 1, "AY:");
        OLED_ShowChar(3, 4, (AY < 0) ? '-' : '+');
        OLED_ShowNum(3, 5, (AY < 0 ? -AY : AY) / 2048, 1);
        OLED_ShowChar(3, 6, '.');
        OLED_ShowNum(3, 7, ((AY < 0 ? -AY : AY) % 2048) * 100 / 2048, 2);
        OLED_ShowChar(3, 9, 'g');
        OLED_ShowString(3, 10, "   ");

        OLED_ShowString(4, 1, "AZ:");
        OLED_ShowChar(4, 4, (AZ < 0) ? '-' : '+');
        OLED_ShowNum(4, 5, (AZ < 0 ? -AZ : AZ) / 2048, 1);
        OLED_ShowChar(4, 6, '.');
        OLED_ShowNum(4, 7, ((AZ < 0 ? -AZ : AZ) % 2048) * 100 / 2048, 2);
        OLED_ShowChar(4, 9, 'g');
        OLED_ShowString(4, 10, "   ");
    }
    else  // 角速度页
    {
        OLED_ShowString(2, 1, "GX:");
        OLED_ShowChar(2, 4, (GX < 0) ? '-' : '+');
        OLED_ShowNum(2, 5, (GX < 0 ? -GX : GX) * 10 / 164, 2);
        OLED_ShowChar(2, 7, '.');
        OLED_ShowNum(2, 8, (((GX < 0 ? -GX : GX) * 10) % 164) * 100 / 164, 2);
        OLED_ShowString(2, 10, "dps");

        OLED_ShowString(3, 1, "GY:");
        OLED_ShowChar(3, 4, (GY < 0) ? '-' : '+');
        OLED_ShowNum(3, 5, (GY < 0 ? -GY : GY) * 10 / 164, 2);
        OLED_ShowChar(3, 7, '.');
        OLED_ShowNum(3, 8, (((GY < 0 ? -GY : GY) * 10) % 164) * 100 / 164, 2);
        OLED_ShowString(3, 10, "dps");

        OLED_ShowString(4, 1, "GZ:");
        OLED_ShowChar(4, 4, (GZ < 0) ? '-' : '+');
        OLED_ShowNum(4, 5, (GZ < 0 ? -GZ : GZ) * 10 / 164, 2);
        OLED_ShowChar(4, 7, '.');
        OLED_ShowNum(4, 8, (((GZ < 0 ? -GZ : GZ) *10) % 164) * 100 / 164, 2);
        OLED_ShowString(4, 10, "dps");
    }

    Delay_ms(100);
    if (Key_GetNum() == 1)
{
    page = !page;

    if (page == 0)
    {
        OLED_ShowString(1, 1, "ACC ID: ");
        OLED_ShowHexNum(1, 9, ID, 2);
    }
    else
    {
        OLED_ShowString(1, 1, "GYRO ID:");
        OLED_ShowHexNum(1, 9, ID, 2);
    }
}
}
	}