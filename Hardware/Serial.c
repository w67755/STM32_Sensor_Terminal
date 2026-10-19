#include "stm32f10x.h"                  // Device header


void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1 ;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_Cmd(USART1, ENABLE);
}
void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}
void Serial_SendString(char *String)
{
	while (*String != '\0')
	{
		Serial_SendByte(*String);
		String ++;
	}
}
void Serial_SendSignedNum(int8_t Num)
{
	uint16_t absNum;
	if (Num < 0)
    {
        Serial_SendByte('-');
        absNum = (uint16_t)(-Num);
    }
    else
    {
        Serial_SendByte('+');
        absNum = (uint16_t)Num;
    }
	Serial_SendByte(absNum / 100 % 10 + '0');
	Serial_SendByte(absNum / 10 % 10 + '0');
	Serial_SendByte(absNum % 10 + '0');
}

void Serial_SendFixed2(int32_t value)
{
    uint32_t absValue;
    uint32_t integerPart;
    uint8_t digits[6];
    uint8_t count = 0;

    if (value < 0)
    {
        Serial_SendByte('-');
        absValue = (uint32_t)(-value);
    }
    else
    {
        Serial_SendByte('+');
        absValue = (uint32_t)value;
    }

    integerPart = absValue / 100;

    /* 取出整数部分各位 */
    do
    {
        digits[count++] = integerPart % 10;
        integerPart /= 10;
    } while (integerPart > 0);

    /* 反向发送整数部分 */
    while (count > 0)
    {
        Serial_SendByte(digits[--count] + '0');
    }

    Serial_SendByte('.');
    Serial_SendByte(absValue / 10 % 10 + '0');
    Serial_SendByte(absValue % 10 + '0');
}

void Serial_SendDataLine(int16_t AX, int16_t AY, int16_t AZ,
                         int16_t GX, int16_t GY, int16_t GZ)
{
    Serial_SendString("AX=");
    Serial_SendFixed2((int32_t)AX * 100 / 2048);
    Serial_SendString("g, AY=");
    Serial_SendFixed2((int32_t)AY * 100 / 2048);
    Serial_SendString("g, AZ=");
    Serial_SendFixed2((int32_t)AZ * 100 / 2048);
    Serial_SendString("g, GX=");
    Serial_SendFixed2((int32_t)GX * 100 / 164);
    Serial_SendString("dps, GY=");
    Serial_SendFixed2((int32_t)GY * 100 / 164);
    Serial_SendString("dps, GZ=");
    Serial_SendFixed2((int32_t)GZ * 100 / 164);
    Serial_SendString("dps\r\n");
}


