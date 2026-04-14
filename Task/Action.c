#include "system.h"

void Grab_1(void)  //从色环处抓
{
	static uint8_t grab_flag=1;	
	switch (grab_flag)
	{
		case 1:
		{
			Move_Z(9600, 2500, 2500, 5000);				//下去	
			if (stepPosition_Z == 9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				grab_flag = 2;
			}
		}break;
		case 2:
		{
			Servo_SetAngle3(18);									//抓
			if (i>50)
			{
				i = 0;	
				delay_ms(200);				
				grab_flag = 3;
			}
		}break;
		case 3:
		{
			Move_Z(-9600, 2500, 2500, 5000);			//上去
			if (stepPosition_Z == -9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				grab_flag = 4;
			}
		}break;	
		case 4:
		{Servo_SetAngle4(6);										//置物台红色
			if (i>50)
			{
				i = 0;	
				delay_ms(500);				
				grab_flag = 5;
			}			
		}break;		
		case 5:
		{
			Move_Turn_Z(1855, 50, 50, 800);    //爪子从红色旋转到置物台
			if (stepPosition_Turn_Z == 1855)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;	
				delay_ms(500);
				grab_flag = 6;
			}				
		}break;	
		case 6:
		{
			Move_Z(2300, 2500, 2500, 5000);				//下去
			if (stepPosition_Z == 2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;	
				delay_ms(500);				
				grab_flag = 7;
			}
		}break;
		case 7:
		{
			Servo_SetAngle3(50);									//放
			if (i>50)
			{
				i = 0;			
				grab_flag = 8;
			}
		} break;
		case 8:
		{
			Move_Z(-2300, 2500, 2500, 5000);			//上去
			if (stepPosition_Z == -2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				grab_flag = 9;
			}
		}break;		
		case 9:
		{
			Move_Turn_Z(-1855, 50, 50, 800);  //爪子转会红色对应的位置
			if (stepPosition_Turn_Z == -1855)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;	
				grab_filish_flag = 1;				
				grab_flag = 0;
			}				
		}break;
	}
}

void Grab_2(void)  //从色环处抓
{
	static uint8_t grab_flag=1;	
	switch (grab_flag)
	{
	
		case 1:
		{
			Move_Z(9600, 2500, 2500, 5000);					//下去
			if (stepPosition_Z == 9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				grab_flag = 2;
			}
		}break;
		case 2:
		{
			Servo_SetAngle3(18);										//抓
			if (i>50)
			{
				i = 0;
				delay_ms(200);				
				grab_flag = 3;
			}
		}break;
		case 3:
		{
			Move_Z(-9600, 2500, 2500, 5000);			//上
			if (stepPosition_Z == -9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				grab_flag = 4;
			}
		}break;		
		case 4:
		{
			Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				grab_flag = 5;
			}
		}break;
		case 5:
		{
			Servo_SetAngle4(129);									//置物台绿色
			if (i>50)
			{
				i = 0;			
				delay_ms(500);
				grab_flag = 6;
			}			
		}break;	
		case 6:
		{
			Move_Turn_Z(2415, 50, 50, 800);		//转到置物台
			if (stepPosition_Turn_Z == 2415)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;	
				delay_ms(500);				
				grab_flag = 7;
			}				
		}break;			
		case 7:
		{
			Move_Z(2300, 2500, 2500, 5000);			//下
			if (stepPosition_Z == 2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;		
				delay_ms(500);
				grab_flag = 8;
			}
		}break;
		case 8:
		{
			Servo_SetAngle3(50);								//放
			if (i>50)
			{
				i = 0;			
				grab_flag = 9;
			}
		} break;
		case 9:
		{
			Move_Z(-2300, 2500, 2500, 5000);			//上
			if (stepPosition_Z == -2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				grab_flag = 10;
			}
		}break;				
		case 10:
		{
			Move_Turn_Z(-2415, 50, 50, 800);		//转回绿色色环
			if (stepPosition_Turn_Z == -2415)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;	
				grab_flag = 11;
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
				grab_filish_flag = 1;				
				grab_flag = 0;
			}
		}break;
	}
}

