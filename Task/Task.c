#include "system.h"

uint8_t Execute_flag = 0;
uint8_t Execute_X_flag = 0;
uint8_t Execute_Y_flag = 0;
int Error_X;
int Error_Y;

void Task_123(void)	//粗加工区
{
	static uint8_t task_flag=1;
	
	switch (task_flag)
	{
		case 1:
		{
			Move_Z(4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == 4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 30;
			}
		}break;
		case 30:
		{
			if (SeHuan == '2')
			{
				i = 0;				
				task_flag = 31;
			}		
		}break;		
		case 31:
		{
			Move_Z(-4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 2;
			}
		}break;
		case 2:
		{
			Move_Turn_Z(560, 50, 50, 800);  	//爪子从中心转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 3;
			}
		}break;
		case 3:
		{
			Place_1();														//放置红色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 4;
			}			
		}break;
		case 4:
		{
			Move_Turn_Z(-560, 50, 50, 800);  	//爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 5;
			}			
		}break;
		case 5:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回到绿色色环对应的位置
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;	
//				delay_ms(500);				
				task_flag = 6;
			}
		}break;		
		case 6:
		{
			Place_2();														//放置绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 7;
			}			
			}break;
		case 7:
		{
			Move_Turn_Z(-560, 50, 50, 800);  	//爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;		
//				delay_ms(500);								
				task_flag = 8;
			}		
		}break;
		case 8:
		{
			Place_3();														//放置蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
//				delay_ms(1000);
				task_flag = 9;
			}				
		}break;	
		case 9:
		{
			Move_Turn_Z(1120, 50, 50, 800);  	//爪子从蓝色转到红色对应的位置
			if (stepPosition_Turn_Z == 1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 10;
			}
		}break;	
		case 10:
		{
			Grab_1();															//抓红色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 11;
			}				
		}break;
		case 11:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子从红色转到绿色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;	
//				delay_ms(500);								
				task_flag = 12;
			}		
		}break;
		case 12:
		{
			Move_Y(4780, 2500, 2500, 5000);			//出去到蓝色色环对应位置
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;		
//				delay_ms(500);								
				task_flag = 13;
			}			
		}break;		
		case 13:
		{
			Grab_2();															//抓绿色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 14;
			}				
		}break;	
		case 14:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 15;
			}
		}break;	
		case 15:
		{
			Move_Y(-4780, 2500, 2500, 5000);			//出去到蓝色色环对应位置
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;		
//				delay_ms(500);								
				task_flag = 16;
			}			
		}break;
		case 16:
		{
			Grab_3();														//抓蓝色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 17;
			}				
		}break;
		case 17:
		{
			Move_Y(4780, 2500, 2500, 5000);			//出去到蓝色色环对应位置
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				task_flag = 18;
			}			
		}break;		
		case 18:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子回正
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;		
				SeHuan = '0';	
				task_filish_flag = 1;
				task_flag = 0;
			}
		}break;
	}
}

void Task_132(void)	//粗加工区
{
	static uint8_t task_flag=1;

	switch (task_flag)
	{
		case 1:
		{
			Move_Z(4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == 4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 30;
			}
		}break;
		case 30:
		{
			if (SeHuan == '2')
			{
				i = 0;				
				task_flag = 31;
			}		
		}break;		
		case 31:
		{
			Move_Z(-4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 2;
			}
		}break;
		case 2:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 3;
			}
		}break;	
		case 3:
		{
			Place_1();												//放红色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 4;
			}					
		}break;
		case 4:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				task_flag = 5;
			}
		}break;		
		case 5:
		{
			Move_Turn_Z(-1120, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;	
				delay_ms(500);								
				task_flag = 6;
			}				
		}break;			
		case 6:
		{
			Place_3();													//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 7;
			}					
		}break;
		case 7:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 8;
			}				
		}break;
		case 8:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;	
//				delay_ms(500);								
				task_flag = 9;
			}
		}break;		
		case 9:
		{
			Place_2();														//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;
//				delay_ms(1000);
				place_filish_flag = 0;
				task_flag = 10;
			}				
		}break;
		case 10:
		{
			Move_Turn_Z(560, 50, 50, 800);  	//爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 11;
			}
		}break;
		case 11:
		{
			Move_Y(-4780, 2500, 2500, 5000);  			//爪子回到红色色环对应的位置
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;		
//				delay_ms(500);								
				task_flag = 12;
			}
		}break;			
		case 12:
		{
			Grab_1();														 //抓红色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 13;
			}
		}break;	
		case 13:
		{
			Move_Turn_Z(-1120, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;			
//				delay_ms(500);								
				task_flag = 14;
			}
		}break;	
		case 14:
		{
			Grab_3();													//抓蓝色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 15;
			}				
		}break;	
		case 15:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 16;
			}
		}break;
		case 16:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				delay_ms(500);				
				task_flag = 17;
			}
		}break;		
		case 17:
		{
			Grab_2();													//抓绿色
			if (grab_filish_flag == 1)
			{
				i = 0;
				SeHuan = '0';
				grab_filish_flag = 0;
				task_filish_flag = 1;
				task_flag = 0;
			}					
		}break;	
	}	
}

