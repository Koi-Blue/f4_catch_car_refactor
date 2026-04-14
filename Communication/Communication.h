#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#include "system.h"

void USART1_Init(uint32_t bound);
uint8_t Serial_GetRxFlag(void);
void USART1_IRQHandler(void);

void USART3_Init(uint32_t bound);
uint8_t Serial_GetRxFlag3(void);
void USART3_IRQHandler(void);

void Serial_SendByte(uint8_t Byte);
void Serial_SendByte3(uint8_t Byte);

#endif
