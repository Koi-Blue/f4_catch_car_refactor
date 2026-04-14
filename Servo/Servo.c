#include "system.h"

void TIM9_PWM_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);/*使能定时器11时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);/*使能GPIOF时钟*/

	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9);/*复用*/
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9);/*复用*/

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOE,&GPIO_InitStructure);              //初始化PF9

	TIM_TimeBaseInitStructure.TIM_Period = 20000-1;/*自动重装载*/
	TIM_TimeBaseInitStructure.TIM_Prescaler = 168-1;/*预分频*/
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;/*时钟分频*/
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;/*向上计数*/
	TIM_TimeBaseInit(TIM9,&TIM_TimeBaseInitStructure);/*初始化*/

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;/*PWM模式*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;/*输出*/
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;/*比较极性高*/
	TIM_OC1Init(TIM9,&TIM_OCInitStructure);
	TIM_OC2Init(TIM9,&TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM9,TIM_OCPreload_Enable);/*输出比较预装载使能*/
	TIM_OC2PreloadConfig(TIM9,TIM_OCPreload_Enable);/*输出比较预装载使能*/

	TIM_ARRPreloadConfig(TIM9,ENABLE);/*自动重载预装载使能*/

	TIM_Cmd(TIM9,ENABLE);/*计数使能*/

}

void Servo_SetAngle1(float Angle)			//爪子
{
	TIM_SetCompare1(TIM9, Angle / 270 * 2000 + 500);
}

void Servo_SetAngle2(float Angle)			//车上置物台
{
	TIM_SetCompare2(TIM9, Angle / 270 * 2000 + 500);
}

void TIM10_PWM_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);/*使能定时器11时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);/*使能GPIOF时钟*/
	

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM10);/*复用*/

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;/*复用*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;/*推挽输出*/
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;/*PB8*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;/*上拉*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;/**/
	GPIO_Init(GPIOB, &GPIO_InitStructure);/*初始化IO*/

	TIM_TimeBaseInitStructure.TIM_Period = 20000-1;/*自动重装载*/
	TIM_TimeBaseInitStructure.TIM_Prescaler = 168-1;/*预分频*/
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;/*时钟分频*/
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;/*向上计数*/
	TIM_TimeBaseInit(TIM10, &TIM_TimeBaseInitStructure);/*初始化*/

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;/*PWM模式*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;/*输出*/
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;/*比较极性高*/
	TIM_OC1Init(TIM10, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);/*输出比较预装载使能*/

	TIM_CtrlPWMOutputs(TIM10, ENABLE);

	TIM_ARRPreloadConfig(TIM10, ENABLE);/*自动重载预装载使能*/

	TIM_Cmd(TIM10, ENABLE);/*计数使能*/

}


void Servo_SetAngle3(float Angle)			//云台
{
	TIM_SetCompare1(TIM10, Angle / 270 * 2000 + 500);
}

void TIM11_PWM_Init(void)
{

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);/*使能定时器11时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);/*使能GPIOF时钟*/
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM11);/*复用*/

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;/*复用*/
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;/*推挽输出*/
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;/*PB9*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;/*上拉*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;/**/
	GPIO_Init(GPIOB, &GPIO_InitStructure);/*初始化IO*/

	TIM_TimeBaseInitStructure.TIM_Period = 20000-1;/*自动重装载*/
	TIM_TimeBaseInitStructure.TIM_Prescaler = 168-1;/*预分频*/
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;/*时钟分频*/
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;/*向上计数*/
	TIM_TimeBaseInit(TIM11, &TIM_TimeBaseInitStructure);/*初始化*/

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;/*PWM模式*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;/*输出*/
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;/*比较极性高*/
	TIM_OC1Init(TIM11, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM11, TIM_OCPreload_Enable);/*输出比较预装载使能*/

	TIM_CtrlPWMOutputs(TIM11,ENABLE);

	TIM_ARRPreloadConfig(TIM11, ENABLE);/*自动重载预装载使能*/

	TIM_Cmd(TIM11, ENABLE);/*计数使能*/

}

void Servo_SetAngle4(float Angle)			//备用
{
	TIM_SetCompare1(TIM11, Angle / 270 * 2000 + 500);
}
