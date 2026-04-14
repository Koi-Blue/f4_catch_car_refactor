#include "system.h"

struct STime				stcTime;
struct SAcc 				stcAcc;
struct SGyro 				stcGyro;
struct SAngle 	    stcAngle;
struct SMag 				stcMag;
struct SDStatus     stcDStatus;
struct SPress 	    stcPress;
struct SLonLat 	    stcLonLat;
struct SGPSV 				stcGPSV;
struct SQ           stcQ;

char ACCCALSW[5] = {0XFF,0XAA,0X01,0X01,0X00};  // 进入加速度校准模式
char SAVACALSW[5]= {0XFF,0XAA,0X00,0X00,0X00};  // 保存当前配置



// JY901数据
static unsigned char TxBuffer[256];
static unsigned char TxCounter=0;
static unsigned char count=0; 
extern void CopeSerial2Data(unsigned char ucData);

void USART5_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource13, GPIO_AF_UART5);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(UART5, &USART_InitStructure);
	
	USART_Cmd(UART5, ENABLE);
	
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//开启相关中断
  USART_ClearFlag(USART2,USART_FLAG_TC);

	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	//Usart3 NVIC 配置
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;//串口3中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
}

// USART3 串口接收中断
void UART5_IRQHandler(void)
{
    if(USART_GetITStatus(UART5, USART_IT_TXE) != RESET)
    {   
        USART_SendData(UART5, TxBuffer[TxCounter++]); 
        USART_ClearITPendingBit(UART5, USART_IT_TXE);
        if(TxCounter == count) USART_ITConfig(UART5, USART_IT_TXE, DISABLE);
    }
	else if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
    {
		CopeSerial2Data((unsigned char)UART5->DR);//处理数据
		USART_ClearITPendingBit(UART5, USART_IT_RXNE);
    }
	
	USART_ClearITPendingBit(UART5,USART_IT_ORE);
}


void UART2_Put_Char(unsigned char DataToSend)
{
	TxBuffer[count++] = DataToSend;  
  USART_ITConfig(UART5, USART_IT_TXE, ENABLE);  
}

void UART2_Put_String(unsigned char *Str)
{
	while(*Str)
	{
		if(*Str=='\r')UART2_Put_Char(0x0d);
			else if(*Str=='\n')UART2_Put_Char(0x0a);
				else UART2_Put_Char(*Str);
		Str++;
	}
}



//用串口2给JY模块发送指令
void sendcmd(char cmd[])
{
	char i;
	for(i=0;i<5;i++)
		UART2_Put_Char(cmd[i]);
}


// CopeSerialData为串口2中断调用函数，串口每收到一个数据，调用一次这个函数。
void CopeSerial2Data(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	
	ucRxBuffer[ucRxCnt++]=ucData;	//将收到的数据存入缓冲区中
	if (ucRxBuffer[0]!=0x55)        //数据头不对，则重新开始寻找0x55数据头
	{
		ucRxCnt=0;
		return;
	}
    
	if (ucRxCnt<11) {return;}//数据不满11个，则返回
	else
	{
		switch(ucRxBuffer[1])//判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
		{
			case 0x50:	memcpy(&stcTime,&ucRxBuffer[2],8);      break;  //memcpy为编译器自带的内存拷贝函数，需引用"string.h"，将接收缓冲区的字符拷贝到数据结构体里面，从而实现数据的解析。
			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);       break;
			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);      break;
			case 0x53:	memcpy(&stcAngle,&ucRxBuffer[2],8);     break;
			case 0x54:	memcpy(&stcMag,&ucRxBuffer[2],8);       break;
			case 0x55:	memcpy(&stcDStatus,&ucRxBuffer[2],8);   break;
			case 0x56:	memcpy(&stcPress,&ucRxBuffer[2],8);     break;
			case 0x57:	memcpy(&stcLonLat,&ucRxBuffer[2],8);    break;
			case 0x58:	memcpy(&stcGPSV,&ucRxBuffer[2],8);      break;
			case 0x59:	memcpy(&stcQ,&ucRxBuffer[2],8);         break;
		}
		ucRxCnt=0;//清空缓存区
	}
}

void CopeSerial1Data(unsigned char ucData)
{	
	UART2_Put_Char(ucData);//转发串口1收到的数据给串口2（JY模块）
}

void Receive_Gyro(void)			//串口获取角度值
{
	Receive_Roll	= (float)stcAngle.Angle[0]/32768*180;
	Receive_Pitch = (float)stcAngle.Angle[1]/32768*180;
	Receive_Yaw 	= (float)stcAngle.Angle[2]/32768*180;
}
