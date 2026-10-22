#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "Key.h"
#include "Calibration.h"
#include "Serial.h"
#include "AD.h"
#include "SensorPage.h"
#include "DHT11.h"

uint8_t ID;
int16_t AX, AY, AZ, GX, GY, GZ;
uint8_t page = 0;

uint8_t Serialcount;
uint16_t TempADC;
uint16_t LightADC;
uint16_t IRADC;
uint8_t DHT11_Temp, DHT11_Humid;
uint8_t DHT11_Counter = 0;
 


int main(void)
{		
	OLED_Init();
	MPU6050_Init();
	Key_Init();
	Serial_Init();
	AD_Init();
	DHT11_Init();
	
	Serial_SendString("MPU6050 start\r\n");
	
	OLED_ShowString(1, 1, "ACC ID:");
	ID = MPU6050_GetID();
	OLED_ShowHexNum(1, 8, ID, 2);
	
	OLED_Clear();
	OLED_ShowString(1, 1, "KEEP STILL");
	MPU6050_GyroCalibration();

	OLED_Clear();
	OLED_ShowString(1, 1, "ACC ID: ");
	OLED_ShowHexNum(1, 9, ID, 2);
	

	
		while (1)
{	
    MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
	MPU_GyroCompensate(&GX , &GY, &GZ);
	
	DHT11_Counter++;
	if (DHT11_Counter >= 20)
	{
    DHT11_Counter = 0;
    DHT11_ReceiveData(&DHT11_Temp, &DHT11_Humid);
	}
	
	Serialcount ++;
	if (Serialcount >= 5)
	{
		Serialcount = 0;
		Serial_SendDataLine(AX, AY, AZ, GX, GY, GZ);
	}
	

    SensorPage_Show(page, AX, AY, AZ, GX, GY, GZ);

    Delay_ms(100);
   if (Key_GetNum() == 1)
{
    page++;

    if (page >= 5)
    {
        page = 0;
    }

    OLED_Clear();
}
    if (page == 0)
    {
        OLED_ShowString(1, 1, "ACC ID:");
        OLED_ShowHexNum(1, 9, ID, 2);
    }
    else if (page == 1)
    {
        OLED_ShowString(1, 1, "GYRO ID:");
        OLED_ShowHexNum(1, 9, ID, 2);
    }
    else if (page == 2)
    {
        OLED_ShowString(1, 1, "TEMP SENSOR");
    }
    else if (page == 3)
    {
        OLED_ShowString(1, 1, "LIGHT SENSOR");
    }
	else
	{
		OLED_ShowString(1, 1, "DHT11");

		OLED_ShowString(2, 1, "Temp:");
		OLED_ShowString(3, 1, "Humi:");
		OLED_ShowNum(2, 7, DHT11_Temp, 2);
        OLED_ShowChar(2, 9, 'C');

        OLED_ShowNum(3, 7, DHT11_Humid, 2);
        OLED_ShowChar(3, 9, '%');
	}		

}
	}