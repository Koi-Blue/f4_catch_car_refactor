#include "system.h"

void Turntable_1(void)
{
		static uint8_t Turntable_flag=1;
		switch (Turntable_flag)
		{
			case 1:
			{
				if (WuKuai == '1')
				{
					if (i >= 10)
					{
						i = 0;
						Turntable_flag = 2;
					}
				}
			}break;				
			case 2:
			{
				Move_Z(2800, 2500, 2500, 5000);
				if (stepPosition_Z == 2800)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;
					Turntable_flag = 3;
				}
			}break;			
			case 3:
			{	
				Servo_SetAngle3(18);
				if (i>100)
				{
					i = 0;
					Turntable_flag = 4;
				}				
			}break;
			case 4:
			{
				Move_Z(-2800, 2500, 2500, 5000);
				if (stepPosition_Z == -2800)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;					
					Turntable_flag = 5;
				}
			}break;
			case 5:
			{
				Servo_SetAngle4(6);     //车上置物台
				if (i>50)
				{
					i = 0;
					Turntable_flag = 6;
				}							
			}break;	
			case 6:
			{
				Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
				if (stepPosition_Y == -4780)
				{
					TIM_Cmd(TIM2, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_10);
					stepPosition_Y = 0;
					i = 0;				
					Turntable_flag = 7;
				}
			}break;			
			case 7:
			{
				Move_Turn_Z(2415, 50, 50, 800);
				if (stepPosition_Turn_Z == 2415)
				{
					TIM_Cmd(TIM4, DISABLE);
					GPIO_SetBits(GPIOD, GPIO_Pin_13);
					stepPosition_Turn_Z = 0;
					i = 0;	
					delay_ms(1000);
					Turntable_flag = 8;
				}				
			}break;							
			case 8:
			{
				Move_Z(2200, 2500, 2500, 5000);
				if (stepPosition_Z == 2200)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;					
					Turntable_flag = 9;
				}
			}break;				
			case 9:
			{
				Servo_SetAngle3(50);
				if (i>100)
				{
					i = 0;				
					Turntable_flag = 10;
				}
			}break;			
			case 10:
			{
				Move_Z(-2200, 2500, 2500, 5000);
				if (stepPosition_Z == -2200)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;					
					Turntable_flag = 11;
				}
			}break;	
			case 11:
			{
				Move_Y(4780, 2500, 2500, 5000);				//爪子Y回位
				if (stepPosition_Y == 4780)
				{
					TIM_Cmd(TIM2, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_10);
					stepPosition_Y = 0;
					i = 0;				
					Turntable_flag = 12;
				}
			}break;							
			case 12:
			{
				Move_Turn_Z(-2415, 50, 50, 800);
				if (stepPosition_Turn_Z == -2415)
				{
					TIM_Cmd(TIM4, DISABLE);
					GPIO_SetBits(GPIOD, GPIO_Pin_13);
					stepPosition_Turn_Z = 0;
					i = 0;		
					WuKuai = '0';						
					Turntable_filish_flag = 1;					
					Turntable_flag = 0;
				}				
			}break;				
		}
}

