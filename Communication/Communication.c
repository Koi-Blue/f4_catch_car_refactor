#include "system.h"

uint8_t Serial_RxFlag;
int8_t QR_Code[] = {0, 0, 0, 0, 0, 0};  //A(帧头)  A(数据验证位)  1 2 3  3 2 1 E(帧尾)
uint8_t WuKuai;	 //A(帧头)  B(数据验证位)  1 E(帧尾)
uint8_t SeHuan;	 //A(帧头)  C(数据验证位)  1 E(帧尾)
//char Data_Verify;


void USART1_Init(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	 //Enable the gpio clock //使能GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //Enable the Usart clock //使能USART时钟

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9, GPIO_AF_USART1);	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10, GPIO_AF_USART1);	 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;            //输出模式
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;          //推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;       //高速50MHZ
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;            //上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);  		          //初始化
	
  //UsartNVIC configuration //UsartNVIC配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	//Preempt priority //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	//Subpriority //子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		
	//Enable the IRQ channel //IRQ通道使能
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  //Initialize the VIC register with the specified parameters 
	//根据指定的参数初始化VIC寄存器	
	NVIC_Init(&NVIC_InitStructure);	
	
  //USART Initialization Settings 初始化设置
	USART_InitStructure.USART_BaudRate = bound; //Port rate //串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //The word length is 8 bit data format //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //A stop bit //一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No; //Prosaic parity bits //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //No hardware data flow control //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//Sending and receiving mode //收发模式
	USART_Init(USART1, &USART_InitStructure); //Initialize serial port 1 //初始化串口1
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //Open the serial port to accept interrupts //开启串口接受中断
	USART_Cmd(USART1, ENABLE);                     //Enable serial port 1 //使能串口1
}

/**
  * 函    数：获取串口接收数据包标志位
  * 参    数：无
  * 返 回 值：串口接收数据包标志位，范围：0~1，接收到数据包后，标志位置1，读取后标志位自动清零
  */
uint8_t Serial_GetRxFlag(void)
{
	if (Serial_RxFlag == 1)			//如果标志位为1
	{
		Serial_RxFlag = 0;
		return 1;									//则返回1，并自动清零标志位
	}
	return 0;										//如果标志位为0，则返回0
}

/**
  * 函    数：USART1中断函数
  * 参    数：无
  * 返 回 值：无
  * 注意事项：此函数为中断函数，无需调用，中断触发后自动执行
  *           函数名为预留的指定名称，可以从启动文件复制
  *           请确保函数名正确，不能有任何差异，否则中断函数将不能进入
  */
	
int flag = 0;
static uint8_t RxState = 0;		//定义表示当前状态机状态的静态变量
static uint8_t pRxPacket = 0;	//定义表示当前接收数据位置的静态变量
static char Data_Verify;
//void USART1_IRQHandler(void)
//{

//	
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//判断是否是USART1的接收事件触发的中断
//	{
//		uint8_t RxData = USART_ReceiveData(USART1);				//读取数据寄存器，存放在接收的数据变量
//		
//		/*使用状态机的思路，依次处理数据包的不同部分*/
//		
//		/*当前状态为0，接收数据包包头*/
//		if (RxState == 0)
//		{
//			if (RxData == 0xFF)			//如果数据确实是包头
//			{
//				RxState = 1;			//置下一个状态
//				pRxPacket = 0;			//数据包的位置归零
//				flag = 1;
//			}
//		}
//		/*当前状态为1，接收数据包数据*/