void Task_213(void)	//粗加工区
{
	static uint8_t task_flag=1;

	switch (task_flag)
	{
		case 1:
		{
			Move_Z(4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == 4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 30;
			}
		}break;
		case 30:
		{
			if (SeHuan == '2')
			{
				i = 0;				
				task_flag = 31;
			}		
		}break;		
		case 31:
		{
			Move_Z(-4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 2;
			}
		}break;
		case 2:
		{
			Place_2();													//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 3;
			}				
		}break;
		case 3:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;			
//				delay_ms(500);								
				task_flag = 4;
			}
		}break;
		case 4:
		{
			Place_1();														//放红色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 5;
			}			
		}break;
		case 5:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				task_flag = 6;
			}
		}break;			
		case 6:
		{
			Move_Turn_Z(-1120, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;			
				delay_ms(500);								
				task_flag = 7;
			}
		}break;	
		case 7:
		{
			Place_3();														//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
//				delay_ms(1000);
				task_flag = 8;
			}				
		}break;
		case 8:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 9;
			}
		}break;	
		case 9:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;	
				delay_ms(500);				
				task_flag = 10;
			}
		}break;			
		case 10:
		{
			Grab_2();														//抓绿色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 11;
			}				
		}break;
		case 11:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 12;
			}
		}break;
		case 12:
		{
			Move_Y(-4780, 2500, 2500, 5000);			//出去到红色
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				delay_ms(500);				
				task_flag = 13;
			}					
		}break;
		case 13:
		{
			Grab_1();												//抓红色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 14;
			}			
		}break;
		case 14:
		{
			Move_Turn_Z(-1120, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				delay_ms(500);				
				task_flag = 15;
			}
		}break;
		case 15:
		{
			Grab_3();														//抓蓝色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 16;
			}			
		}break;
		case 16:
		{
			Move_Y(4780, 2500, 2500, 5000);				//出去到蓝色
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				task_flag = 17;
			}					
		}break;		
		case 17:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				SeHuan = '0';
				task_filish_flag = 1;
				task_flag = 0;			
			}					
		}break;
	}
}

void Task_231(void)	//粗加工区
{
	static uint8_t task_flag=1;

	switch (task_flag)
	{
		case 1:
		{
			Move_Z(4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == 4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 30;
			}
		}break;
		case 30:
		{
			if (SeHuan == '2')
			{
				i = 0;				
				task_flag = 31;
			}		
		}break;		
		case 31:
		{
			Move_Z(-4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 2;
			}
		}break;
		case 2:
		{
			Place_2();													//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 3;
			}				
		}break;
		case 3:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;			
				delay_ms(500);								
				task_flag = 4;			
			}
		}break;
		case 4:
		{
			Place_3();													//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 5;
			}				
		}break;
		case 5:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				task_flag = 6;
			}
		}break;			
		case 6:
		{
			Move_Turn_Z(1120, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
//				delay_ms(500);				
				task_flag = 7;			
			}
		}break;		
		case 7:
		{
			Place_1();													//放红色						
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
//				delay_ms(1000);
				task_flag = 8;
			}				
		}break;
		case 8:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;		
				task_flag = 9;
			}
		}break;		
		case 9:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
//				delay_ms(500);				
				task_flag = 10;			
			}
		}break;			
		case 10:
		{
			Grab_2();														//抓绿色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 11;
			}					
		}break;
		case 11:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 12;			
			}
		}break;
		case 12:
		{
			Move_Y(-4780, 2500, 2500, 5000);			 //出去到蓝色位置
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
//				delay_ms(500);				
				task_flag = 13;
			}				
		}break;
		case 13:
		{
			Grab_3();														//抓蓝色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 14;
			}					
		}break;
		case 14:
		{
			Move_Turn_Z(1120, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
//				delay_ms(500);				
				task_flag = 15;			
			}
		}break;
		case 15:
		{
			Grab_1();														//抓红色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 16;
			}					
		}break;
		case 16:
		{
			Move_Y(4780, 2500, 2500, 5000);				//出去到红色
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				task_flag = 17;
			}				
		}break;		
		case 17:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				SeHuan = '0';
				task_filish_flag = 1;
				task_flag = 0;			
			}				
		}break;
	}	
}

void Task_312(void)	//粗加工区
{
	static uint8_t task_flag=1;

	switch (task_flag)
	{
		case 1:
		{
			Move_Z(4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == 4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 30;
			}
		}break;
		case 30:
		{
			if (SeHuan == '2')
			{
				i = 0;				
				task_flag = 31;
			}		
		}break;		
		case 31:
		{
			Move_Z(-4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 2;
			}
		}break;
		case 2:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
//				delay_ms(500);				
				task_flag = 3;			
			}
		}break;
		case 3:
		{
			Place_3();													//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 4;
			}					
		}break;
		case 4:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				task_flag = 5;
			}
		}break;		
		case 5:
		{
			Move_Turn_Z(1120, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == 1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
//				delay_ms(500);				
				task_flag = 6;			
			}
		}break;		
		case 6:
		{
			Place_1();													//放红色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
//				delay_ms(1000);
				task_flag = 7;
			}	
		}break;
		case 7:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 8;			
			}
		}break;
		case 8:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
//				delay_ms(500);				
				task_flag = 9;
			}
		}break;			
		case 9:
		{
			Place_2();													//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 10;
			}					
		}break;	
		case 10:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 11;			
			}
		}break;
		case 11:
		{
			Move_Y(-4780, 2500, 2500, 5000);  			//爪子出去的蓝色
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
//				delay_ms(500);				
				task_flag = 12;
			}
		}break;		
		case 12:
		{
			Grab_3();															//抓蓝色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 13;
			}					
		}break;
		case 13:
		{
			Move_Turn_Z(1120, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				delay_ms(500);				
				task_flag = 14;			
			}
		}break;
		case 14:
		{
			Grab_1();															//抓红色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 15;
			}					
		}break;
		case 15:
		{
			Move_Turn_Z(-560, 50, 50, 800);  		//爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 16;			
			}
		}break;
		case 16:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				delay_ms(500);				
				task_flag = 17;
			}
		}break;		
		case 17:
		{
			Grab_2();																//抓绿色
			if (grab_filish_flag == 1)
			{
				i = 0;
				SeHuan = '0';
				grab_filish_flag = 0;					
				task_filish_flag = 1;
				task_flag = 0;
			}					
		}break;
	}
}