void Grab_3(void)  //从色环处抓
{
	static uint8_t grab_flag=1;	
	switch (grab_flag)
	{
		case 1:
		{
			Move_Z(9600, 2500, 2500, 5000);			//下
			if (stepPosition_Z == 9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				grab_flag = 2;
			}
		}break;
		case 2:
		{
			Servo_SetAngle3(18);									//抓
			if (i>50)
			{
				i = 0;	
				delay_ms(200);
				grab_flag = 3;
			}
		}break;
		case 3:
		{
			Move_Z(-9600, 2500, 2500, 5000);			//上
			if (stepPosition_Z == -9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				grab_flag = 4;
			}
		}break;	
		case 4:
		{
			Servo_SetAngle4(249);										//置物台蓝色
			if (i>50)
			{
				i = 0;	
				delay_ms(500);				
				grab_flag = 5;
			}			
		}break;			
		case 5:
		{
			Move_Turn_Z(2960, 50, 50, 800);			//爪子转到置物台
			if (stepPosition_Turn_Z == 2960)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;		
				delay_ms(500);
				grab_flag = 6;
			}				
		}break;
		case 6:
		{
			Move_Z(2300, 2500, 2500, 5000);					//下
			if (stepPosition_Z == 2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				delay_ms(500);
				grab_flag = 7;
			}
		}break;
		case 7:
		{
			Servo_SetAngle3(50);										//放
			if (i>50)
			{
				i = 0;			
				grab_flag = 8;
			}
		} break;
		case 8:
		{
			Move_Z(-2300, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				grab_flag = 9;
			}
		}break;		
		case 9:
		{
			Move_Turn_Z(-2975, 50, 50, 800);				//回到蓝色色环位置
			if (stepPosition_Turn_Z == -2975)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;	
				grab_filish_flag = 1;				
				grab_flag = 0;
			}				
		}break;
	}
}

void Place_1(void) //放置在色环中
{	
	static uint8_t place_flag=1;	
	switch (place_flag)
	{
		case 1:
		{
			Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				place_flag = 2;
			}
		}break;	
		case 2:
		{
			Servo_SetAngle4(6);											//置物台红色
			if (i>50)
			{
				i = 0;			
				place_flag = 3;
			}			
		}break;			
		case 3:
		{
			Move_Turn_Z(1855, 50, 50, 800);			//爪子从红色转到车上置物台
			if (stepPosition_Turn_Z == 1855)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;			
				delay_ms(500);				
				place_flag = 4;
			}				
		}break;		
		case 4:
		{
			Move_Z(2300, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				place_flag = 5;
			}
		}break;
		case 5:
		{
			Servo_SetAngle3(18);											//爪子抓取
			if (i>50)
			{
				i = 0;			
				place_flag = 6;
			}
		}break;
		case 6:
		{
			Move_Z(-2300, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				delay_ms(500);
				place_flag = 7;
			}
		}break;
		case 7:
		{
			Move_Turn_Z(-1855, 50, 50, 800);			//爪子转到红色对应的位置
			if (stepPosition_Turn_Z == -1855)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				place_flag = 8;
			}				
		}break;
		case 8:
		{
			Move_Z(9600, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				place_flag = 9;
			}
		}break;
		case 9:
		{
			Servo_SetAngle3(50);										//爪子放置
			if (i>50)
			{
				i = 0;			
				place_flag = 10;
			}
		} break;
		case 10:
		{
			Move_Z(-9600, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;		
				place_filish_flag = 1;				
				place_flag = 0;
			}
		}break;
	}
}

