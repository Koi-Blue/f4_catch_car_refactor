#ifndef __ACTION_TURN_Z_H
#define __ACTION_TURN_Z_H

#include "stm32f4xx.h"                  // Device header

void Action_Turn_Z_PWM_Init(void);
void TIM4_IRQHandler(void);
void Move_Turn_Z(int step, uint32_t accel, uint32_t decel, uint32_t speed);
void speed_decision_Turn_Z(void);
void StepCounter_Turn_Z(signed char inc);
void DIR_Turn_Z(uint8_t a);

#endif