void Task_321(void)	//粗加工区
{
	static uint8_t task_flag=1;

	switch (task_flag)
	{
		case 1:
		{
			Move_Z(4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == 4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 30;
			}
		}break;
		case 30:
		{
			if (SeHuan == '2')
			{
				i = 0;				
				task_flag = 31;
			}		
		}break;		
		case 31:
		{
			Move_Z(-4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 2;
			}
		}break;
		case 2:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 3;			
			}
		}break;
		case 3:
		{
			Place_3();														//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 4;
			}				
		}break;
		case 4:
		{
			Move_Turn_Z(560, 50, 50, 800);  		//爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 5;			
			}
		}break;
		case 5:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
//				delay_ms(500);				
				task_flag = 6;
			}
		}break;		
		case 6:
		{
			Place_2();															//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 7;
			}			
		}break;
		case 7:
		{
			Move_Turn_Z(560, 50, 50, 800); 	 //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
//				delay_ms(500);				
				task_flag = 8;			
			}
		}break;
		case 8:
		{
			Place_1();														//放红色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
//				delay_ms(1000);
				task_flag = 9;
			}			
		}break;
		case 9:
		{
			Move_Turn_Z(-1120, 50, 50, 800); 	 //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 10;			
			}
		}break;
		case 10:
		{
			Grab_3();															//抓蓝色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 11;
			}					
		}break;
		case 11:
		{
			Move_Turn_Z(560, 50, 50, 800);  		//爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 12;			
			}
		}break;
		case 12:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;			
//				delay_ms(500);				
				task_flag = 13;
			}
		}break;		
		case 13:
		{
			Grab_2();															//抓绿色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 14;
			}					
		}break;
		case 14:
		{
			Move_Turn_Z(560, 50, 50, 800);  		//爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)	
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 15;			
			}
		}break;
		case 15:
		{
			Move_Y(-4780, 2500, 2500, 5000);					//出去到红色
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
//				delay_ms(500);				
				task_flag = 16;
			}			
		}break;
		case 16:
		{
			Grab_1();															//抓红色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 17;
			}					
		}break;
		case 17:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				task_flag = 18;
			}
		}break;		
		case 18:
		{
			Move_Turn_Z(-560, 50, 50, 800); 	 //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				SeHuan = '0';
				task_filish_flag = 1;
				task_flag = 0;			
			}
		}break;
	}	
}


void Task_123_2(void)	//粗加工区
{
	static uint8_t task_flag=1;
	
	switch (task_flag)
	{
		case 1:
		{
			Move_Z(4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == 4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 30;
			}
		}break;
		case 30:
		{
			if (SeHuan == '2')
			{
				i = 0;				
				task_flag = 31;
			}		
		}break;		
		case 31:
		{
			Move_Z(-4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 2;
			}
		}break;
		case 2:
		{
			Move_Turn_Z(560, 50, 50, 800);  	//爪子从中心转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 3;
			}
		}break;
		case 3:
		{
			Place_13();														//放置红色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 4;
			}			
		}break;
		case 4:
		{
			Move_Turn_Z(-560, 50, 50, 800);  	//爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 5;
			}			
		}break;
		case 5:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回到绿色色环对应的位置
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;	
//				delay_ms(500);				
				task_flag = 6;
			}
		}break;		
		case 6:
		{
			Place_23();														//放置绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 7;
			}			
			}break;
		case 7:
		{
			Move_Turn_Z(-560, 50, 50, 800);  	//爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;		
//				delay_ms(500);								
				task_flag = 8;
			}		
		}break;
		case 8:
		{
			Place_32();														//放置蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
//				delay_ms(1000);
				task_flag = 9;
			}				
		}break;	
		case 9:
		{
			Move_Turn_Z(1120, 50, 50, 800);  	//爪子从蓝色转到红色对应的位置
			if (stepPosition_Turn_Z == 1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 10;
			}
		}break;	
		case 10:
		{
			Grab_11();															//抓红色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 11;
			}				
		}break;
		case 11:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子从红色转到绿色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;	
//				delay_ms(500);								
				task_flag = 12;
			}		
		}break;
		case 12:
		{
			Move_Y(4780, 2500, 2500, 5000);			//出去到蓝色色环对应位置
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;		
//				delay_ms(500);								
				task_flag = 13;
			}			
		}break;		
		case 13:
		{
			Grab_22();															//抓绿色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 14;
			}				
		}break;	
		case 14:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 15;
			}
		}break;	
		case 15:
		{
			Move_Y(-4780, 2500, 2500, 5000);			//出去到蓝色色环对应位置
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;		
//				delay_ms(500);								
				task_flag = 16;
			}			
		}break;
		case 16:
		{
			Grab_33();														//抓蓝色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 17;
			}				
		}break;
		case 17:
		{
			Move_Y(4780, 2500, 2500, 5000);			//出去到蓝色色环对应位置
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				task_flag = 18;
			}			
		}break;		
		case 18:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子回正
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;		
				SeHuan = '0';	
				task_filish_flag = 1;
				task_flag = 0;
			}
		}break;
	}
}