void Place_2(void) //放置在色环中
{
	static uint8_t place_flag=1;	
	switch (place_flag)
	{
		case 1:
		{
			Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				place_flag = 2;
			}
		}break;	
		case 2:
		{
			Servo_SetAngle4(129);										//置物台绿色
			if (i>50)
			{
				i = 0;			
				place_flag = 3;
			}			
		}break;
		case 3:
		{
			Move_Turn_Z(2415, 50, 50, 800);			//爪子从绿色转到车上置物台
			if (stepPosition_Turn_Z == 2415)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;		
				delay_ms(500);				
				place_flag = 4;
			}				
		}break;		
		case 4:
		{
			Move_Z(2300, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				place_flag = 5;
			}
		}break;
		case 5:
		{
			Servo_SetAngle3(18);											//爪子抓取
			if (i>50)
			{
				i = 0;			
				place_flag = 6;
			}
		}break;
		case 6:
		{
			Move_Z(-2300, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;		
				delay_ms(500);				
				place_flag = 7;
			}
		}break;			
		case 7:
		{
			Move_Turn_Z(-2415, 50, 50, 800);			//爪子转到绿色色环对应的位置
			if (stepPosition_Turn_Z == -2415)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				place_flag = 8;
			}				
		}break;
		case 8:
		{
			Move_Y(4780, 2500, 2500, 5000);				//爪子Y回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				place_flag = 9;
			}
		}break;
		case 9:
		{
			Move_Z(9600, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				place_flag = 10;
			}
		}break;
		case 10:
		{
			Servo_SetAngle3(50);										//爪子放置
			if (i>50)
			{
				i = 0;			
				place_flag = 11;
			}
		} break;
		case 11:
		{
			Move_Z(-9600, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;	
				place_filish_flag = 1;								
				place_flag = 0;
			}
		}break;
	}
}

void Place_3(void) //放置在色环中
{
	static uint8_t place_flag=1;	
	switch (place_flag)
	{
		case 1:
		{
			Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				place_flag = 2;
			}
		}break;	
		case 2:
		{
			Servo_SetAngle4(249);										//置物台蓝色
			if (i>50)
			{
				i = 0;			
				place_flag = 3;
			}			
		}break;	
		case 3:
		{
			Move_Turn_Z(2975, 50, 50, 800);			//爪子从蓝色色环转到车上置物台
			if (stepPosition_Turn_Z == 2975)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;			
				delay_ms(500);				
				place_flag = 4;
			}				
		}break;	
		case 4:
		{
			Move_Z(2300, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				place_flag = 5;
			}
		}break;
		case 5:
		{
			Servo_SetAngle3(18);											//爪子抓取
			if (i>50)
			{
				i = 0;			
				place_flag = 6;
			}
		}break;
		case 6:
		{
			Move_Z(-2300, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;
				delay_ms(500);
				place_flag = 7;
			}
		}break;
		case 7:
		{
			Move_Turn_Z(-2975, 50, 50, 800);			//爪子转到蓝色色环对应的位置
			if (stepPosition_Turn_Z == -2975)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				place_flag = 8;
			}				
		}break;
		case 8:
		{
			Move_Z(9600, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				place_flag = 9;
			}
		}break;
		case 9:
		{
			Servo_SetAngle3(50);											//爪子放置
			if (i>50)
			{
				i = 0;			
				place_flag = 10;
			}
		} break;
		case 10:
		{
			Move_Z(-9600, 2500, 2500, 5000);					//爪子上去
			if (stepPosition_Z == -9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;	
				place_filish_flag = 1;								
				place_flag = 0;
			}
		}break;
	}
}

void Pile_1(void) //放置在物块上
{	
	static uint8_t pile_flag=1;	
	switch (pile_flag)
	{
		case 1:
		{
			Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;			
				pile_flag = 2;
			}
		}break;	
		case 2:
		{
			Move_Turn_Z(1855, 50, 50, 800);			//爪子从红色转到车上置物台
			if (stepPosition_Turn_Z == 1855)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;		
//				delay_ms(800);								
				pile_flag = 3;
			}				
		}break;
		case 3:
		{
			Servo_SetAngle4(9);											//置物台红色
			if (i>50)
			{
				i = 0;			
				pile_flag = 4;
			}			
		}break;			
		case 4:
		{
			Move_Z(3950, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 3950)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				pile_flag = 5;
			}
		}break;
		case 5:
		{
			Servo_SetAngle3(18);											//爪子抓取
			if (i>50)
			{
				i = 0;			
				pile_flag = 6;
			}
		}break;
		case 6:
		{
			Move_Z(-3950, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -3950)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				pile_flag = 7;
			}
		}break;
		case 7:
		{
			Move_Turn_Z(-1855, 50, 50, 800);			//爪子转到红色对应的位置
			if (stepPosition_Turn_Z == -1855)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				pile_flag = 8;
			}				
		}break;
		case 8:
		{
			Move_Z(6400, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 6400)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				pile_flag = 9;
			}
		}break;
		case 9:
		{
			Servo_SetAngle3(50);										//爪子放置
			if (i>50)
			{
				i = 0;			
				pile_flag = 10;
			}
		} break;
		case 10:
		{
			Move_Z(-6400, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -6400)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;		
				pile_filish_flag = 1;				
				pile_flag = 0;
			}
		}break;
	}
}