//		else if (RxState == 1)
//		{
//			if(flag == 1)
//			{
//				Data_Verify = RxData;
//				flag  = 0;
//				pRxPacket = 0;
//				RxData = 0;
//		  }
//			else
//			{
//				switch(Data_Verify)
//				{
//					case 0x5A: 
//					QR_Code[pRxPacket] = RxData;
//					pRxPacket ++; 
//					if (pRxPacket >=6) 
//					{
//						RxState = 2; 
//						Data_Verify = 0;
//					}
//					break;
//					
//					
//					
//					case 0x5B:   
//					WuKuai = RxData; 
//					pRxPacket ++; 
//					if (pRxPacket > 0)  
//					{
//						RxState = 2;
//						Data_Verify = 0;
//					} 
//					
//					break;
//					
//					case 0x5C:   
//							SeHuan = (int)(RxData);
//							pRxPacket ++;  
//							if (pRxPacket > 0) 
//							{RxState = 2; Data_Verify = 0;} 
//					break;
//				}
//			}
//		}
//		/*当前状态为2，接收数据包包尾*/
//		else if (RxState == 2)
//		{
//			if (RxData == 0xFE)			//如果数据确实是包尾部
//			{
//				RxState = 0;			//状态归0
//				Serial_RxFlag = 1;		//接收数据包标志位置1，成功接收一个数据包
//			}
//		}
//		else
//		{
//			pRxPacket = 0;
//			RxState = 0;			//状态归0
//			Serial_RxFlag = 0;		//接收数据包标志位置1，成功接收一个数据包
//		
//		}
//		
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		//清除标志位
//	}
//}

void USART1_IRQHandler(void)
{

	
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//判断是否是USART1的接收事件触发的中断
	{
		uint8_t RxData = USART_ReceiveData(USART1);				//读取数据寄存器，存放在接收的数据变量
		
		/*使用状态机的思路，依次处理数据包的不同部分*/
		
		/*当前状态为0，接收数据包包头*/
		if (RxState == 0)
		{
			if (RxData == 'A')			//如果数据确实是包头
			{
				RxState = 1;			//置下一个状态
				pRxPacket = 0;			//数据包的位置归零
				flag = 1;
			}
		}
		/*当前状态为1，接收数据包数据*/

		else if (RxState == 1)
		{
			if(flag == 1)
			{
				Data_Verify = RxData;
				flag  = 0;
				pRxPacket = 0;
				RxData = 0;
		  }
			else
			{
				switch(Data_Verify)
				{
					case 'A': 
					QR_Code[pRxPacket] = RxData;
					pRxPacket ++; 
					if (pRxPacket >5) 
					{
						RxState = 2; 
						Data_Verify = 0;
					}
					break;					
					case 'B':   
					WuKuai = RxData; 
					pRxPacket ++; 
					if (pRxPacket > 0)  
					{
						RxState = 2;
						Data_Verify = 0;
					} 					
					break;
					
					case 'C':   
							SeHuan = RxData;
							pRxPacket ++;  
							if (pRxPacket > 0) 
							{
								RxState = 2; 
								Data_Verify = 0;
							} 
					break;
				}
			}
		}
		/*当前状态为2，接收数据包包尾*/
		else if (RxState == 2)
		{
			if (RxData == 'E')			//如果数据确实是包尾部
			{
				RxState = 0;			//状态归0
				Serial_RxFlag = 1;		//接收数据包标志位置1，成功接收一个数据包
			}
		}
		else
		{
			pRxPacket = 0;
			RxState = 0;			//状态归0
			Serial_RxFlag = 0;		//接收数据包标志位置1，成功接收一个数据包
		
		}
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		//清除标志位
	}
}

/**
  * ?    ?:????????
  * ?    ?:Byte ????????
  * ? ? ?:?
  */
void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);		//????????????,???USART????????
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	//??????
	/*?????????????????????,?????,???????*/
}

/**
  * ?    ?:????????
  * ?    ?:Array ?????????
  * ?    ?:Length ????????
  * ? ? ?:?
  */
//void Serial_SendArray(uint8_t *Array, uint16_t Length)
//{
//	uint16_t i;
//	for (i = 0; i < Length; i ++)		//????
//	{
//		Serial_SendByte(Array[i]);		//????Serial_SendByte????????
//	}
//}

///**
//  * ?    ?:?????????
//  * ?    ?:String ??????????
//  * ? ? ?:?
//  */
//void Serial_SendString(char *String)
//{
//	uint8_t i;
//	for (i = 0; String[i] != '\0'; i ++)//??????(???),?????????????
//	{
//		Serial_SendByte(String[i]);		//????Serial_SendByte????????
//	}
//}

/**
  * ?    ?:????(????)
  * ? ? ?:?????X?Y??
  */
