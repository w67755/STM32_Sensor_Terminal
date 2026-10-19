#ifndef __SERIAL_H
#define __SERIAL_H

void Serial_Init(void);
void Serial_SendString(char *String);
void Serial_SendByte(uint8_t Byte);
void Serial_SendFixed2(int32_t value);
void Serial_SendDataLine(int16_t AX, int16_t AY, int16_t AZ,
						int16_t GX, int16_t GY, int16_t GZ);

#endif