void Pile_2(void) //放置在物块上
{
	static uint8_t pile_flag=1;	
	switch (pile_flag)
	{
		case 1:
		{
			Move_Turn_Z(2415, 50, 50, 800);			//爪子从绿色转到车上置物台
			if (stepPosition_Turn_Z == 2415)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;			
//				delay_ms(800);								
				pile_flag = 2;
			}				
		}break;
		case 2:
		{
			Servo_SetAngle4(129);										//置物台绿色
			if (i>50)
			{
				i = 0;			
				pile_flag = 3;
			}			
		}break;		
		case 3:
		{
			Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				pile_flag = 4;
			}
		}break;			
		case 4:
		{
			Move_Z(2300, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				pile_flag = 5;
			}
		}break;
		case 5:
		{
			Servo_SetAngle3(0);											//爪子抓取
			if (i>50)
			{
				i = 0;			
				pile_flag = 5;
			}
		}break;
		case 6:
		{
			Move_Z(-2300, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				pile_flag = 7;
			}
		}break;
		case 7:
		{
			Move_Y(4780, 2500, 2500, 5000);				//爪子Y回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				pile_flag = 8;
			}
		}break;			
		case 8:
		{
			Move_Turn_Z(-2415, 50, 50, 800);			//爪子转到绿色色环对应的位置
			if (stepPosition_Turn_Z == -2415)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				pile_flag = 9;
			}				
		}break;
		case 9:
		{
			Move_Z(3950, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 3950)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				pile_flag = 10;
			}
		}break;
		case 10:
		{
			Servo_SetAngle3(50);										//爪子放置
			if (i>50)
			{
				i = 0;			
				pile_flag = 11;
			}
		} break;
		case 11:
		{
			Move_Z(-3950, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -3950)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;	
				pile_filish_flag = 1;								
				pile_flag = 0;
			}
		}break;
	}
}

void Pile_3(void) //放置在物块上
{
	static uint8_t pile_flag=1;	
	switch (pile_flag)
	{
		case 1:
		{
			Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				pile_flag = 2;
			}
		}break;	
		case 2:
		{
			Move_Turn_Z(2975, 50, 50, 800);			//爪子从蓝色色环转到车上置物台
			if (stepPosition_Turn_Z == 2975)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;					
//				delay_ms(800);								
				pile_flag = 3;
			}				
		}break;
		case 3:
		{
			Servo_SetAngle4(249);										//置物台蓝色
			if (i>50)
			{
				i = 0;			
				pile_flag = 4;
			}			
		}break;		
		case 4:
		{
			Move_Z(2300, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				pile_flag =5;
			}
		}break;
		case 5:
		{
			Servo_SetAngle3(18);											//爪子抓取
			if (i>50)
			{
				i = 0;			
				pile_flag = 6;
			}
		}break;
		case 6:
		{
			Move_Z(-2300, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				pile_flag = 7;
			}
		}break;
		case 7:
		{
			Move_Turn_Z(-2975, 50, 50, 800);			//爪子转到蓝色色环对应的位置
			if (stepPosition_Turn_Z == -2975)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				pile_flag = 8;
			}				
		}break;
		case 8:
		{
			Move_Z(3950, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 3950)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				pile_flag = 9;
			}
		}break;
		case 9:
		{
			Servo_SetAngle3(50);											//爪子放置
			if (i>50)
			{
				i = 0;			
				pile_flag = 10;
			}
		} break;
		case 10:
		{
			Move_Z(-3950, 2500, 2500, 5000);					//爪子上去
			if (stepPosition_Z == -3950)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;	
				pile_filish_flag = 1;								
				pile_flag = 0;
			}
		}break;
	}
}

