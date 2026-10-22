#ifndef __DHT11_H
#define __DHT11_H

void DHT11_Init(void);
uint8_t DHT11_ReciveByte(void);
void DHT11_ReceiveData(uint8_t *DHT11_Temp, uint8_t *DHT11_Humid);


#endif