void Turntable_2(void)
{
		static uint8_t Turntable_flag=1;
		switch (Turntable_flag)
		{
			case 1:
			{
				if (WuKuai == '2')
				{
					if (i >= 10)
					{
						i = 0;
						Turntable_flag = 2;
					}
				}
			}break;				
			case 2:
			{
				Move_Z(2800, 2500, 2500, 5000);
				if (stepPosition_Z == 2800)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;
					Turntable_flag = 3;
				}
			}break;			
			case 3:
			{	
				Servo_SetAngle3(18);
				if (i>100)
				{
					i = 0;
					Turntable_flag = 4;
				}				
			}break;
			case 4:
			{
				Move_Z(-2800, 2500, 2500, 5000);
				if (stepPosition_Z == -2800)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;					
					Turntable_flag = 5;
				}
			}break;
			case 5:
			{
				Servo_SetAngle4(129);     //车上置物台
				if (i>50)
				{
					i = 0;
					Turntable_flag = 6;
				}							
			}break;		
			case 6:
			{
				Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
				if (stepPosition_Y == -4780)
				{
					TIM_Cmd(TIM2, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_10);
					stepPosition_Y = 0;
					i = 0;				
					Turntable_flag = 7;
				}
			}break;			
			case 7:
			{
				Move_Turn_Z(2415, 50, 50, 800);
				if (stepPosition_Turn_Z == 2415)
				{
					TIM_Cmd(TIM4, DISABLE);
					GPIO_SetBits(GPIOD, GPIO_Pin_13);
					stepPosition_Turn_Z = 0;
					i = 0;			
					delay_ms(1000);					
					Turntable_flag = 8;
				}				
			}break;										
			case 8:
			{
				Move_Z(2200, 2500, 2500, 5000);
				if (stepPosition_Z == 2200)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;					
					Turntable_flag = 9;
				}
			}break;				
			case 9:
			{
				Servo_SetAngle3(50);
				if (i>100)
				{
					i = 0;				
					Turntable_flag = 10;
				}
			}break;			
			case 10:
			{
				Move_Z(-2200, 2500, 2500, 5000);
				if (stepPosition_Z == -2200)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;					
					Turntable_flag = 11;
				}
			}break;	
			case 11:
			{
				Move_Y(4780, 2500, 2500, 5000);				//爪子Y回位
				if (stepPosition_Y == 4780)
				{
					TIM_Cmd(TIM2, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_10);
					stepPosition_Y = 0;
					i = 0;				
					Turntable_flag = 12;
				}
			}break;							
			case 12:
			{
				Move_Turn_Z(-2415, 50, 50, 800);
				if (stepPosition_Turn_Z == -2415)
				{
					TIM_Cmd(TIM4, DISABLE);
					GPIO_SetBits(GPIOD, GPIO_Pin_13);
					stepPosition_Turn_Z = 0;
					i = 0;		
					WuKuai = '0';						
					Turntable_filish_flag = 1;					
					Turntable_flag = 0;
				}				
			}break;				
		}
}

void Turntable_3(void)
{
		static uint8_t Turntable_flag=1;
		switch (Turntable_flag)
		{
			case 1:
			{
				if (WuKuai == '3')
				{
					if (i >= 10)
					{
						i = 0;
						Turntable_flag = 2;
					}
				}
			}break;				
			case 2:
			{
				Move_Z(2800, 2500, 2500, 5000);
				if (stepPosition_Z == 2800)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;
					Turntable_flag = 3;
				}
			}break;			
			case 3:
			{	
				Servo_SetAngle3(18);
				if (i>100)
				{
					i = 0;
					Turntable_flag = 4;
				}				
			}break;
			case 4:
			{
				Move_Z(-2800, 2500, 2500, 5000);
				if (stepPosition_Z == -2800)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;					
					Turntable_flag = 5;
				}
			}break;
			case 5:
			{
				Servo_SetAngle4(249);     //车上置物台
				if (i>50)
				{
					i = 0;
					Turntable_flag = 6;
				}							
			}break;				
			case 6:
			{
				Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
				if (stepPosition_Y == -4780)
				{
					TIM_Cmd(TIM2, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_10);
					stepPosition_Y = 0;
					i = 0;				
					Turntable_flag = 7;
				}
			}break;				
			case 7:
			{
				Move_Turn_Z(2415, 50, 50, 800);
				if (stepPosition_Turn_Z == 2415)
				{
					TIM_Cmd(TIM4, DISABLE);
					GPIO_SetBits(GPIOD, GPIO_Pin_13);
					stepPosition_Turn_Z = 0;
					i = 0;				
					delay_ms(1000);					
					Turntable_flag = 8;
				}				
			}break;								
			case 8:
			{
				Move_Z(2200, 2500, 2500, 5000);
				if (stepPosition_Z == 2200)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;					
					Turntable_flag = 9;
				}
			}break;				
			case 9:
			{
				Servo_SetAngle3(50);
				if (i>100)
				{
					i = 0;				
					Turntable_flag = 10;
				}
			}break;			
			case 10:
			{
				Move_Z(-2200, 2500, 2500, 5000);
				if (stepPosition_Z == -2200)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;					
					Turntable_flag = 11;
				}
			}break;
			case 11:
			{
				Move_Y(4780, 2500, 2500, 5000);				//爪子Y回位
				if (stepPosition_Y == 4780)
				{
					TIM_Cmd(TIM2, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_10);
					stepPosition_Y = 0;
					i = 0;				
					Turntable_flag = 12;
				}
			}break;							
			case 12:
			{
				Move_Turn_Z(-2415, 50, 50, 800);
				if (stepPosition_Turn_Z == -2415)
				{
					TIM_Cmd(TIM4, DISABLE);
					GPIO_SetBits(GPIOD, GPIO_Pin_13);
					stepPosition_Turn_Z = 0;
					i = 0;		
					WuKuai = '0';						
					Turntable_filish_flag = 1;					
					Turntable_flag = 0;
				}				
			}break;				
		}
}


