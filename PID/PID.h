#ifndef __PID_H
#define	__PID_H

#include "system.h"

/*MotorA_Position_pid*/
typedef struct
{
    float target_position;      //目标值
    float actual_position;      //实际值
    float err;             			//定义偏差值
    float err_last;          		//定义上一个偏差值
    float Kp,Ki,Kd;          		//定义比例、积分、微分系数
    float integral;          		//定义积分值
		int Position_OUTPUT;      //位置pid输出
} PPid;

/*Angle_pid*/
typedef struct
{
    float target_Angle;      //目标值
    float actual_Angle;      //实际值
    float err;             			//定义偏差值
    float err_last;          		//定义上一个偏差值
    float Kp,Ki,Kd;          		//定义比例、积分、微分系数
    float integral;          		//定义积分值
		int Angle_OUTPUT;      //位置pid输出
} APid;

extern PPid  PID;
extern APid	 Pid;
void PID_P_param_init(void);
int PositionPID_realize(float target_position, float actual_position);
void PID_Angle_param_init(void);
int AnglePID_realize(float target_Angle, float actual_Angle);

#endif