void Task_132_2(void)	//粗加工区
{
	static uint8_t task_flag=1;

	switch (task_flag)
	{
		case 1:
		{
			Move_Z(4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == 4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 30;
			}
		}break;
		case 30:
		{
			if (SeHuan == '2')
			{
				i = 0;				
				task_flag = 31;
			}		
		}break;		
		case 31:
		{
			Move_Z(-4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 2;
			}
		}break;
		case 2:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 3;
			}
		}break;	
		case 3:
		{
			Place_13();												//放红色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 4;
			}					
		}break;
		case 4:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				task_flag = 5;
			}
		}break;		
		case 5:
		{
			Move_Turn_Z(-1120, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;	
				delay_ms(500);								
				task_flag = 6;
			}				
		}break;			
		case 6:
		{
			Place_32();													//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 7;
			}					
		}break;
		case 7:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 8;
			}				
		}break;
		case 8:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;	
//				delay_ms(500);								
				task_flag = 9;
			}
		}break;		
		case 9:
		{
			Place_23();														//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;
//				delay_ms(1000);
				place_filish_flag = 0;
				task_flag = 10;
			}				
		}break;
		case 10:
		{
			Move_Turn_Z(560, 50, 50, 800);  	//爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 11;
			}
		}break;
		case 11:
		{
			Move_Y(-4780, 2500, 2500, 5000);  			//爪子回到红色色环对应的位置
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;		
//				delay_ms(500);								
				task_flag = 12;
			}
		}break;			
		case 12:
		{
			Grab_11();														 //抓红色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 13;
			}
		}break;	
		case 13:
		{
			Move_Turn_Z(-1120, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;			
//				delay_ms(500);								
				task_flag = 14;
			}
		}break;	
		case 14:
		{
			Grab_33();													//抓蓝色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 15;
			}				
		}break;	
		case 15:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 16;
			}
		}break;
		case 16:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				delay_ms(500);				
				task_flag = 17;
			}
		}break;		
		case 17:
		{
			Grab_22();													//抓绿色
			if (grab_filish_flag == 1)
			{
				i = 0;
				SeHuan = '0';
				grab_filish_flag = 0;
				task_filish_flag = 1;
				task_flag = 0;
			}					
		}break;	
	}	
}

void Task_213_2(void)	//粗加工区
{
	static uint8_t task_flag=1;

	switch (task_flag)
	{
		case 1:
		{
			Move_Z(4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == 4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 30;
			}
		}break;
		case 30:
		{
			if (SeHuan == '2')
			{
				i = 0;				
				task_flag = 31;
			}		
		}break;		
		case 31:
		{
			Move_Z(-4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 2;
			}
		}break;
		case 2:
		{
			Place_23();													//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 3;
			}				
		}break;
		case 3:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;			
//				delay_ms(500);								
				task_flag = 4;
			}
		}break;
		case 4:
		{
			Place_13();														//放红色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 5;
			}			
		}break;
		case 5:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				task_flag = 6;
			}
		}break;			
		case 6:
		{
			Move_Turn_Z(-1120, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;			
				delay_ms(500);								
				task_flag = 7;
			}
		}break;	
		case 7:
		{
			Place_32();														//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
//				delay_ms(1000);
				task_flag = 8;
			}				
		}break;
		case 8:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 9;
			}
		}break;	
		case 9:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;	
				delay_ms(500);				
				task_flag = 10;
			}
		}break;			
		case 10:
		{
			Grab_22();														//抓绿色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 11;
			}				
		}break;
		case 11:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 12;
			}
		}break;
		case 12:
		{
			Move_Y(-4780, 2500, 2500, 5000);			//出去到红色
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				delay_ms(500);				
				task_flag = 13;
			}					
		}break;
		case 13:
		{
			Grab_11();												//抓红色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 14;
			}			
		}break;
		case 14:
		{
			Move_Turn_Z(-1120, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				delay_ms(500);				
				task_flag = 15;
			}
		}break;
		case 15:
		{
			Grab_33();														//抓蓝色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 16;
			}			
		}break;
		case 16:
		{
			Move_Y(4780, 2500, 2500, 5000);				//出去到蓝色
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				task_flag = 17;
			}					
		}break;		
		case 17:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				SeHuan = '0';
				task_filish_flag = 1;
				task_flag = 0;			
			}					
		}break;
	}
}

void Task_231_2(void)	//粗加工区
{
	static uint8_t task_flag=1;

	switch (task_flag)
	{
		case 1:
		{
			Move_Z(4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == 4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 30;
			}
		}break;
		case 30:
		{
			if (SeHuan == '2')
			{
				i = 0;				
				task_flag = 31;
			}		
		}break;		
		case 31:
		{
			Move_Z(-4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 2;
			}
		}break;
		case 2:
		{
			Place_23();													//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 3;
			}				
		}break;
		case 3:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;			
				delay_ms(500);								
				task_flag = 4;			
			}
		}break;
		case 4:
		{
			Place_32();													//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 5;
			}				
		}break;
		case 5:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				task_flag = 6;
			}
		}break;			
		case 6:
		{
			Move_Turn_Z(1120, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
//				delay_ms(500);				
				task_flag = 7;			
			}
		}break;		
		case 7:
		{
			Place_13();													//放红色						
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
//				delay_ms(1000);
				task_flag = 8;
			}				
		}break;
		case 8:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;		
				task_flag = 9;
			}
		}break;		
		case 9:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