void Turntable_123(void)
{
	static uint8_t Turntable_task_flag = 1;
	switch (Turntable_task_flag)
	{
		case 1:
		{
			Turntable_1();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 2;
			}
		}break;
		case 2:
		{
			Turntable_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);				
				Turntable_task_flag = 3;
			}
		}break;
		case 3:
		{
			Turntable_3();
			if (Turntable_filish_flag == 1)
			{
				Turntable_task_filish_flag = 1;
				Turntable_filish_flag = 0;
				Turntable_task_flag = 0;				
			}
		}break;
	}		
}

void Turntable_132(void)
{
	static uint8_t Turntable_task_flag = 1;
	switch (Turntable_task_flag)
	{
		case 1:
		{			
			Turntable_1();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 2;
			}
		}break;
		case 2:
		{
			Turntable_3();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 3;				
			}
		}break;	
		case 3:
		{		
			Turntable_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_task_filish_flag = 1;
				Turntable_filish_flag = 0;
				Turntable_task_flag = 0;				
			}
		}break;	
	}
}

void Turntable_213(void)
{
	static uint8_t Turntable_task_flag = 1;
	switch (Turntable_task_flag)
	{
		case 1:
		{			
			Turntable_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 2;
			}
		}break;
		case 2:
		{		
			Turntable_1();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 3;				
			}
		}break;	
		case 3:
		{		
			Turntable_3();
			if (Turntable_filish_flag == 1)
			{
				Turntable_task_filish_flag = 1;
				Turntable_filish_flag = 0;
				Turntable_task_flag = 0;				
			}
		}break;	
	}			
}

void Turntable_231(void)
{
	static uint8_t Turntable_task_flag = 1;
	switch (Turntable_task_flag)
	{
		case 1:
		{			
			Turntable_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 2;
			}
		}break;
		case 2:
		{		
			Turntable_3();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 3;				
			}
		}break;	
		case 3:
		{		
			Turntable_1();
			if (Turntable_filish_flag == 1)
			{
				Turntable_task_filish_flag = 1;
				Turntable_filish_flag = 0;
				Turntable_task_flag = 0;				
			}
		}break;	
	}	
}

void Turntable_312(void)
{
	static uint8_t Turntable_task_flag = 1;
	switch (Turntable_task_flag)
	{
		case 1:
		{			
			Turntable_3();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 2;
			}
		}break;
		case 2:
		{		
			Turntable_1();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 3;				
			}
		}break;	
		case 3:
		{		
			Turntable_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_task_filish_flag = 1;
				Turntable_filish_flag = 0;
				Turntable_task_flag = 0;				
			}
		}break;	
	}			
}

void Turntable_321(void)
{
	static uint8_t Turntable_task_flag = 1;
	switch (Turntable_task_flag)
	{
		case 1:
		{			
			Turntable_3();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 2;
			}
		}break;
		case 2:
		{		
			Turntable_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 3;				
			}
		}break;	
		case 3:
		{		
			Turntable_1();
			if (Turntable_filish_flag == 1)
			{
				Turntable_task_filish_flag = 1;
				Turntable_filish_flag = 0;
				Turntable_task_flag = 0;				
			}
		}break;	
	}	
}

