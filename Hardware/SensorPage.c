#include "stm32f10x.h"                  // Device header
#include "OLED.h" 
#include "AD.h"

void SensorPage_Show(uint8_t page,
                     int16_t AX, int16_t AY, int16_t AZ,
                     int16_t GX, int16_t GY, int16_t GZ)
{
    uint16_t adcValue;

    if (page == 0)
    {
        OLED_ShowString(2, 1, "AX:");
        OLED_ShowChar(2, 4, (AX < 0) ? '-' : '+');
        OLED_ShowNum(2, 5, (AX < 0 ? -AX : AX) / 2048, 1);
        OLED_ShowChar(2, 6, '.');
        OLED_ShowNum(2, 7, ((AX < 0 ? -AX : AX) % 2048) * 100 / 2048, 2);
        OLED_ShowChar(2, 9, 'g');
        OLED_ShowString(2, 10, "   ");  

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
    else if (page == 1)
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
    else if (page == 2)
    {
        adcValue = AD_GetValue(ADC_Channel_0);

        
        OLED_ShowString(2, 1, "ADC:");
        OLED_ShowNum(2, 6, adcValue, 4);
    }
    else if (page == 3)
    {
        adcValue = AD_GetValue(ADC_Channel_1);

        
        OLED_ShowString(2, 1, "ADC:");
        OLED_ShowNum(2, 6, adcValue, 4);
    }
}



