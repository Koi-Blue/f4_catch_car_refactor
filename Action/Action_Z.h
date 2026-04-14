#ifndef __ACTION_Z_H
#define __ACTION_Z_H

#include "stm32f4xx.h"                  // Device header

void Action_Z_PWM_Init(void);
void TIM3_IRQHandler(void);
void Move_Z(int step, uint32_t accel, uint32_t decel, uint32_t speed);
void speed_decision_Z(void);
void StepCounter_Z(signed char inc);
void DIR_Z(uint8_t a);

#endif
