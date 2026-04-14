#include "system.h"

int task_code1;
int task_code2;

void Map(void)
{
	task_code1 = (QR_Code[0] * 100) + (QR_Code[1] * 10) + (QR_Code[2] * 1);
	task_code2 = (QR_Code[3] * 100) + (QR_Code[4] * 10) + (QR_Code[5] * 1);
	
	Distance_OUTPUT = PID.Position_OUTPUT;
		switch(map_flag)
		{
			case 1:                     
			{
					if (Stop_flag == 1)
					{
							distance_flag = 0;
							angle_flag = 1;
							if (finish_jiaozheng == 1)
							{
								angle_flag = 0;
								delay_ms(15);
								delay_ms(1000);
								map_flag = 2;
								Stop_flag = 0;
								stop_cnt = 0;
								finish_jiaozheng = 0;
							}
					}
					else
					{
						distance_flag = 1;
						Set_target_Position(555);   //出库490
						Aleft(PWM1, PWM2, PWM3, PWM4);
					
					}
			}break;
			case 2:
			{
					distance_flag = 1;
					Set_target_Position(4100);			//扫二维码
					Advance(PWM1, PWM2, PWM3, PWM4);
					if (Stop_flag == 1)
					{
						map_flag = 3;
						Stop_flag = 0;
					}
			}break;
			case 3:						
			{

					if (Stop_flag == 1)
					{
						distance_flag = 0;
						Turntable_123();
						delay_ms(10000);
						map_flag = 4;
						Stop_flag = 0;
					}
					else
					{
							distance_flag = 1;
							Set_target_Position(5200);			//取物区							
							Advance(PWM1, PWM2, PWM3, PWM4);
					}
			}break;	
			case 4:						
			{

					if (Stop_flag == 1)
					{
						delay_ms(500);
						distance_flag = 0;
						angle_flag = 1;
						if (finish_jiaozheng == 1)
						{
							angle_flag = 0;
							delay_ms(15);
//						map_flag = 100;
							map_flag = 5;
							Stop_flag = 0;
							stop_cnt = 0;
							finish_jiaozheng = 0;
						}
					}
					else
					{
						distance_flag = 1;
						Set_target_Position(2200);			//回中线
						Backwards(PWM1, PWM2, PWM3, PWM4);
					}
			}break;
			case 5:                     
			{

					if (Stop_flag == 1)
					{
						distance_flag = 0;
						angle_flag = 1;
						if (finish_jiaozheng == 1)
						{
							angle_flag = 0;
							delay_ms(15);
//						map_flag = 100;
							delay_ms(1000);
							map_flag = 6;
							Stop_flag = 0;
							stop_cnt = 0;
							finish_jiaozheng = 0;
						}
					}
					else
					{
						distance_flag = 1;
						Set_target_Position(11850);			//到粗加工区					
						Aleft(PWM1, PWM2, PWM3, PWM4);
					}
			}break;
			case 6:
			{

					if (Stop_flag == 1)
					{
						distance_flag = 0;
						angle_flag = 1;
						if (finish_jiaozheng == 1)
						{
							angle_flag = 0;
							delay_ms(15);
//						map_flag = 100;
							delay_ms(500);
							map_flag = 7;
							Stop_flag = 0;
							stop_cnt = 0;
							finish_jiaozheng = 0;
						}
					}
					else
					{
							distance_flag = 1;
							Set_target_Position(11550);			//左上角转弯
							Towards_The_right(PWM1, PWM2, PWM3, PWM4);
					}
			}break;
			case 7:						
			{
					if (Stop_flag == 1)
					{
						delay_ms(1000);
						distance_flag = 0;
						map_flag = 8;
						Stop_flag = 0;
					}
					else
					{
						distance_flag = 1;
						Set_target_Position(2500);			//暂存区
						Advance(PWM1, PWM2, PWM3, PWM4);
					}
			}break;	
			case 8:						
			{
					if (Stop_flag == 1)
					{
						distance_flag = 0;
						map_flag = 9;
						Stop_flag = 0;
					}
					else
					{
						distance_flag = 1;
						Set_target_Position(2900);			//右上角转弯
						Advance(PWM1, PWM2, PWM3, PWM4);					
					}
			}break;
			case 9:                     
			{
					if (Stop_flag == 1)
					{
						distance_flag = 0;
						angle_flag = 1;
						if (finish_jiaozheng == 1)
						{
							angle_flag = 0;
							delay_ms(15);
//						map_flag = 100;
							delay_ms(1000);
							map_flag = 10;
							Stop_flag = 0;
							stop_cnt = 0;
							finish_jiaozheng = 0;
						}
					}
					else
					{
						distance_flag = 1;
						Set_target_Position(5950);			//取物区
						Aleft(PWM1, PWM2, PWM3, PWM4);
					}
			}break;
			case 10:
			{
					if (Stop_flag == 1)
					{
						distance_flag = 0;
						map_flag = 11;
						Stop_flag = 0;
					}
					else
					{
						distance_flag = 1;
						Set_target_Position(11000);			//回中线
						Backwards(PWM1, PWM2, PWM3, PWM4);
					}
			}break;
			case 11:						
			{

					if (Stop_flag == 1)
					{
						distance_flag = 0;
						map_flag = 0;
						Stop_flag = 0;
					}
					else
					{
						distance_flag = 1;
						Set_target_Position(6100);			//到粗加工区
						Towards_The_right(PWM1, PWM2, PWM3, PWM4);
					}
			}break;
		}
}
