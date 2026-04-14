#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "stm32f4xx.h"                  // Device header

#include "system.h"
#include "math.h"
#include "sys.h"
#include "delay.h"
#include "Timer.h"
#include "Servo.h"
#include "JY901B.h"
#include "usart.h"
#include "Move.h"
#include "Action_Y.h"
#include "Action_Z.h"
#include "Action_Turn_Z.h"
#include "Action.h"
#include "Task.h"
#include "Turntable.h"
#include "pid.h"
#include "Communication.h"

extern float  rcount;
extern float  yaw, Turn_Angle;
extern float Receive_Roll, Receive_Pitch, Receive_Yaw;
extern int  Turn_Step, stepPosition, stepPosition_Y, stepPosition_Z, stepPosition_Turn_Z;  //步数计数
extern int  duizheng_step_X, duizheng_step_Y;  //步数计数
extern int8_t QR_Code[6];
extern uint8_t WuKuai;
extern uint8_t SeHuan;
extern uint8_t 	map_flag;
extern uint8_t	Stop_flag;
extern uint8_t  distance_flag;
extern uint8_t  grab_flag;
extern uint8_t  grab_filish_flag;
extern uint8_t  place_flag;
extern uint8_t  place_filish_flag;
extern uint8_t  pile_flag;
extern uint8_t  pile_filish_flag;
extern uint8_t  Turntable_flag;
extern uint8_t  Turntable_filish_flag;
extern uint8_t 	Turntable_task_flag;
extern uint8_t 	Turntable_task_filish_flag;
extern uint8_t  task_flag;
extern uint8_t  task_filish_flag;
extern uint8_t  mission_flag;
extern uint8_t  mission_filish_flag;
extern uint8_t  finish_jiaozheng; //校正标志位
extern uint8_t  finish_duizheng; //对正标志位
extern uint8_t  stop_cnt;
extern int task_code1;
extern int task_code2;
extern uint8_t Angle_flag;
extern int  i;

void System_Init(void);

#endif