//				delay_ms(500);				
				task_flag = 10;			
			}
		}break;			
		case 10:
		{
			Grab_22();														//抓绿色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 11;
			}					
		}break;
		case 11:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 12;			
			}
		}break;
		case 12:
		{
			Move_Y(-4780, 2500, 2500, 5000);			 //出去到蓝色位置
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
//				delay_ms(500);				
				task_flag = 13;
			}				
		}break;
		case 13:
		{
			Grab_33();														//抓蓝色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 14;
			}					
		}break;
		case 14:
		{
			Move_Turn_Z(1120, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
//				delay_ms(500);				
				task_flag = 15;			
			}
		}break;
		case 15:
		{
			Grab_11();														//抓红色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 16;
			}					
		}break;
		case 16:
		{
			Move_Y(4780, 2500, 2500, 5000);				//出去到红色
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				task_flag = 17;
			}				
		}break;		
		case 17:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				SeHuan = '0';
				task_filish_flag = 1;
				task_flag = 0;			
			}				
		}break;
	}	
}

void Task_312_2(void)	//粗加工区
{
	static uint8_t task_flag=1;

	switch (task_flag)
	{
		case 1:
		{
			Move_Z(4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == 4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 30;
			}
		}break;
		case 30:
		{
			if (SeHuan == '2')
			{
				i = 0;				
				task_flag = 31;
			}		
		}break;		
		case 31:
		{
			Move_Z(-4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 2;
			}
		}break;
		case 2:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
//				delay_ms(500);				
				task_flag = 3;			
			}
		}break;
		case 3:
		{
			Place_32();													//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 4;
			}					
		}break;
		case 4:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				task_flag = 5;
			}
		}break;		
		case 5:
		{
			Move_Turn_Z(1120, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == 1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
//				delay_ms(500);				
				task_flag = 6;			
			}
		}break;		
		case 6:
		{
			Place_13();													//放红色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
//				delay_ms(1000);
				task_flag = 7;
			}	
		}break;
		case 7:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 8;			
			}
		}break;
		case 8:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
//				delay_ms(500);				
				task_flag = 9;
			}
		}break;			
		case 9:
		{
			Place_23();													//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 10;
			}					
		}break;	
		case 10:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 11;			
			}
		}break;
		case 11:
		{
			Move_Y(-4780, 2500, 2500, 5000);  			//爪子出去的蓝色
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
//				delay_ms(500);				
				task_flag = 12;
			}
		}break;		
		case 12:
		{
			Grab_33();															//抓蓝色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 13;
			}					
		}break;
		case 13:
		{
			Move_Turn_Z(1120, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				delay_ms(500);				
				task_flag = 14;			
			}
		}break;
		case 14:
		{
			Grab_11();															//抓红色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 15;
			}					
		}break;
		case 15:
		{
			Move_Turn_Z(-560, 50, 50, 800);  		//爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 16;			
			}
		}break;
		case 16:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				delay_ms(500);				
				task_flag = 17;
			}
		}break;		
		case 17:
		{
			Grab_22();																//抓绿色
			if (grab_filish_flag == 1)
			{
				i = 0;
				SeHuan = '0';
				grab_filish_flag = 0;					
				task_filish_flag = 1;
				task_flag = 0;
			}					
		}break;
	}
}

void Task_321_2(void)	//粗加工区
{
	static uint8_t task_flag=1;

	switch (task_flag)
	{
		case 1:
		{
			Move_Z(4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == 4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 30;
			}
		}break;
		case 30:
		{
			if (SeHuan == '2')
			{
				i = 0;				
				task_flag = 31;
			}		
		}break;		
		case 31:
		{
			Move_Z(-4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				task_flag = 2;
			}
		}break;
		case 2:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 3;			
			}
		}break;
		case 3:
		{
			Place_32();														//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 4;
			}				
		}break;
		case 4:
		{
			Move_Turn_Z(560, 50, 50, 800);  		//爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 5;			
			}
		}break;
		case 5:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
//				delay_ms(500);				
				task_flag = 6;
			}
		}break;		
		case 6:
		{
			Place_23();															//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				task_flag = 7;
			}			
		}break;
		case 7:
		{
			Move_Turn_Z(560, 50, 50, 800); 	 //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
//				delay_ms(500);				
				task_flag = 8;			
			}
		}break;
		case 8:
		{
			Place_13();														//放红色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
//				delay_ms(1000);
				task_flag = 9;
			}			
		}break;
		case 9:
		{
			Move_Turn_Z(-1120, 50, 50, 800); 	 //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 10;			
			}
		}break;
		case 10:
		{
			Grab_33();															//抓蓝色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 11;
			}					
		}break;
		case 11:
		{
			Move_Turn_Z(560, 50, 50, 800);  		//爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 12;			
			}
		}break;
		case 12:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;			
//				delay_ms(500);				
				task_flag = 13;
			}
		}break;		
		case 13:
		{
			Grab_22();															//抓绿色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 14;
			}					
		}break;
		case 14:
		{
			Move_Turn_Z(560, 50, 50, 800);  		//爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)	
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				task_flag = 15;			
			}
		}break;
		case 15:
		{
			Move_Y(-4780, 2500, 2500, 5000);					//出去到红色
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
//				delay_ms(500);				
				task_flag = 16;
			}			
		}break;
		case 16:
		{
			Grab_11();															//抓红色
			if (grab_filish_flag == 1)
			{
				i = 0;
				grab_filish_flag = 0;
				task_flag = 17;
			}					
		}break;
		case 17:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				task_flag = 18;
			}
		}break;		
		case 18:
		{
			Move_Turn_Z(-560, 50, 50, 800); 	 //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				SeHuan = '0';
				task_filish_flag = 1;
				task_flag = 0;			
			}
		}break;
	}	
}

