#include "system.h"

speedRampData srd_Y;

void Action_Y_PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);
		
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15;          
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;            //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	     //速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;            //上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_11;          
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;            //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	     //速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;            //上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_15);
	GPIO_ResetBits(GPIOB, GPIO_Pin_10);
	GPIO_ResetBits(GPIOB, GPIO_Pin_11);	

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Prescaler = 84-1;                      //定时器分频 PSC
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;        //向上计数模式
	TIM_TimeBaseStructure.TIM_Period = 100-1;                       //自动重装载值 ARR
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 50-1;															//CCR
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;    //在空闲时输出低,这里的设置可以改变TIM_OCPolarity 

	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;  // 抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;         // 子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_UpdateRequestConfig(TIM2, TIM_UpdateSource_Regular);
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能在CCR1上的预装载寄存器
	
  TIM_ARRPreloadConfig(TIM2,ENABLE);  //  ARPE使能 
  TIM_CtrlPWMOutputs(TIM2, ENABLE);   // 使能TIM1的PWM输出，TIM1与TIM2有效,如果没有这行会问题
	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void)
{
	speed_decision_Y();
}

void Move_Y(int step, uint32_t accel, uint32_t decel, uint32_t speed)
{
    unsigned int max_s_lim;
    unsigned int accel_lim;

    if (step == 0) {
        return;
    } else if (step > 0) {
        srd_Y.dir = CCW;
    } else {
        srd_Y.dir = CW;
    }
    DIR_Y(srd_Y.dir);		

    if (step == 1) {
        srd_Y.accel_count = -1;
        srd_Y.run_state = DECEL;
        srd_Y.step_delay = 1000;
				TIM_SetAutoreload(TIM2, 100-1);
				TIM_SetCompare1(TIM2, 50-1);				
				TIM_Cmd(TIM2, ENABLE);
    }

    else if (step != 0) {		
			if (stepPosition_Y <1)
			{
        srd_Y.min_delay = (int32_t)(A_T_x10 / speed);

        srd_Y.step_delay = (int32_t)((T1_FREQ_148 * sqrt(A_SQ / accel)) / 10);

        max_s_lim = (uint32_t)(speed * speed / (A_x200 * accel / 10));

        if (max_s_lim == 0) {
            max_s_lim = 1;
        }

        accel_lim = (uint32_t)(step * decel / (accel + decel));

        if (accel_lim == 0) {
            accel_lim = 1;
        }

        if (accel_lim <= max_s_lim) {
            srd_Y.decel_val = accel_lim - step;
        } else {
            srd_Y.decel_val = -(max_s_lim * accel / decel);
        }

        if (srd_Y.decel_val == 0) {
            srd_Y.decel_val = -1;
        }

        srd_Y.decel_start = step + srd_Y.decel_val;

        if (srd_Y.step_delay <= srd_Y.min_delay) {
            srd_Y.step_delay = srd_Y.min_delay;
            srd_Y.run_state = RUN;
        } else {
            srd_Y.run_state = ACCEL;
        }
				if (stepPosition == step)
				{
					srd_Y.run_state = STOP;
				}
				
        srd_Y.accel_count = 0;
				TIM_SetAutoreload(TIM2, srd_Y.step_delay - 1);
				uint32_t tim_count = TIM_GetCounter(TIM2);  
				TIM_SetCompare1(TIM2, srd_Y.step_delay / 2 - 1);  				
				TIM_Cmd(TIM2, ENABLE); 
			}
    }
}

/**
  * @brief  速度决策1
	*	@note 	在中断中使用，每进一次中断，决策一次
  * @retval 无
  */
void speed_decision_Y(void)
{
    uint16_t new_step_delay = 0;
    static uint16_t last_accel_delay = 0;
    static uint32_t step_count = 0;
    static int32_t rest = 0;

    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 

        TIM_SetCompare1(TIM2, srd_Y.step_delay / 2); 				
				TIM_SetAutoreload(TIM2, srd_Y.step_delay);

        switch (srd_Y.run_state)
        {
            case STOP:
                step_count = 0;  
                rest = 0;        
								TIM2->CCER &= ~(1<<12);								
								TIM_Cmd(TIM2, DISABLE);
								break;
            case ACCEL:
								StepCounter_Y(srd_Y.dir);							
								TIM2->CCER |= 1<<12;	
                step_count++;
                srd_Y.accel_count++;
								
                new_step_delay = srd_Y.step_delay - (((2 * srd_Y.step_delay) + rest) / (4 * srd_Y.accel_count + 1)); 
                rest = ((2 * srd_Y.step_delay) + rest) % (4 * srd_Y.accel_count + 1);  

                if (step_count >= srd_Y.decel_start)
                {
                    srd_Y.accel_count = srd_Y.decel_val;
										srd_Y.run_state = DECEL;
                }
                else if (new_step_delay <= srd_Y.min_delay)
                {
                    last_accel_delay = new_step_delay;
                    new_step_delay = srd_Y.min_delay;
                    rest = 0;
										srd_Y.run_state = RUN;
                }
                break;

            case RUN:
								StepCounter_Y(srd_Y.dir);	
								TIM2->CCER |= 1<<12;	
                step_count++;
                new_step_delay = srd_Y.min_delay;
								
                if (step_count >= srd_Y.decel_start)
                {
                    srd_Y.accel_count = srd_Y.decel_val;
                    new_step_delay = last_accel_delay;
                    srd_Y.run_state = DECEL;
                }
                break;

            case DECEL:
								StepCounter_Y(srd_Y.dir);	
								TIM2->CCER |= 1<<12;	
                step_count++;
                srd_Y.accel_count++;
                new_step_delay = srd_Y.step_delay - (((2 * srd_Y.step_delay) + rest) / (4 * srd_Y.accel_count + 1)); 
                rest = ((2 * srd_Y.step_delay) + rest) % (4 * srd_Y.accel_count + 1);  

                if (srd_Y.accel_count >= 0)
                {
                    srd_Y.run_state = STOP;
                }
                break;
        }
        srd_Y.step_delay = new_step_delay;
    }
}

void StepCounter_Y(signed char inc)
{
	if(inc == CCW)
	{
		stepPosition_Y++;
	}
	else
	{
		stepPosition_Y--;
	}
}

void DIR_Y(uint8_t a)
{
	if(a == CW)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_11);    		
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_11);		
	
	}
}