void Grab_11(void)  //从色环处抓
{
	static uint8_t grab_flag=1;	
	switch (grab_flag)
	{
		case 1:
		{
			Move_Z(9600, 2500, 2500, 5000);				//下去	
			if (stepPosition_Z == 9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				grab_flag = 2;
			}
		}break;
		case 2:
		{
			Servo_SetAngle3(18);									//抓
			if (i>50)
			{
				i = 0;	
				delay_ms(200);				
				grab_flag = 3;
			}
		}break;
		case 3:
		{
			Move_Z(-9600, 2500, 2500, 5000);			//上去
			if (stepPosition_Z == -9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				grab_flag = 4;
			}
		}break;	
		case 4:
		{Servo_SetAngle4(6);										//置物台红色
			if (i>50)
			{
				i = 0;	
				delay_ms(500);				
				grab_flag = 5;
			}			
		}break;		
		case 5:
		{
			Move_Turn_Z(1855, 50, 50, 800);    //爪子从红色旋转到置物台
			if (stepPosition_Turn_Z == 1855)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;	
				delay_ms(500);
				grab_flag = 6;
			}				
		}break;	
		case 6:
		{
			Move_Z(2300, 2500, 2500, 5000);				//下去
			if (stepPosition_Z == 2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;	
				delay_ms(500);				
				grab_flag = 7;
			}
		}break;
		case 7:
		{
			Servo_SetAngle3(50);									//放
			if (i>50)
			{
				i = 0;			
				grab_flag = 8;
			}
		} break;
		case 8:
		{
			Move_Z(-2300, 2500, 2500, 5000);			//上去
			if (stepPosition_Z == -2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				grab_flag = 9;
			}
		}break;		
		case 9:
		{
			Move_Turn_Z(-1855, 50, 50, 800);  //爪子转会红色对应的位置
			if (stepPosition_Turn_Z == -1855)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;	
				grab_filish_flag = 1;				
				grab_flag = 0;
			}				
		}break;
	}
}

void Grab_22(void)  //从色环处抓
{
	static uint8_t grab_flag=1;	
	switch (grab_flag)
	{
	
		case 1:
		{
			Move_Z(9600, 2500, 2500, 5000);					//下去
			if (stepPosition_Z == 9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				grab_flag = 2;
			}
		}break;
		case 2:
		{
			Servo_SetAngle3(18);										//抓
			if (i>50)
			{
				i = 0;
				delay_ms(200);				
				grab_flag = 3;
			}
		}break;
		case 3:
		{
			Move_Z(-9600, 2500, 2500, 5000);			//上
			if (stepPosition_Z == -9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				grab_flag = 4;
			}
		}break;		
		case 4:
		{
			Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				grab_flag = 5;
			}
		}break;
		case 5:
		{
			Servo_SetAngle4(129);									//置物台绿色
			if (i>50)
			{
				i = 0;			
				delay_ms(500);
				grab_flag = 6;
			}			
		}break;	
		case 6:
		{
			Move_Turn_Z(2415, 50, 50, 800);		//转到置物台
			if (stepPosition_Turn_Z == 2415)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;	
				delay_ms(500);				
				grab_flag = 7;
			}				
		}break;			
		case 7:
		{
			Move_Z(2300, 2500, 2500, 5000);			//下
			if (stepPosition_Z == 2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;		
				delay_ms(500);
				grab_flag = 8;
			}
		}break;
		case 8:
		{
			Servo_SetAngle3(50);								//放
			if (i>50)
			{
				i = 0;			
				grab_flag = 9;
			}
		} break;
		case 9:
		{
			Move_Z(-2300, 2500, 2500, 5000);			//上
			if (stepPosition_Z == -2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				grab_flag = 10;
			}
		}break;				
		case 10:
		{
			Move_Turn_Z(-2415, 50, 50, 800);		//转回绿色色环
			if (stepPosition_Turn_Z == -2415)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;	
				grab_flag = 11;
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
				grab_filish_flag = 1;				
				grab_flag = 0;
			}
		}break;
	}
}

