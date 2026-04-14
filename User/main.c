#include "stm32f4xx.h"                  // Device header
#include "system.h"

int   stepPosition, stepPosition_Y, stepPosition_Z, stepPosition_Turn_Z;  //²½Êı¼ÆÊı
int   Turn_Step, duizheng_step_X, duizheng_step_Y;  //²½Êı¼ÆÊı
float 	Receive_Roll, Receive_Pitch, Receive_Yaw;
float 	yaw, sum, Yaw_last, Turn_Angle;
int		Angle_output, count, task_code1, task_code2;
uint8_t 	map_flag = 1;
uint8_t		Stop_flag = 0;
uint8_t   flag_a = 1;
uint8_t   grab_flag = 1;
uint8_t   grab_filish_flag = 0;
uint8_t   place_flag = 1;
uint8_t   place_filish_flag = 0;
uint8_t   pile_flag = 1;
uint8_t   pile_filish_flag = 0;
uint8_t   Turntable_flag = 1;
uint8_t   Turntable_filish_flag = 0;
uint8_t   task_flag = 0;
uint8_t   task_filish_flag = 0;
uint8_t   mission_flag = 0;
uint8_t   mission_filish_flag = 0;
uint8_t   Turntable_task_flag = 0;
uint8_t 	Turntable_task_filish_flag = 0; //zhuqu
uint8_t 	Angle_flag = 0;
int   i,c;
int   sstep;



void JY901B_check(float num)
{
	int count = 0; (void) count; // æ¶ˆé™¤æœªä½¿ç”¨è­¦å‘Š SiJY 26-4-14  ç¡®å®šä¸ä½¿ç”¨ä¹‹åï¼Œéœ€è¦æ¸…é™¤
	float Yaw_last = 1000;	
	float sum = 0; (void) sum  ; // æ¶ˆé™¤æœªä½¿ç”¨è­¦å‘Š SiJY 26-4-14

	Receive_Gyro();
	while(Receive_Yaw==0)
	{
		Yaw_last = 1000;
		Receive_Gyro();
	}

	while(1)
	{
		if(fabs(Receive_Yaw - Yaw_last) < num)
		{
			Pid.target_Angle = Receive_Yaw;
			break;
		}
		Yaw_last = Receive_Yaw;
		delay_ms(12);
		Receive_Gyro();
	
	}
}

void Data_handle(void)
{
	task_code1 = (QR_Code[0] - 48) * 100 + (QR_Code[1] - 48) * 10 + (QR_Code[2] - 48) * 1;
	task_code2 = (QR_Code[3] - 48) * 100 +( QR_Code[4] - 48) * 10 + (QR_Code[5] - 48) * 1;
}


