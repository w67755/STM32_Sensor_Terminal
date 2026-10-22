#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//写引脚高低电平
void DHT11_W_DQ(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_0, (BitAction)BitValue);
}

//读引脚高低电平
uint8_t DHT11_R_DQ(void)
{
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0);
	return BitValue;
}

//设置为推挽输出
void DHT11_SetOutput(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
}

//设置为上拉输入
void DHT11_SetInput(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
}

void DHT11_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	DHT11_SetOutput();
}

//起始
void DHT11_Start(void)
{
	DHT11_W_DQ(1);
	DHT11_W_DQ(0);
	Delay_ms(20);
	DHT11_W_DQ(1);
	Delay_us(30);
}

//接收一个字节
uint8_t DHT11_ReciveByte(void)
{	
	uint8_t i, Wait = 0;
	uint8_t Byte = 0x00; 
	for (i = 0; i < 8; i ++)
	{
		while (DHT11_R_DQ() == 0 && (Wait < 100))          //50us过后跳出循环
		{
			Delay_us(1);
			Wait ++;
		}
		Wait = 0;
		Delay_us(40);
		if (DHT11_R_DQ() == 1)
	{
		Byte |= (0x80 >> i);					//高位先出
		while (DHT11_R_DQ() == 1 && (Wait < 100)) //防止卡死
		{
			Delay_us(1);
			Wait ++;
		}
		Wait = 0;
	}	
	
	}
	
	return Byte;
}

void DHT11_ReceiveData(uint8_t *DHT11_Temp, uint8_t *DHT11_Humid)
{	uint8_t Wait = 0;
	uint8_t	T_Low, T_High, RH_Low, RH_High, DataSum, CountSum;

	DHT11_SetOutput();
	
	DHT11_Start();
	
	DHT11_SetInput();
	
	while (DHT11_R_DQ() == 0 && (Wait < 100))  //拉低80us
		{
			Delay_us(1);
			Wait ++;
		}
			Wait = 0;
	while (DHT11_R_DQ() == 1 && (Wait < 100))  //拉高80us
		{
			Delay_us(1);
			Wait ++;
		}
			Wait = 0;
		
	RH_High = DHT11_ReciveByte(); //湿度整数部分
	RH_Low = DHT11_ReciveByte(); //湿度小数部分
	T_High = DHT11_ReciveByte();//温度整数部分
	T_Low = DHT11_ReciveByte();//温度小数部分
	DataSum = DHT11_ReciveByte();//校验和
		
	while (DHT11_R_DQ() == 0 && (Wait < 100))  //拉低50us
		{
			Delay_us(1);
			Wait ++;
		}
			Wait = 0;
	CountSum = RH_High + RH_Low + T_High + T_Low;
	if (CountSum == DataSum)
	{
		*DHT11_Temp = T_High;
		*DHT11_Humid = RH_High;
	}
}
