#include "system.h"

speedRampData srd_Move;

void Move_PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC, ENABLE);
		
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM5);	

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;          
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;            //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	     //速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;            //上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;          
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;            //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	     //速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;            //上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);	
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_0);
	GPIO_ResetBits(GPIOC, GPIO_Pin_1);
	GPIO_ResetBits(GPIOC, GPIO_Pin_2);
	GPIO_ResetBits(GPIOC, GPIO_Pin_3);
	GPIO_ResetBits(GPIOC, GPIO_Pin_4);
	GPIO_ResetBits(GPIOC, GPIO_Pin_5);
	GPIO_ResetBits(GPIOC, GPIO_Pin_6);
	GPIO_ResetBits(GPIOC, GPIO_Pin_7);	

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Prescaler = 84-1;                      //定时器分频 PSC
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;        //向上计数模式
	TIM_TimeBaseStructure.TIM_Period = 100-1;                       //自动重装载值 ARR
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 50-1;															//CCR
//	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;    //在空闲时输出低,这里的设置可以改变TIM_OCPolarity 

	TIM_OC1Init(TIM5, &TIM_OCInitStructure);  
  TIM_OC2Init(TIM5, &TIM_OCInitStructure);
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);  
  TIM_OC4Init(TIM5, &TIM_OCInitStructure);	
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;  // 抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;         // 子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_UpdateRequestConfig(TIM5, TIM_UpdateSource_Regular);
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
  TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能在CCR1上的预装载寄存器
  TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能在CCR1上的预装载寄存器
  TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);	
	
  TIM_ARRPreloadConfig(TIM5,ENABLE);  //  ARPE使能 
  TIM_CtrlPWMOutputs(TIM5, ENABLE);   // 使能TIM1的PWM输出，TIM1与TIM8有效,如果没有这行会问题
	TIM_Cmd(TIM5, ENABLE);
}

void TIM5_IRQHandler(void)
{
	speed_decision();
}

void Move(int step, uint32_t accel, uint32_t decel, uint32_t speed)
{
    unsigned int max_s_lim;
    unsigned int accel_lim;

    if (step == 0) {
        return;
    } else if (step > 0) {
        srd_Move.dir = CCW;
    } else {
        srd_Move.dir = CW;
				step = -step;
    }		

    if (step == 1) {
        srd_Move.accel_count = -1;
        srd_Move.run_state = DECEL;
        srd_Move.step_delay = 1000;
				TIM_SetAutoreload(TIM5, 100-1);
				TIM_SetCompare3(TIM5, 50-1);
				TIM_SetCompare4(TIM5, 50-1);	
				TIM_SetCompare2(TIM5, 50-1);
				TIM_SetCompare1(TIM5, 50-1);				
				TIM_Cmd(TIM5, ENABLE);
    }

    else if (step != 0) {	
			if (stepPosition < 1)
			{
        srd_Move.min_delay = (int32_t)(A_T_x10 / speed);

        srd_Move.step_delay = (int32_t)((T1_FREQ_148 * sqrt(A_SQ / accel)) / 10);

        max_s_lim = (uint32_t)(speed * speed / (A_x200 * accel / 10));

        if (max_s_lim == 0) {
            max_s_lim = 1;
        }

        accel_lim = (uint32_t)(step * decel / (accel + decel));

        if (accel_lim == 0) {
            accel_lim = 1;
        }

        if (accel_lim <= max_s_lim) {
            srd_Move.decel_val = accel_lim - step;
        } else {
            srd_Move.decel_val = -(max_s_lim * accel / decel);
        }

        if (srd_Move.decel_val == 0) {
            srd_Move.decel_val = -1;
        }

        srd_Move.decel_start = step + srd_Move.decel_val;

        if (srd_Move.step_delay <= srd_Move.min_delay) {
            srd_Move.step_delay = srd_Move.min_delay;
            srd_Move.run_state = RUN;
        } else {
            srd_Move.run_state = ACCEL;
        }

        srd_Move.accel_count = 0;
				TIM_SetAutoreload(TIM5, srd_Move.step_delay	-	1);
				TIM_SetCompare3(TIM5, srd_Move.step_delay / 2 - 1); 				
				TIM_SetCompare4(TIM5, srd_Move.step_delay / 2 - 1);  
				TIM_SetCompare2(TIM5, srd_Move.step_delay / 2 - 1);
				TIM_SetCompare1(TIM5, srd_Move.step_delay / 2 - 1);				
				TIM_Cmd(TIM5, ENABLE); 
			}
    }
}

/**
  * @brief  速度决策1
	*	@note 	在中断中使用，每进一次中断，决策一次
  * @retval 无
  */
