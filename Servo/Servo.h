#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f4xx.h"  

void TIM9_PWM_Init(void);
void Servo_SetAngle1(float Angle);
void Servo_SetAngle2(float Angle);
void TIM10_PWM_Init(void);
void Servo_SetAngle3(float Angle);
void TIM11_PWM_Init(void);
void Servo_SetAngle4(float Angle);

#endif