void Grab_33(void)  //从色环处抓
{
	static uint8_t grab_flag=1;	
	switch (grab_flag)
	{
		case 1:
		{
			Move_Z(9600, 2500, 2500, 5000);			//下
			if (stepPosition_Z == 9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				grab_flag = 2;
			}
		}break;
		case 2:
		{
			Servo_SetAngle3(18);									//抓
			if (i>50)
			{
				i = 0;	
				delay_ms(200);
				grab_flag = 3;
			}
		}break;
		case 3:
		{
			Move_Z(-9600, 2500, 2500, 5000);			//上
			if (stepPosition_Z == -9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				grab_flag = 4;
			}
		}break;	
		case 4:
		{
			Servo_SetAngle4(249);										//置物台蓝色
			if (i>50)
			{
				i = 0;	
				delay_ms(500);				
				grab_flag = 5;
			}			
		}break;			
		case 5:
		{
			Move_Turn_Z(2960, 50, 50, 800);			//爪子转到置物台
			if (stepPosition_Turn_Z == 2960)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;		
				delay_ms(500);
				grab_flag = 6;
			}				
		}break;
		case 6:
		{
			Move_Z(2300, 2500, 2500, 5000);					//下
			if (stepPosition_Z == 2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				delay_ms(500);
				grab_flag = 7;
			}
		}break;
		case 7:
		{
			Servo_SetAngle3(50);										//放
			if (i>50)
			{
				i = 0;			
				grab_flag = 8;
			}
		} break;
		case 8:
		{
			Move_Z(-2300, 2500, 2500, 5000);				//上
			if (stepPosition_Z == -2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				grab_flag = 9;
			}
		}break;		
		case 9:
		{
			Move_Turn_Z(-2975, 50, 50, 800);				//回到蓝色色环位置
			if (stepPosition_Turn_Z == -2975)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;	
				grab_filish_flag = 1;				
				grab_flag = 0;
			}				
		}break;
	}
}

void Place_11(void) //放置在色环中
{	
	static uint8_t place_flag=1;	
	switch (place_flag)
	{
		case 1:
		{
			Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				place_flag = 2;
			}
		}break;	
		case 2:
		{
			Servo_SetAngle4(6);											//置物台红色
			if (i>50)
			{
				i = 0;			
				place_flag = 3;
			}			
		}break;			
		case 3:
		{
			Move_Turn_Z(1855, 50, 50, 800);			//爪子从红色转到车上置物台
			if (stepPosition_Turn_Z == 1855)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;			
				delay_ms(500);				
				place_flag = 4;
			}				
		}break;		
		case 4:
		{
			Move_Z(2300, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				place_flag = 5;
			}
		}break;
		case 5:
		{
			Servo_SetAngle3(18);											//爪子抓取
			if (i>50)
			{
				i = 0;			
				place_flag = 6;
			}
		}break;
		case 6:
		{
			Move_Z(-2300, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				delay_ms(500);
				place_flag = 7;
			}
		}break;
		case 7:
		{
			Move_Turn_Z(-1855, 50, 50, 800);			//爪子转到红色对应的位置
			if (stepPosition_Turn_Z == -1855)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				place_flag = 8;
			}				
		}break;
		case 8:
		{
			Move_Z(9600, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				place_flag = 9;
			}
		}break;
		case 9:
		{
			Servo_SetAngle3(50);										//爪子放置
			if (i>50)
			{
				i = 0;			
				place_flag = 10;
			}
		} break;
		case 10:
		{
			Move_Z(-9600, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;		
				place_filish_flag = 1;				
				place_flag = 0;
			}
		}break;
	}
}

void Place_22(void) //放置在色环中
{
	static uint8_t place_flag=1;	
	switch (place_flag)
	{
		case 1:
		{
			Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				place_flag = 2;
			}
		}break;	
		case 2:
		{
			Servo_SetAngle4(129);										//置物台绿色
			if (i>50)
			{
				i = 0;			
				place_flag = 3;
			}			
		}break;
		case 3:
		{
			Move_Turn_Z(2415, 50, 50, 800);			//爪子从绿色转到车上置物台
			if (stepPosition_Turn_Z == 2415)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;		
				delay_ms(500);				
				place_flag = 4;
			}				
		}break;		
		case 4:
		{
			Move_Z(2300, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				place_flag = 5;
			}
		}break;
		case 5:
		{
			Servo_SetAngle3(18);											//爪子抓取
			if (i>50)
			{
				i = 0;			
				place_flag = 6;
			}
		}break;
		case 6:
		{
			Move_Z(-2300, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;		
				delay_ms(500);				
				place_flag = 7;
			}
		}break;			
		case 7:
		{
			Move_Turn_Z(-2415, 50, 50, 800);			//爪子转到绿色色环对应的位置
			if (stepPosition_Turn_Z == -2415)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				place_flag = 8;
			}				
		}break;
		case 8:
		{
			Move_Y(4780, 2500, 2500, 5000);				//爪子Y回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				place_flag = 9;
			}
		}break;
		case 9:
		{
			Move_Z(9600, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				place_flag = 10;
			}
		}break;
		case 10:
		{
			Servo_SetAngle3(50);										//爪子放置
			if (i>50)
			{
				i = 0;			
				place_flag = 11;
			}
		} break;
		case 11:
		{
			Move_Z(-9600, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;	
				place_filish_flag = 1;								
				place_flag = 0;
			}
		}break;
	}
}