void speed_decision(void)
{
    uint16_t new_step_delay = 0;
    static uint16_t last_accel_delay = 0;
    static uint32_t step_count = 0;
    static int32_t rest = 0;

    if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) 
    {						
        TIM_ClearITPendingBit(TIM5, TIM_IT_Update); 

        TIM_SetCompare3(TIM5, srd_Move.step_delay / 2);
        TIM_SetCompare4(TIM5, srd_Move.step_delay / 2); 
        TIM_SetCompare2(TIM5, srd_Move.step_delay / 2); 
        TIM_SetCompare1(TIM5, srd_Move.step_delay / 2); 				
				TIM_SetAutoreload(TIM5, srd_Move.step_delay);

        switch (srd_Move.run_state)
        {
            case STOP:
                step_count = 0;  
                rest = 0;        
								TIM5->CCER &= ~(1<<12);								
								TIM_Cmd(TIM5, DISABLE);
								break;
            case ACCEL:
								TIM5->CCER |= 1<<12;							
								StepCounter(srd_Move.dir);							
                step_count++;
                srd_Move.accel_count++;
								
                new_step_delay = srd_Move.step_delay - (((2 * srd_Move.step_delay) + rest) / (4 * srd_Move.accel_count + 1)); 
                rest = ((2 * srd_Move.step_delay) + rest) % (4 * srd_Move.accel_count + 1);  

                if (step_count >= srd_Move.decel_start)
                {
                    srd_Move.accel_count = srd_Move.decel_val;
										srd_Move.run_state = DECEL;
                }
                else if (new_step_delay <= srd_Move.min_delay)
                {
                    last_accel_delay = new_step_delay;
                    new_step_delay = srd_Move.min_delay;
                    rest = 0;
										srd_Move.run_state = RUN;
                }
                break;

            case RUN:
								TIM5->CCER |= 1<<12;							
								StepCounter(srd_Move.dir);	
                step_count++;
                new_step_delay = srd_Move.min_delay;
								
                if (step_count >= srd_Move.decel_start)
                {
                    srd_Move.accel_count = srd_Move.decel_val;
                    new_step_delay = last_accel_delay;
                    srd_Move.run_state = DECEL;
                }
                break;

            case DECEL:
								TIM5->CCER |= 1<<12;							
								StepCounter(srd_Move.dir);	
                step_count++;
                srd_Move.accel_count++;
                new_step_delay = srd_Move.step_delay - (((2 * srd_Move.step_delay) + rest) / (4 * srd_Move.accel_count + 1)); 
                rest = ((2 * srd_Move.step_delay) + rest) % (4 * srd_Move.accel_count + 1);  

                if (srd_Move.accel_count >= 0)
                {
                    srd_Move.run_state = STOP;
                }
                break;
        }
        srd_Move.step_delay = new_step_delay;
    }
}

void StepCounter(signed char inc)
{
	if(inc == CCW)
	{
		stepPosition++;
	}
	else
	{
		stepPosition--;
	}
}

void DIR_LF(uint8_t a)
{
	if(a == CW)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_0);		
	}
	else
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_0);    		
	}
}

void DIR_LB(uint8_t a)
{
	if(a == CW)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_1);		
	}
	else
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_1);    		
	}
}

void DIR_RF(uint8_t a)
{
	if(a == CCW)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_2);		
	}
	else
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_2);    		
	}
}

void DIR_RB(uint8_t a)
{
	if(a == CCW)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_3);		
	}
	else
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_3);    		
	}
}

void Car_dirict(int X, int Y)
{
	if (X < 0) {DIR_LF(CCW); DIR_LB(CCW); DIR_RF(CCW); DIR_RB(CCW);}
	else if(X > 0) {DIR_LF(CW); DIR_LB(CW); DIR_RF(CW); DIR_RB(CW);}
				
	if (Y > 0) {DIR_LF(CCW); DIR_LB(CW); DIR_RF(CW); DIR_RB(CCW);}
	else if(Y < 0) {DIR_LF(CW); DIR_LB(CCW); DIR_RF(CCW); DIR_RB(CW);}				
}

void Car_Move(int Step, int X, int Y)
{
		Car_dirict(X, Y);
		Move(Step, 50, 50, 1600);     //(600, 600, 2400)  (500, 500, 2500)   (500, 500, 3000)  (600, 600, 3000)
		if (stepPosition == Step)
		{				
			Stop_flag = 1;						
			stepPosition = 0;	
		}
}

void Compute(float Turn_Angle)
{
	AnglePID_realize(Pid.target_Angle + Turn_Angle, Receive_Yaw);
}

void Turn_dirict(float Angle)
{
	if (Angle < 0) {DIR_LF(CCW); DIR_LB(CCW); DIR_RF(CW); DIR_RB(CW);}
	else if(Angle > 0) {DIR_LF(CW); DIR_LB(CW); DIR_RF(CCW); DIR_RB(CCW);}							
}

void Car_Turn(int Step, float Angle)
{
		Turn_dirict(Angle);
		Move(Step, 200, 200, 800);
		if (stepPosition == Step)
		{			
			Stop_flag = 1;
			Angle_flag = 1;
			stepPosition = 0;	
		}
}