void Turntable_1_2(void)
{
		static uint8_t Turntable_flag=1;
		switch (Turntable_flag)
		{
			case 1:
			{
				if (WuKuai == '1')
				{
					if (i >= 10)
					{
						i = 0;
						Turntable_flag = 2;
					}
				}
			}break;				
			case 2:
			{
				Move_Z(2800, 2500, 2500, 5000);
				if (stepPosition_Z == 2800)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;
					Turntable_flag = 3;
				}
			}break;			
			case 3:
			{	
				Servo_SetAngle3(18);
				if (i>100)
				{
					i = 0;
					Turntable_flag = 4;
				}				
			}break;
			case 4:
			{
				Move_Z(-2800, 2500, 2500, 5000);
				if (stepPosition_Z == -2800)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;					
					Turntable_flag = 5;
				}
			}break;
			case 5:
			{
				Servo_SetAngle4(6);     //车上置物台
				if (i>50)
				{
					i = 0;
					Turntable_flag = 6;
				}							
			}break;	
			case 6:
			{
				Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
				if (stepPosition_Y == -4780)
				{
					TIM_Cmd(TIM2, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_10);
					stepPosition_Y = 0;
					i = 0;				
					Turntable_flag = 7;
				}
			}break;			
			case 7:
			{
				Move_Turn_Z(2415, 50, 50, 800);
				if (stepPosition_Turn_Z == 2415)
				{
					TIM_Cmd(TIM4, DISABLE);
					GPIO_SetBits(GPIOD, GPIO_Pin_13);
					stepPosition_Turn_Z = 0;
					i = 0;	
					delay_ms(1000);
					Turntable_flag = 8;
				}				
			}break;							
			case 8:
			{
				Move_Z(2200, 2500, 2500, 5000);
				if (stepPosition_Z == 2200)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;					
					Turntable_flag = 9;
				}
			}break;				
			case 9:
			{
				Servo_SetAngle3(50);
				if (i>100)
				{
					i = 0;				
					Turntable_flag = 10;
				}
			}break;			
			case 10:
			{
				Move_Z(-2200, 2500, 2500, 5000);
				if (stepPosition_Z == -2200)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;					
					Turntable_flag = 11;
				}
			}break;	
			case 11:
			{
				Move_Y(4780, 2500, 2500, 5000);				//爪子Y回位
				if (stepPosition_Y == 4780)
				{
					TIM_Cmd(TIM2, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_10);
					stepPosition_Y = 0;
					i = 0;				
					Turntable_flag = 12;
				}
			}break;							
			case 12:
			{
				Move_Turn_Z(-2415, 50, 50, 800);
				if (stepPosition_Turn_Z == -2415)
				{
					TIM_Cmd(TIM4, DISABLE);
					GPIO_SetBits(GPIOD, GPIO_Pin_13);
					stepPosition_Turn_Z = 0;
					i = 0;		
					WuKuai = '0';						
					Turntable_filish_flag = 1;					
					Turntable_flag = 0;
				}				
			}break;				
		}
}

