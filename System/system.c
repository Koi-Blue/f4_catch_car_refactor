#include "system.h"

void System_Init(void)
{
	delay_init(168);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	Move_PWM_Init();
	Action_Y_PWM_Init();
	Action_Z_PWM_Init();
	Action_Turn_Z_PWM_Init();
	USART2_Init();
	USART1_Init(115200);
	Timer7_Init(8400 - 1, 100 - 1);	
	TIM9_PWM_Init();
	TIM10_PWM_Init();
	TIM11_PWM_Init();
	uart_init2(115200);
	USART3_Init(115200);
}
