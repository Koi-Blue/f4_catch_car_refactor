#include "system.h"

#define Angle_OUTPUT_MAX 16700

//定义全局变量
PPid PID;
APid  Pid;


/**
  * @brief  位置式PID参数初始化
	*	@note 	角度环，外环
  * @retval 无
  */
void PID_Angle_param_init(void)
{
		/* 初始化参数 */
	  Pid.target_Angle = 0;				
    Pid.actual_Angle = 0.0;
    Pid.err = 0.0;
    Pid.err_last = 0.0;
    Pid.integral = 0.0;
		Pid.Angle_OUTPUT = 0;
		Pid.Kp = 50;
		Pid.Ki = 0;
		Pid.Kd = 10;
}


#define INTER_MAX  1000
float detime = 0.1;

/**************************************************************************
函数功能：位置式PID控制器，角度环，外环，
入口参数：目标角度 当前角度
返 回 值：速度控制值
根据位置式离散PID公式 
PID.Position_OUTPUT=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
PID.Position_OUTPUT代表输出
**************************************************************************/
int AnglePID_realize(float target_Angle, float actual_Angle)
{
		float error_deadzone=detime;//设置死区
	/*传入目标值*/
		Pid.target_Angle = target_Angle;
	/*传入目标值*/
		Pid.actual_Angle = actual_Angle;		
	/*计算目标值与实际值的误差*/
    Pid.err = Pid.target_Angle-Pid.actual_Angle;
	/*误差累积*/
    Pid.integral+=Pid.err;
			
    if(Pid.integral> INTER_MAX ) Pid.integral= INTER_MAX ;	//积分限幅 防止到达目标位置后过冲
	  if(Pid.integral<-INTER_MAX ) Pid.integral=-INTER_MAX ;	//积分限幅 防止到达目标位置后过冲
		if (fabsf(Pid.err) < error_deadzone) 
		{
			Pid.err = 0;
		}
	/*PID算法实现*/
    Pid.Angle_OUTPUT=Pid.Kp*Pid.err+Pid.Ki*Pid.integral+Pid.Kd*(Pid.err-Pid.err_last);
//	/*输出限幅*/	
		if(Pid.Angle_OUTPUT >  Angle_OUTPUT_MAX) Pid.Angle_OUTPUT = Angle_OUTPUT_MAX;
		if(Pid.Angle_OUTPUT < -Angle_OUTPUT_MAX) Pid.Angle_OUTPUT = -Angle_OUTPUT_MAX;
	/*误差传递*/
    Pid.err_last=Pid.err;
	/*返回当前实际值*/
    return Pid.Angle_OUTPUT;
}

/**
  * @brief  位置式PID参数初始化
	*	@note 	位置环，外环，MotorA
  * @retval 无
  */
void PID_P_param_init(void)
{
		/* 初始化参数 */
		PID.target_position = 0.0;				
    PID.actual_position = 0.0;
    PID.err = 0.0;
    PID.err_last = 0.0;
    PID.integral = 0.0;
		PID.Position_OUTPUT = 0;
		PID.Kp = 0.05;
		PID.Ki = 0;
		PID.Kd = 0.2;
}

/**************************************************************************
函数功能：位置式PID控制器
入口参数：目标圈数(位置) 当前位置
返 回 值：速度控制值
根据位置式离散PID公式 
PID.Position_OUTPUT=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
PID.Position_OUTPUT代表输出
**************************************************************************/
int PositionPID_realize(float target_position, float actual_position)
{
	/*传入目标值*/
		PID.target_position = target_position;
	/*传入目标值*/
		PID.actual_position = actual_position;		
	/*计算目标值与实际值的误差*/
    PID.err = PID.target_position-PID.actual_position;
	/*误差累积*/
    PID.integral+=PID.err;
		if (fabsf(PID.err) < 5) 
		{
			PID.err = 0;
		}
			
    if(PID.integral> 5400) PID.integral= 5400;	//积分限幅 防止到达目标位置后过冲
	  if(PID.integral<-5400) PID.integral=-5400;	//积分限幅 防止到达目标位置后过冲
	
	/*PID算法实现*/
    PID.Position_OUTPUT=PID.Kp*PID.err+PID.Ki*PID.integral+PID.Kd*(PID.err-PID.err_last);
	/*误差传递*/
    PID.err_last=PID.err;
	/*返回当前实际值*/
    return PID.Position_OUTPUT;
}