void Mission_123(void)	//暂存区一层
{
	static uint8_t mission_flag=1;

	switch (mission_flag)
	{
		case 1:
		{
			Move_Z(4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == 4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				mission_flag = 30;
			}
		}break;
		case 30:
		{
			if (SeHuan == '2')
			{
				i = 0;				
				mission_flag = 31;
			}		
		}break;
		case 31:
		{
			Move_Z(-4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				mission_flag = 2;
			}
		}break;
		case 2:
		{
			Move_Turn_Z(560, 50, 50, 800);  	//爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				mission_flag = 3;			
			}		
		}break;
		case 3:
		{
			Place_11();														//放置红色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				mission_flag = 4;
			}
		}break;
		case 4:
		{
			Move_Turn_Z(-560, 50, 50, 800);  	//爪子转到绿色色环对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				mission_flag = 5;			
			}	
		}break;
		case 5:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回到绿色色环对应的位置
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
//				delay_ms(500);				
				mission_flag = 6;
			}
		}break;		
		case 6:
		{
			Place_22();														//放置绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				mission_flag = 7;
			}			
		}break;
		case 7:
		{
			Move_Turn_Z(-560, 50, 50, 800);  		//爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
//				i = 0;					
				delay_ms(500);				
				mission_flag = 8;			
			}				
		}break;
		case 8:
		{
			Place_33();														//放置蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				mission_flag = 9;
			}			
		}break;	
		case 9:
		{
			Move_Turn_Z(560, 50, 50, 800);  		//爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)	
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 10;
			}						
		}break;
		case 10:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回到绿色色环对应的位置
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;
				SeHuan = '0';		
				mission_filish_flag = 1;
				mission_flag = 0;
			}
		}break;		
	}
}

void Mission_132(void)	//暂存区一层
{
	static uint8_t mission_flag=1;

	switch (mission_flag)
	{
		case 1:
		{
			Move_Z(4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == 4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				mission_flag = 30;
			}
		}break;
		case 30:
		{
			if (SeHuan == '2')
			{
				i = 0;				
				mission_flag = 31;
			}		
		}break;
		case 31:
		{
			Move_Z(-4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				mission_flag = 2;
			}
		}break;
		case 2:
		{	
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 3;
			}		
		}break;
		case 3:
		{
			Place_11();													//放红色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				mission_flag = 4;
			}
		}break;
		case 4:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				mission_flag = 5;
			}
		}break;		
		case 5:
		{				
			Move_Turn_Z(-1120, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;				
//				delay_ms(500);								
				mission_flag = 6;
			}	
		}break;		
		case 6:
		{		
			Place_33();													//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				mission_flag = 7;
			}
		}break;
		case 7:
		{				
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 8;
			}	
		}break;
		case 8:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
//				delay_ms(500);				
				mission_flag = 9;
			}
		}break;		
		case 9:
		{		
			Place_22();													//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				SeHuan = '0';
				mission_filish_flag = 1;
				mission_flag = 0;
			}
		}break;				
	}
}

void Mission_213(void)	//暂存区一层
{
	static uint8_t mission_flag=1;

	switch (mission_flag)
	{
		case 1:
		{
			Move_Z(4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == 4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				mission_flag = 30;
			}
		}break;
		case 30:
		{
			if (SeHuan == '2')
			{
				i = 0;				
				mission_flag = 31;
			}		
		}break;
		case 31:
		{
			Move_Z(-4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				mission_flag = 2;
			}
		}break;
		case 2:
		{	
			Place_22();													//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				mission_flag = 3;
			}
		}break;	
		case 3:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
//				delay_ms(500);				
				mission_flag = 4;
			}					
		}break;
		case 4:
		{
			Place_11();													//放红色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				mission_flag = 5;
			}
		}break;	
		case 5:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				mission_flag = 6;
			}
		}break;			
		case 6:
		{
			Move_Turn_Z(-1120, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
//				delay_ms(500);				
				mission_flag = 7;
			}					
		}break;	
		case 7:
		{
			Place_33();													//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				mission_flag = 8;
			}
		}break;
		case 8:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 9;
			}					
		}break;
		case 9:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;	
				SeHuan = '0';			
				mission_filish_flag = 1;
				mission_flag = 0;
			}
		}break;		
	}
}

void Mission_231(void)	//暂存区一层
{
	static uint8_t mission_flag=1;

	switch (mission_flag)
	{
		case 1:
		{
			Move_Z(4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == 4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				mission_flag = 30;
			}
		}break;
		case 30:
		{
			if (SeHuan == '2')
			{
				i = 0;				
				mission_flag = 31;
			}		
		}break;
		case 31:
		{
			Move_Z(-4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				mission_flag = 2;
			}
		}break;
		case 2:
		{	
			Place_22();													//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				mission_flag = 3;
			}
		}break;	
		case 3:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
//				delay_ms(500);				
				mission_flag = 4;
			}				
		}break;
		case 4:
		{
			Place_33();													//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				mission_flag = 5;
			}
		}break;	
		case 5:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				mission_flag = 6;
			}
		}break;			
		case 6:
		{
			Move_Turn_Z(1120, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
//				delay_ms(500);				
				mission_flag = 7;
			}					
		}break;	
		case 7:
		{
			Place_11();													//放红色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				mission_flag = 8;
			}
			}break;
		case 8:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 9;
			}				
		}break;
		case 9:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;		
				SeHuan = '0';				
				mission_filish_flag = 1;
				mission_flag = 0;
			}
		}break;		
	}
}