void Place_33(void) //放置在色环中
{
	static uint8_t place_flag=1;	
	switch (place_flag)
	{
		case 1:
		{
			Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				place_flag = 2;
			}
		}break;	
		case 2:
		{
			Servo_SetAngle4(249);										//置物台蓝色
			if (i>50)
			{
				i = 0;			
				place_flag = 3;
			}			
		}break;	
		case 3:
		{
			Move_Turn_Z(2975, 50, 50, 800);			//爪子从蓝色色环转到车上置物台
			if (stepPosition_Turn_Z == 2975)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;			
				delay_ms(500);				
				place_flag = 4;
			}				
		}break;	
		case 4:
		{
			Move_Z(2300, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				place_flag = 5;
			}
		}break;
		case 5:
		{
			Servo_SetAngle3(18);											//爪子抓取
			if (i>50)
			{
				i = 0;			
				place_flag = 6;
			}
		}break;
		case 6:
		{
			Move_Z(-2300, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;
				delay_ms(500);
				place_flag = 7;
			}
		}break;
		case 7:
		{
			Move_Turn_Z(-2975, 50, 50, 800);			//爪子转到蓝色色环对应的位置
			if (stepPosition_Turn_Z == -2975)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				place_flag = 8;
			}				
		}break;
		case 8:
		{
			Move_Z(9600, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				place_flag = 9;
			}
		}break;
		case 9:
		{
			Servo_SetAngle3(50);											//爪子放置
			if (i>50)
			{
				i = 0;			
				place_flag = 10;
			}
		} break;
		case 10:
		{
			Move_Z(-9600, 2500, 2500, 5000);					//爪子上去
			if (stepPosition_Z == -9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;	
				place_filish_flag = 1;								
				place_flag = 0;
			}
		}break;
	}
}

void Place_13(void) //放置在色环中
{	
	static uint8_t place_flag=1;	
	switch (place_flag)
	{
		case 1:
		{
			Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				place_flag = 2;
			}
		}break;	
		case 2:
		{
			Servo_SetAngle4(6);											//置物台红色
			if (i>50)
			{
				i = 0;			
				place_flag = 3;
			}			
		}break;			
		case 3:
		{
			Move_Turn_Z(1855, 50, 50, 800);			//爪子从红色转到车上置物台
			if (stepPosition_Turn_Z == 1855)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;			
				delay_ms(500);				
				place_flag = 4;
			}				
		}break;		
		case 4:
		{
			Move_Z(2300, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				place_flag = 5;
			}
		}break;
		case 5:
		{
			Servo_SetAngle3(18);											//爪子抓取
			if (i>50)
			{
				i = 0;			
				place_flag = 6;
			}
		}break;
		case 6:
		{
			Move_Z(-2300, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				delay_ms(500);
				place_flag = 7;
			}
		}break;
		case 7:
		{
			Move_Turn_Z(-1855, 50, 50, 800);			//爪子转到红色对应的位置
			if (stepPosition_Turn_Z == -1855)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				place_flag = 8;
			}				
		}break;
		case 8:
		{
			Move_Z(9600, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				place_flag = 9;
			}
		}break;
		case 9:
		{
			Servo_SetAngle3(50);										//爪子放置
			if (i>50)
			{
				i = 0;			
				place_flag = 10;
			}
		} break;
		case 10:
		{
			Move_Z(-9600, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;		
				place_filish_flag = 1;				
				place_flag = 0;
			}
		}break;
	}
}