//uint32_t Serial_Pow(uint32_t X, uint32_t Y)
//{
//	uint32_t Result = 1;	//???????1
//	while (Y --)			//??Y?
//	{
//		Result *= X;		//?X?????
//	}
//	return Result;
//}

/**
  * ?    ?:??????
  * ?    ?:Number ??????,??:0~4294967295
  * ?    ?:Length ????????,??:0~10
  * ? ? ?:?
  */
//void Serial_SendNumber(uint32_t Number, uint8_t Length)
//{
//	uint8_t i;
//	for (i = 0; i < Length; i ++)		//??????????????
//	{
//		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');	//????Serial_SendByte??????
//	}
//}

///**
//  * ?    ?:??printf??????????
//  * ?    ?:????????,????
//  * ? ? ?:????????,????
//  */
//int fputc(int ch, FILE *f)
//{
//	Serial_SendByte(ch);			//?printf????????????????
//	return ch;
//}

///**
//  * ?    ?:?????prinf??
//  * ?    ?:format ??????
//  * ?    ?:... ???????
//  * ? ? ?:?
//  */
//void Serial_Printf(char *format, ...)
//{
//	char String[100];				//??????
//	va_list arg;					//???????????????arg
//	va_start(arg, format);			//?format??,???????arg??
//	vsprintf(String, format, arg);	//??vsprintf???????????????????
//	va_end(arg);					//????arg
//	Serial_SendString(String);		//????????(???)
//}

void USART3_Init(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	 //Enable the gpio clock //使能GPIO时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //Enable the Usart clock //使能USART时钟

	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8, GPIO_AF_USART3);	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9, GPIO_AF_USART3);	 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;            //输出模式
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;          //推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;       //高速50MHZ
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;            //上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);  		          //初始化
	
  //UsartNVIC configuration //UsartNVIC配置
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	//Preempt priority //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;
	//Subpriority //子优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		
	//Enable the IRQ channel //IRQ通道使能
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
  //Initialize the VIC register with the specified parameters 
	//根据指定的参数初始化VIC寄存器	
	NVIC_Init(&NVIC_InitStructure);	
	
  //USART Initialization Settings 初始化设置
	USART_InitStructure.USART_BaudRate = bound; //Port rate //串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //The word length is 8 bit data format //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //A stop bit //一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No; //Prosaic parity bits //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //No hardware data flow control //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//Sending and receiving mode //收发模式
	USART_Init(USART3, &USART_InitStructure); //Initialize serial port 1 //初始化串口1
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); //Open the serial port to accept interrupts //开启串口接受中断
	USART_Cmd(USART3, ENABLE);                     //Enable serial port 1 //使能串口1
}

/**
  * 函    数：获取串口接收数据包标志位
  * 参    数：无
  * 返 回 值：串口接收数据包标志位，范围：0~1，接收到数据包后，标志位置1，读取后标志位自动清零
  */
uint8_t Serial_GetRxFlag3(void)
{
	if (Serial_RxFlag == 1)			//如果标志位为1
	{
		Serial_RxFlag = 0;
		return 1;									//则返回1，并自动清零标志位
	}
	return 0;										//如果标志位为0，则返回0
}

/**
  * 函    数：USART1中断函数
  * 参    数：无
  * 返 回 值：无
  * 注意事项：此函数为中断函数，无需调用，中断触发后自动执行
  *           函数名为预留的指定名称，可以从启动文件复制
  *           请确保函数名正确，不能有任何差异，否则中断函数将不能进入
  */
	
//int flag = 0;
//static uint8_t RxState = 0;		//定义表示当前状态机状态的静态变量
//static uint8_t pRxPacket = 0;	//定义表示当前接收数据位置的静态变量
//static char Data_Verify;
//void USART1_IRQHandler(void)
//{

//	
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)		//判断是否是USART1的接收事件触发的中断
//	{
//		uint8_t RxData = USART_ReceiveData(USART1);				//读取数据寄存器，存放在接收的数据变量
//		
//		/*使用状态机的思路，依次处理数据包的不同部分*/
//		
//		/*当前状态为0，接收数据包包头*/
//		if (RxState == 0)
//		{
//			if (RxData == 0xFF)			//如果数据确实是包头
//			{
//				RxState = 1;			//置下一个状态
//				pRxPacket = 0;			//数据包的位置归零
//				flag = 1;
//			}
//		}
//		/*当前状态为1，接收数据包数据*/