void Mission_312(void)	//暂存区一层
{
	static uint8_t mission_flag=1;

	switch (mission_flag)
	{
		case 1:
		{
			Move_Z(4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == 4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				mission_flag = 30;
			}
		}break;
		case 30:
		{
			if (SeHuan == '2')
			{
				i = 0;				
				mission_flag = 31;
			}		
		}break;
		case 31:
		{
			Move_Z(-4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				mission_flag = 2;
			}
		}break;
		case 2:
		{		
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 3;
			}						
		}break;
		case 3:
		{
			Place_33();													//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				mission_flag = 4;
			}
		}break;	
		case 4:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				mission_flag = 5;
			}
		}break;		
		case 5:
		{
			Move_Turn_Z(1120, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == 1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
//				delay_ms(500);				
				mission_flag = 6;
			}							
		}break;		
		case 6:
		{
			Place_11();													//放红色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				mission_flag = 7;
			}
		}break;
		case 7:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 8;
			}
		}break;
		case 8:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
//				delay_ms(500);							
				mission_flag = 9;
			}
		}break;		
		case 9:
		{
			Place_22();														//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				place_filish_flag = 0;
				SeHuan = '0';			
				mission_filish_flag = 1;
				mission_flag = 0;
			}
		}break;				
	}
}

void Mission_321(void)	//暂存区一层
{
	static uint8_t mission_flag=1;

	switch (mission_flag)
	{
		case 1:
		{
			Move_Z(4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == 4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				mission_flag = 30;
			}
		}break;
		case 30:
		{
			if (SeHuan == '2')
			{
				i = 0;				
				mission_flag = 31;
			}		
		}break;
		case 31:
		{
			Move_Z(-4800, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -4800)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				mission_flag = 2;
			}
		}break;
		case 2:
		{	
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 3;
			}	
		}break;
		case 3:
		{
			Place_33();													//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;		
				place_filish_flag = 0;
				mission_flag = 4;
			}
		}break;
		case 4:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 5;
			}
		}break;
		case 5:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;
//				delay_ms(500);								
				mission_flag = 6;
			}
		}break;		
		case 6:
		{
			Place_22();													//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;		
				place_filish_flag = 0;
				mission_flag = 7;
			}
		}break;	
		case 7:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;				
//				delay_ms(500);								
				mission_flag = 8;
			}	
		}break;
		case 8:
		{
			Place_11();													//放红色
			if (place_filish_flag == 1)
			{
				i = 0;			
				place_filish_flag = 0;
				mission_flag = 9;
			}
		}break;
		case 9:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 10;
			}
		}break;	
		case 10:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;	
				SeHuan = '0';		
				mission_filish_flag = 1;
				mission_flag = 0;
			}
		}break;		
	}
}

void Pile_123(void)	//暂存区码垛
{
	static uint8_t mission_flag=1;

	switch (mission_flag)
	{
		case 1:
		{
			if (WuKuai == '2')
			{
				if (i >= 10)
				{
					i = 0;
					mission_flag = 2;
				}
			}	
		}break;
		case 2:
		{
			Move_Turn_Z(560, 50, 50, 800);  	//爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				mission_flag = 3;			
			}		
		}break;
		case 3:
		{
			Pile_1();														//放置红色
			if (place_filish_flag == 1)
			{
				i = 0;
				mission_flag = 4;
			}
		}break;
		case 4:
		{
			Move_Turn_Z(-560, 50, 50, 800);  	//爪子转到绿色色环对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				mission_flag = 5;			
			}	
		}break;
		case 5:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回到绿色色环对应的位置
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;			
				delay_ms(500);								
				mission_flag = 6;
			}
		}break;		
		case 6:
		{
			Pile_2();														//放置绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				mission_flag = 7;
			}			
		}break;
		case 7:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;					
				delay_ms(500);								
				mission_flag = 8;			
			}				
		}break;
		case 8:
		{
			Pile_3();														//放置蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				mission_flag = 9;
			}			
		}break;	
		case 9:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 10;
			}						
		}break;
		case 10:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回到绿色色环对应的位置
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;
				Execute_flag = 0;		
				mission_filish_flag = 1;
				mission_flag = 0;
			}
		}break;	
	}
}

void Pile_132(void)	//暂存区码垛
{
	static uint8_t mission_flag=1;

	switch (mission_flag)
	{
		case 1:
		{
			if (WuKuai == '2')
			{
				if (i >= 10)
				{
					i = 0;
					mission_flag = 2;
				}
			}			
		}break;
		case 2:
		{	
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				delay_ms(500);								
				mission_flag = 3;
			}		
		}break;
		case 3:
		{
			Pile_1();														//放红色
			if (place_filish_flag == 1)
			{
				i = 0;
				mission_flag = 4;
			}
		}break;
		case 4:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				mission_flag = 5;
			}
		}break;		
		case 5:
		{				
			Move_Turn_Z(-1120, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;			
				delay_ms(500);								
				mission_flag = 6;
			}	
		}break;		
		case 6:
		{		
			Pile_3();														//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				mission_flag = 7;
			}
		}break;
		case 7:
		{				
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 8;
			}	
		}break;
		case 8:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				mission_flag = 9;
			}
		}break;		
		case 9:
		{		
			Pile_2();														//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				Execute_flag = 0;
				mission_filish_flag = 1;
				mission_flag = 0;
			}
		}break;					
	}
}