void Turntable_2_2(void)
{
		static uint8_t Turntable_flag=1;
		switch (Turntable_flag)
		{
			case 1:
			{
				if (WuKuai == '2')
				{
					if (i >= 10)
					{
						i = 0;
						Turntable_flag = 2;
					}
				}
			}break;				
			case 2:
			{
				Move_Z(2800, 2500, 2500, 5000);
				if (stepPosition_Z == 2800)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;
					Turntable_flag = 3;
				}
			}break;			
			case 3:
			{	
				Servo_SetAngle3(18);
				if (i>100)
				{
					i = 0;
					Turntable_flag = 4;
				}				
			}break;
			case 4:
			{
				Move_Z(-2800, 2500, 2500, 5000);
				if (stepPosition_Z == -2800)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;					
					Turntable_flag = 5;
				}
			}break;
			case 5:
			{
				Servo_SetAngle4(129);     //车上置物台
				if (i>50)
				{
					i = 0;
					Turntable_flag = 6;
				}							
			}break;		
			case 6:
			{
				Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
				if (stepPosition_Y == -4780)
				{
					TIM_Cmd(TIM2, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_10);
					stepPosition_Y = 0;
					i = 0;				
					Turntable_flag = 7;
				}
			}break;			
			case 7:
			{
				Move_Turn_Z(2415, 50, 50, 800);
				if (stepPosition_Turn_Z == 2415)
				{
					TIM_Cmd(TIM4, DISABLE);
					GPIO_SetBits(GPIOD, GPIO_Pin_13);
					stepPosition_Turn_Z = 0;
					i = 0;			
					delay_ms(1000);					
					Turntable_flag = 8;
				}				
			}break;										
			case 8:
			{
				Move_Z(2200, 2500, 2500, 5000);
				if (stepPosition_Z == 2200)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;					
					Turntable_flag = 9;
				}
			}break;				
			case 9:
			{
				Servo_SetAngle3(50);
				if (i>100)
				{
					i = 0;				
					Turntable_flag = 10;
				}
			}break;			
			case 10:
			{
				Move_Z(-2200, 2500, 2500, 5000);
				if (stepPosition_Z == -2200)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;					
					Turntable_flag = 11;
				}
			}break;	
			case 11:
			{
				Move_Y(4780, 2500, 2500, 5000);				//爪子Y回位
				if (stepPosition_Y == 4780)
				{
					TIM_Cmd(TIM2, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_10);
					stepPosition_Y = 0;
					i = 0;				
					Turntable_flag = 12;
				}
			}break;							
			case 12:
			{
				Move_Turn_Z(-2415, 50, 50, 800);
				if (stepPosition_Turn_Z == -2415)
				{
					TIM_Cmd(TIM4, DISABLE);
					GPIO_SetBits(GPIOD, GPIO_Pin_13);
					stepPosition_Turn_Z = 0;
					i = 0;		
					WuKuai = '0';						
					Turntable_filish_flag = 1;					
					Turntable_flag = 0;
				}				
			}break;				
		}
}

void Turntable_3_2(void)
{
		static uint8_t Turntable_flag=1;
		switch (Turntable_flag)
		{
			case 1:
			{
				if (WuKuai == '3')
				{
					if (i >= 10)
					{
						i = 0;
						Turntable_flag = 2;
					}
				}
			}break;				
			case 2:
			{
				Move_Z(2800, 2500, 2500, 5000);
				if (stepPosition_Z == 2800)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;
					Turntable_flag = 3;
				}
			}break;			
			case 3:
			{	
				Servo_SetAngle3(18);
				if (i>100)
				{
					i = 0;
					Turntable_flag = 4;
				}				
			}break;
			case 4:
			{
				Move_Z(-2800, 2500, 2500, 5000);
				if (stepPosition_Z == -2800)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;					
					Turntable_flag = 5;
				}
			}break;
			case 5:
			{
				Servo_SetAngle4(249);     //车上置物台
				if (i>50)
				{
					i = 0;
					Turntable_flag = 6;
				}							
			}break;				
			case 6:
			{
				Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
				if (stepPosition_Y == -4780)
				{
					TIM_Cmd(TIM2, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_10);
					stepPosition_Y = 0;
					i = 0;				
					Turntable_flag = 7;
				}
			}break;				
			case 7:
			{
				Move_Turn_Z(2415, 50, 50, 800);
				if (stepPosition_Turn_Z == 2415)
				{
					TIM_Cmd(TIM4, DISABLE);
					GPIO_SetBits(GPIOD, GPIO_Pin_13);
					stepPosition_Turn_Z = 0;
					i = 0;				
					delay_ms(1000);					
					Turntable_flag = 8;
				}				
			}break;								
			case 8:
			{
				Move_Z(2200, 2500, 2500, 5000);
				if (stepPosition_Z == 2200)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;					
					Turntable_flag = 9;
				}
			}break;				
			case 9:
			{
				Servo_SetAngle3(50);
				if (i>100)
				{
					i = 0;				
					Turntable_flag = 10;
				}
			}break;			
			case 10:
			{
				Move_Z(-2200, 2500, 2500, 5000);
				if (stepPosition_Z == -2200)
				{
					TIM_Cmd(TIM3, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_0);
					stepPosition_Z = 0;
					i = 0;					
					Turntable_flag = 11;
				}
			}break;
			case 11:
			{
				Move_Y(4780, 2500, 2500, 5000);				//爪子Y回位
				if (stepPosition_Y == 4780)
				{
					TIM_Cmd(TIM2, DISABLE);
					GPIO_SetBits(GPIOB, GPIO_Pin_10);
					stepPosition_Y = 0;
					i = 0;				
					Turntable_flag = 12;
				}
			}break;							
			case 12:
			{
				Move_Turn_Z(-2415, 50, 50, 800);
				if (stepPosition_Turn_Z == -2415)
				{
					TIM_Cmd(TIM4, DISABLE);
					GPIO_SetBits(GPIOD, GPIO_Pin_13);
					stepPosition_Turn_Z = 0;
					i = 0;		
					WuKuai = '0';						
					Turntable_filish_flag = 1;					
					Turntable_flag = 0;
				}				
			}break;				
		}
}