//		else if (RxState == 1)
//		{
//			if(flag == 1)
//			{
//				Data_Verify = RxData;
//				flag  = 0;
//				pRxPacket = 0;
//				RxData = 0;
//		  }
//			else
//			{
//				switch(Data_Verify)
//				{
//					case 0x5A: 
//					QR_Code[pRxPacket] = RxData;
//					pRxPacket ++; 
//					if (pRxPacket >=6) 
//					{
//						RxState = 2; 
//						Data_Verify = 0;
//					}
//					break;
//					
//					
//					
//					case 0x5B:   
//					WuKuai = RxData; 
//					pRxPacket ++; 
//					if (pRxPacket > 0)  
//					{
//						RxState = 2;
//						Data_Verify = 0;
//					} 
//					
//					break;
//					
//					case 0x5C:   
//							SeHuan = (int)(RxData);
//							pRxPacket ++;  
//							if (pRxPacket > 0) 
//							{RxState = 2; Data_Verify = 0;} 
//					break;
//				}
//			}
//		}
//		/*当前状态为2，接收数据包包尾*/
//		else if (RxState == 2)
//		{
//			if (RxData == 0xFE)			//如果数据确实是包尾部
//			{
//				RxState = 0;			//状态归0
//				Serial_RxFlag = 1;		//接收数据包标志位置1，成功接收一个数据包
//			}
//		}
//		else
//		{
//			pRxPacket = 0;
//			RxState = 0;			//状态归0
//			Serial_RxFlag = 0;		//接收数据包标志位置1，成功接收一个数据包
//		
//		}
//		
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		//清除标志位
//	}
//}

void USART3_IRQHandler(void)
{

	
	if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)		//判断是否是USART1的接收事件触发的中断
	{
		uint8_t RxData = USART_ReceiveData(USART3);				//读取数据寄存器，存放在接收的数据变量
		
		/*使用状态机的思路，依次处理数据包的不同部分*/
		
		/*当前状态为0，接收数据包包头*/
		if (RxState == 0)
		{
			if (RxData == 'A')			//如果数据确实是包头
			{
				RxState = 1;			//置下一个状态
				pRxPacket = 0;			//数据包的位置归零
				flag = 1;
			}
		}
		/*当前状态为1，接收数据包数据*/

		else if (RxState == 1)
		{
			if(flag == 1)
			{
				Data_Verify = RxData;
				flag  = 0;
				pRxPacket = 0;
				RxData = 0;
		  }
			else
			{
				switch(Data_Verify)
				{
					case 'A': 
					QR_Code[pRxPacket] = RxData;
					pRxPacket ++; 
					if (pRxPacket >5) 
					{
						RxState = 2; 
						Data_Verify = 0;
					}
					break;					
					case 'B':   
					WuKuai = RxData; 
					pRxPacket ++; 
					if (pRxPacket > 0)  
					{
						RxState = 2;
						Data_Verify = 0;
					} 					
					break;
					
					case 'C':   
							SeHuan = RxData;
							pRxPacket ++;  
							if (pRxPacket > 0) 
							{RxState = 2; Data_Verify = 0;} 
					break;
				}
			}
		}
		/*当前状态为2，接收数据包包尾*/
		else if (RxState == 2)
		{
			if (RxData == 'E')			//如果数据确实是包尾部
			{
				RxState = 0;			//状态归0
				Serial_RxFlag = 1;		//接收数据包标志位置1，成功接收一个数据包
			}
		}
		else
		{
			pRxPacket = 0;
			RxState = 0;			//状态归0
			Serial_RxFlag = 0;		//接收数据包标志位置1，成功接收一个数据包
		
		}
		
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);		//清除标志位
	}
}

/**
  * ?    ?:????????
  * ?    ?:Byte ????????
  * ? ? ?:?
  */
void Serial_SendByte3(uint8_t Byte)
{
	USART_SendData(USART3, Byte);		//????????????,???USART????????
	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);	//??????
	/*?????????????????????,?????,???????*/
}