void Place_23(void) //放置在色环中
{
	static uint8_t place_flag=1;	
	switch (place_flag)
	{
		case 1:
		{
			Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				place_flag = 2;
			}
		}break;	
		case 2:
		{
			Servo_SetAngle4(129);										//置物台绿色
			if (i>50)
			{
				i = 0;			
				place_flag = 3;
			}			
		}break;
		case 3:
		{
			Move_Turn_Z(2415, 50, 50, 800);			//爪子从绿色转到车上置物台
			if (stepPosition_Turn_Z == 2415)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;		
				delay_ms(500);				
				place_flag = 4;
			}				
		}break;		
		case 4:
		{
			Move_Z(2300, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				place_flag = 5;
			}
		}break;
		case 5:
		{
			Servo_SetAngle3(18);											//爪子抓取
			if (i>50)
			{
				i = 0;			
				place_flag = 6;
			}
		}break;
		case 6:
		{
			Move_Z(-2300, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;		
				delay_ms(500);				
				place_flag = 7;
			}
		}break;			
		case 7:
		{
			Move_Turn_Z(-2415, 50, 50, 800);			//爪子转到绿色色环对应的位置
			if (stepPosition_Turn_Z == -2415)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				place_flag = 8;
			}				
		}break;
		case 8:
		{
			Move_Y(4780, 2500, 2500, 5000);				//爪子Y回位
			if (stepPosition_Y == 4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				place_flag = 9;
			}
		}break;
		case 9:
		{
			Move_Z(9600, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				place_flag = 10;
			}
		}break;
		case 10:
		{
			Servo_SetAngle3(50);										//爪子放置
			if (i>50)
			{
				i = 0;			
				place_flag = 11;
			}
		} break;
		case 11:
		{
			Move_Z(-9600, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;	
				place_filish_flag = 1;								
				place_flag = 0;
			}
		}break;
	}
}

void Place_32(void) //放置在色环中
{
	static uint8_t place_flag=1;	
	switch (place_flag)
	{
		case 1:
		{
			Move_Y(-4780, 2500, 2500, 5000);				//爪子Y回位
			if (stepPosition_Y == -4780)
			{
				TIM_Cmd(TIM2, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_10);
				stepPosition_Y = 0;
				i = 0;				
				place_flag = 2;
			}
		}break;	
		case 2:
		{
			Servo_SetAngle4(249);										//置物台蓝色
			if (i>50)
			{
				i = 0;			
				place_flag = 3;
			}			
		}break;	
		case 3:
		{
			Move_Turn_Z(2975, 50, 50, 800);			//爪子从蓝色色环转到车上置物台
			if (stepPosition_Turn_Z == 2975)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;			
				delay_ms(500);				
				place_flag = 4;
			}				
		}break;	
		case 4:
		{
			Move_Z(2300, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				place_flag = 5;
			}
		}break;
		case 5:
		{
			Servo_SetAngle3(18);											//爪子抓取
			if (i>50)
			{
				i = 0;			
				place_flag = 6;
			}
		}break;
		case 6:
		{
			Move_Z(-2300, 2500, 2500, 5000);				//爪子上去
			if (stepPosition_Z == -2300)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;
				delay_ms(500);
				place_flag = 7;
			}
		}break;
		case 7:
		{
			Move_Turn_Z(-2975, 50, 50, 800);			//爪子转到蓝色色环对应的位置
			if (stepPosition_Turn_Z == -2975)
			{
				TIM_Cmd(TIM4, DISABLE);
				GPIO_SetBits(GPIOD, GPIO_Pin_13);
				stepPosition_Turn_Z = 0;
				i = 0;						
				place_flag = 8;
			}				
		}break;
		case 8:
		{
			Move_Z(9600, 2500, 2500, 5000);					//爪子下去
			if (stepPosition_Z == 9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;				
				place_flag = 9;
			}
		}break;
		case 9:
		{
			Servo_SetAngle3(50);											//爪子放置
			if (i>50)
			{
				i = 0;			
				place_flag = 10;
			}
		} break;
		case 10:
		{
			Move_Z(-9600, 2500, 2500, 5000);					//爪子上去
			if (stepPosition_Z == -9600)
			{
				TIM_Cmd(TIM3, DISABLE);
				GPIO_SetBits(GPIOB, GPIO_Pin_0);
				stepPosition_Z = 0;
				i = 0;	
				place_filish_flag = 1;								
				place_flag = 0;
			}
		}break;
	}
}