void Pile_213(void)	//暂存区码垛
{
	static uint8_t mission_flag=1;

	switch (mission_flag)
	{
		case 1:
		{
			if (WuKuai == '2')
			{
				if (i >= 10)
				{
					i = 0;
					mission_flag = 2;
				}
			}		
		}break;
		case 2:
		{	
			Pile_2();														//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				mission_flag = 3;
			}
		}break;	
		case 3:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				delay_ms(500);				
				mission_flag = 4;
			}					
		}break;
		case 4:
		{
			Pile_1();														//放红色
			if (place_filish_flag == 1)
			{
				i = 0;
				mission_flag = 5;
			}
		}break;	
		case 5:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				mission_flag = 6;
			}
		}break;		
		case 6:
		{
			Move_Turn_Z(-1120, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				delay_ms(500);								
				mission_flag = 7;
			}					
		}break;		
		case 7:
		{
			Pile_3();														//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				mission_flag = 8;
			}
		}break;
		case 8:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 9;
			}					
		}break;
		case 9:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;	
				Execute_flag = 0;				
				mission_filish_flag = 1;
				mission_flag = 0;
			}
		}break;		
	}
}

void Pile_231(void)	//暂存区码垛
{
	static uint8_t mission_flag=1;

	switch (mission_flag)
	{
		case 1:
		{
			if (WuKuai == '2')
			{
				if (i >= 10)
				{
					i = 0;
					mission_flag = 2;
				}
			}		
		}break;
		case 2:
		{	
			Pile_2();														//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				mission_flag = 3;
			}
		}break;	
		case 3:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				delay_ms(500);				
				mission_flag = 4;
			}				
		}break;
		case 4:
		{
			Pile_3();														//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				mission_flag = 5;
			}
		}break;
		case 5:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				mission_flag = 6;
			}
		}break;			
		case 6:
		{
			Move_Turn_Z(1120, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				delay_ms(500);				
				mission_flag = 7;
			}					
		}break;	
		case 7:
		{
			Pile_1();														//放红色
			if (place_filish_flag == 1)
			{
				i = 0;
				mission_flag = 8;
			}
			}break;
		case 8:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 9;
			}				
		}break;
		case 9:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;		
				Execute_flag = 0;			
				mission_filish_flag = 1;
				mission_flag = 0;
			}
		}break;		
	}
}

void Pile_312(void)	//暂存区码垛
{
	static uint8_t mission_flag=1;

	switch (mission_flag)
	{
		case 1:
		{
			if (WuKuai == '2')
			{
				if (i >= 10)
				{
					i = 0;
					mission_flag = 2;
				}
			}		
		}break;
		case 2:
		{		
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 3;
			}						
		}break;
		case 3:
		{
			Pile_3();														//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;
				mission_flag = 4;
			}
		}break;
		case 4:
		{
			Move_Y(650, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 650)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				mission_flag = 5;
			}
		}break;		
		case 5:
		{
			Move_Turn_Z(1120, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 1120)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;				
				delay_ms(500);								
				mission_flag = 6;
			}							
		}break;		
		case 6:
		{
			Pile_1();														//放红色
			if (place_filish_flag == 1)
			{
				i = 0;
				mission_flag = 7;
			}
		}break;
		case 7:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到绿色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 8;
			}
		}break;
		case 8:
		{
			Move_Y(650, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 650)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				delay_ms(500);				
				mission_flag = 9;
			}
		}break;		
		case 9:
		{
			Pile_2();															//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;
				Execute_flag = 0;				
				mission_filish_flag = 1;
				mission_flag = 0;
			}
		}break;				
	}
}

void Pile_321(void)	//暂存区码垛
{	
	static uint8_t mission_flag=1;

	switch (mission_flag)
	{
		case 1:
		{
			if (WuKuai == '2')
			{
				if (i >= 10)
				{
					i = 0;
					mission_flag = 2;
				}
			}
		}break;
		case 2:
		{	
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 3;
			}	
		}break;
		case 3:
		{
			Pile_3();														//放蓝色
			if (place_filish_flag == 1)
			{
				i = 0;					
				mission_flag = 4;
			}
		}break;
		case 4:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 5;
			}
		}break;
		case 5:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;			
				delay_ms(500);								
				mission_flag = 6;
			}
		}break;		
		case 6:
		{
			Pile_2();														//放绿色
			if (place_filish_flag == 1)
			{
				i = 0;					
				mission_flag = 7;
			}
		}break;	
		case 7:
		{
			Move_Turn_Z(560, 50, 50, 800);  //爪子转到红色对应的位置
			if (stepPosition_Turn_Z == 560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				delay_ms(500);								
				mission_flag = 8;
			}	
		}break;
		case 8:
		{
			Pile_1();														//放红色
			if (place_filish_flag == 1)
			{
				i = 0;					
				mission_flag = 9;
			}
		}break;
		case 9:
		{
			Move_Turn_Z(-560, 50, 50, 800);  //爪子转到蓝色对应的位置
			if (stepPosition_Turn_Z == -560)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;							
				mission_flag = 10;
			}
		}break;	
		case 10:
		{
			Move_Y(4780, 2500, 2500, 5000);  			//爪子回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;	
				Execute_flag = 0;					
				mission_filish_flag = 1;
				mission_flag = 0;
			}
		}break;		
	}
}