void Turntable_123_2(void)
{
	static uint8_t Turntable_task_flag = 1;
	switch (Turntable_task_flag)
	{
		case 1:
		{
			Turntable_1_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 2;
			}
		}break;
		case 2:
		{
			Turntable_2_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);				
				Turntable_task_flag = 3;
			}
		}break;
		case 3:
		{
			Turntable_3_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_task_filish_flag = 1;
				Turntable_filish_flag = 0;
				Turntable_task_flag = 0;				
			}
		}break;
	}		
}

void Turntable_132_2(void)
{
	static uint8_t Turntable_task_flag = 1;
	switch (Turntable_task_flag)
	{
		case 1:
		{			
			Turntable_1_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 2;
			}
		}break;
		case 2:
		{
			Turntable_3_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 3;				
			}
		}break;	
		case 3:
		{		
			Turntable_2_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_task_filish_flag = 1;
				Turntable_filish_flag = 0;
				Turntable_task_flag = 0;				
			}
		}break;	
	}
}

void Turntable_213_2(void)
{
	static uint8_t Turntable_task_flag = 1;
	switch (Turntable_task_flag)
	{
		case 1:
		{			
			Turntable_2_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 2;
			}
		}break;
		case 2:
		{		
			Turntable_1_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 3;				
			}
		}break;	
		case 3:
		{		
			Turntable_3_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_task_filish_flag = 1;
				Turntable_filish_flag = 0;
				Turntable_task_flag = 0;				
			}
		}break;	
	}			
}

void Turntable_231_2(void)
{
	static uint8_t Turntable_task_flag = 1;
	switch (Turntable_task_flag)
	{
		case 1:
		{			
			Turntable_2_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 2;
			}
		}break;
		case 2:
		{		
			Turntable_3_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 3;				
			}
		}break;	
		case 3:
		{		
			Turntable_1_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_task_filish_flag = 1;
				Turntable_filish_flag = 0;
				Turntable_task_flag = 0;				
			}
		}break;	
	}	
}

void Turntable_312_2(void)
{
	static uint8_t Turntable_task_flag = 1;
	switch (Turntable_task_flag)
	{
		case 1:
		{			
			Turntable_3_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 2;
			}
		}break;
		case 2:
		{		
			Turntable_1_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 3;				
			}
		}break;	
		case 3:
		{		
			Turntable_2_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_task_filish_flag = 1;
				Turntable_filish_flag = 0;
				Turntable_task_flag = 0;				
			}
		}break;	
	}			
}

void Turntable_321_2(void)
{
	static uint8_t Turntable_task_flag = 1;
	switch (Turntable_task_flag)
	{
		case 1:
		{			
			Turntable_3_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 2;
			}
		}break;
		case 2:
		{		
			Turntable_2_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_filish_flag = 0;
				delay_ms(500);
				Turntable_task_flag = 3;				
			}
		}break;	
		case 3:
		{		
			Turntable_1_2();
			if (Turntable_filish_flag == 1)
			{
				Turntable_task_filish_flag = 1;
				Turntable_filish_flag = 0;
				Turntable_task_flag = 0;				
			}
		}break;	
	}	
}

