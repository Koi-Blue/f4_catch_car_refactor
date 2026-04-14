#ifndef __ACTION_Y_H
#define __ACTION_Y_H

#include "stm32f4xx.h"                  // Device header
#include "take_action.h"

void Action_Y_PWM_Init(void);
void TIM2_IRQHandler(void);
void Move_Y(int step, uint32_t accel, uint32_t decel, uint32_t speed);
void speed_decision_Y(void);
void StepCounter_Y(signed char inc);
void DIR_Y(uint8_t a);

#endif