int main(void)
{ 
	System_Init();
	JY901B_check(0.01);
//	Timer7_Init(8400 - 1, 100 - 1);	
	TIM_Cmd(TIM7,ENABLE); // Ê¹ÄÜ¶¨Ê±Æ÷
	map_flag = 1;
	Turntable_flag = 2;
	place_filish_flag = 0;
	place_flag = 1;
//	Turntable_task_flag = 1;
	Servo_SetAngle4(69);//1
	Servo_SetAngle3(50);


	while (1)
	{
		Data_handle();
		Receive_Gyro();		
		switch (map_flag)
		{
			case 1:
			{
				Car_Move(1800, 0, -1);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(1000);
						map_flag = 2;
				}
			}break;
			case 2:
			{
				Car_Move(9600, 1, 0);
				if (Stop_flag == 1)
				{	
						Stop_flag = 0;
						map_flag = 50;							
				}				
			}break;
			case 50:
			{
					Move_Turn_Z(-2415, 50, 50, 800);			//×¦×Ó´ÓÀ¶É«É«»·×ªµ½³µÉÏÖÃÎïÌ¨
					if (stepPosition_Turn_Z == -2415)
					{
						TIM_Cmd(TIM4, DISABLE);
						GPIO_SetBits(GPIOD, GPIO_Pin_13);
						stepPosition_Turn_Z = 0;
						i = 0;			
						Stop_flag = 0;
						delay_ms(200);				
						map_flag = 3;
					}	
			}break;
			case 3:
			{
				Car_Move(9200, 1, 0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(500);				
						map_flag = 51;
				}				
			}break;
			case 51:
			{
				switch (task_code1)
						{
							case 123:
							{
								Turntable_123();
								if (Turntable_task_filish_flag == 1)
								{
									Stop_flag = 0;
									Turntable_task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 4;
								}
							}break;
							case 132:
							{
								Turntable_132();
								if (Turntable_task_filish_flag == 1)
								{
									Stop_flag = 0;
									Turntable_task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 4;
								}
							}break;
							case 213:
							{
								Turntable_213();
								if (Turntable_task_filish_flag == 1)
								{
									Stop_flag = 0;
									Turntable_task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 4;
								}
							}break;
							case 231:
							{
								Turntable_231();
								if (Turntable_task_filish_flag == 1)
								{
									Stop_flag = 0;
									Turntable_task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 4;
								}
							}break;
							case 312:
							{
								Turntable_312();
								if (Turntable_task_filish_flag == 1)
								{
									Stop_flag = 0;
									Turntable_task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 4;
								}
							}break;
							case 321:
							{
								Turntable_321();
								if (Turntable_task_filish_flag == 1)
								{
									Stop_flag = 0;
									Turntable_task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 4;
								}
							}break;
						}
			}break;
			case 4:
			{
				Car_Move(5200, -1, 0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(1000);						
						map_flag = 5;
				}				
			}break;
			case 5:
			{
				Car_Turn(4620, 90.0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(1000);						
						map_flag = 6;
				}				
			}break;			
			case 6:
			{
				Car_Move(22400, 1, 0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(1000);						
						map_flag = 7;
				}				
			}break;
			case 7:
			{
				Car_Turn(4650, 90.0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(1000);						
						map_flag = 40;
				}				
			}break;	
			case 40:
			{
				Car_Move(600, 0, 1);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(1000);						
						map_flag = 52;
				}				
			}break;
			case 52:
			{
						switch (task_code1)
						{
							case 123:
							{
								Task_123();
								if (task_filish_flag == 1)
								{
									Stop_flag = 0;
									task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 41;
								}
							}break;
							case 132:
							{
								Task_132();
								if (task_filish_flag == 1)
								{
									Stop_flag = 0;
									task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 41;
								}
							}break;
							case 213:
							{
								Task_213();
								if (task_filish_flag == 1)
								{
									Stop_flag = 0;
									task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 41;
								}
							}break;
							case 231:
							{
								Task_231();
								if (task_filish_flag == 1)
								{
									Stop_flag = 0;
									task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 41;
								}
							}break;
							case 312:
							{
								Task_312();
								if (task_filish_flag == 1)
								{
									Stop_flag = 0;
									task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 41;
								}
							}break;
							case 321:
							{
								Task_321();
								if (task_filish_flag == 1)
								{
									Stop_flag = 0;
									task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 41;
								}
							}break;
						}
			}break;
			case 41:
			{
				Car_Move(600, 0, -1);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(1000);						
						map_flag = 8;
				}				
			}break;			
			case 8:
			{
				Car_Move(10700, -1, 0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(1000);						
						map_flag = 9;
				}				
			}break;
			case 9:
			{
				Car_Turn(4650, -90.0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(1000);						
						map_flag = 10;
				}				
			}break;				
			case 10:
			{
				Car_Move(10600, -1, 0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(1000);						
						map_flag = 42;
				}				
			}break;
			case 42:
			{
				Car_Move(600, 0, 1);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(200);						
						map_flag = 53;
				}				
			}break;
			case 53:
			{
						switch (task_code1)
						{
							case 123:
							{
								Mission_123();
								if (mission_filish_flag == 1)
								{
									Stop_flag = 0;
									mission_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 43;
								}
							}break;
							case 132:
							{
								Mission_132();
								if (mission_filish_flag == 1)
								{
									Stop_flag = 0;
									mission_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 43;
								}
							}break;
							case 213:
							{
								Mission_213();
								if (mission_filish_flag == 1)
								{
									Stop_flag = 0;
									mission_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 43;
								}
							}break;
							case 231:
							{
								Mission_231();
								if (mission_filish_flag == 1)
								{
									Stop_flag = 0;
									mission_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 43;
								}
							}break;
							case 312:
							{
								Mission_312();
								if (mission_filish_flag == 1)
								{
									Stop_flag = 0;
									mission_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 43;
								}
							}break;
							case 321:
							{
								Mission_321();
								if (mission_filish_flag == 1)
								{
									Stop_flag = 0;
									mission_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 43;
								}
							}break;
						}			
			}break;
			case 43:
			{
				Car_Move(600, 0, -1);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(1000);						
						map_flag = 11;
				}				
			}break;			
			case 11:
			{
				Car_Move(11400, -1, 0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(1000);						
						map_flag = 12;
				}				
			}break;
			case 12:
			{
				Car_Turn(4670, -90.0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;	
						delay_ms(1000);						
						map_flag = 13;
				}				
			}break;			
			case 13:
			{
				Car_Move(5200, -1, 0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;	
						delay_ms(1000);						
						map_flag = 54;
				}				
			}break;
			case 54:
			{
						switch (task_code2)
						{
							case 123:
							{
								Turntable_123_2();
								if (Turntable_task_filish_flag == 1)
								{
									Stop_flag = 0;
									Turntable_task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 14;
								}
							}break;
							case 132:
							{
								Turntable_132_2();
								if (Turntable_task_filish_flag == 1)
								{
									Stop_flag = 0;
									Turntable_task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 14;
								}
							}break;
							case 213:
							{
								Turntable_213_2();
								if (Turntable_task_filish_flag == 1)
								{
									Stop_flag = 0;
									Turntable_task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 14;
								}
							}break;
							case 231:
							{
								Turntable_231_2();
								if (Turntable_task_filish_flag == 1)
								{
									Stop_flag = 0;
									Turntable_task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 14;
								}
							}break;
							case 312:
							{
								Turntable_312_2();
								if (Turntable_task_filish_flag == 1)
								{
									Stop_flag = 0;
									Turntable_task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 14;
								}
							}break;
							case 321:
							{
								Turntable_321_2();
								if (Turntable_task_filish_flag == 1)
								{
									Stop_flag = 0;
									Turntable_task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 14;
								}
							}break;
						}
			}break;
			case 14:
			{
				Car_Move(5320, -1, 0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;	
						delay_ms(1000);						
						map_flag = 15;
				}				
			}break;	
			case 15:
			{
				Car_Turn(4690, 90);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(1000);						
						map_flag = 16;
				}				
			}break;			
			case 16:
			{
				Car_Move(22400, 1, 0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;	
						delay_ms(1000);						
						map_flag = 44;
				}				
			}break;

			case 17:
			{
				Car_Turn(4630, 90.0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;	
						delay_ms(1000);						
						map_flag = 44;
				}				
			}break;
			case 44:
			{
				Car_Move(680, 0, 1);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;	
						delay_ms(1000);						
						map_flag = 55;
				}				
			}break;
			case 55:
			{
						switch (task_code2)
						{
							case 123:
							{
								Task_123_2();
								if (task_filish_flag == 1)
								{
									Stop_flag = 0;
									task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 45;
								}
							}break;
							case 132:
							{
								Task_132_2();
								if (task_filish_flag == 1)
								{
									Stop_flag = 0;
									task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 45;
								}
							}break;
							case 213:
							{
								Task_213_2();
								if (task_filish_flag == 1)
								{
									Stop_flag = 0;
									task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 45;
								}
							}break;
							case 231:
							{
								Task_231_2();
								if (task_filish_flag == 1)
								{
									Stop_flag = 0;
									task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 45;
								}
							}break;
							case 312:
							{
								Task_312_2();
								if (task_filish_flag == 1)
								{
									Stop_flag = 0;
									task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 45;
								}
							}break;
							case 321:
							{
								Task_321_2();
								if (task_filish_flag == 1)
								{
									Stop_flag = 0;
									task_filish_flag = 0;
									delay_ms(1000);						
									map_flag = 45;
								}
							}break;
						}			
			}break;
			case 45:
			{
				Car_Move(680, 0, -1);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(1000);						
						map_flag = 18;
				}				
			}break;			
			case 18:
			{
				Car_Move(10400, -1, 0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(1000);						
						map_flag = 19;
				}				
			}break;
			case 19:
			{
				Car_Turn(4630, -90.0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;	
						delay_ms(1000);						
						map_flag = 20;
				}				
			}break;			
			case 20:
			{
				Car_Move(11000, -1, 0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(1000);						
						map_flag = 21;
				}				
			}break;
			case 21:
			{
				Car_Move(11200, -1, 0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(1000);						
						map_flag = 22;
				}				
			}break;		
			case 22:
			{
				Car_Turn(4670, -90);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;	
						delay_ms(1000);						
						map_flag = 23;
				}				
			}break;			
			case 23:
			{
				Car_Move(23680, -1, 0);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;
						delay_ms(1000);						
						map_flag = 24;
				}				
			}break;
			case 24:
			{
				Car_Move(2320, 0, 1);
				if (Stop_flag == 1)
				{
						Stop_flag = 0;	
						delay_ms(1000);						
						map_flag = 0;
				}				
			}break;												
			case 0:
			{
				Car_Move(0, 0, 0);
			}break;	
		}
	}
}
