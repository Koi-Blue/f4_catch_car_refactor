#ifndef __ACTION_H
#define __ACTION_H

#include "stm32f4xx.h"  

void Grab_1(void);	//从色环抓取物块
void Grab_2(void);	//从色环抓取物块
void Grab_3(void);	//从色环抓取物块

void Place_1(void);	//将物块放置在色环中
void Place_2(void);	//将物块放置在色环中
void Place_3(void);	//将物块放置在色环中

void Pile_1(void); //放置在物块上
void Pile_2(void); //放置在物块上
void Pile_3(void); //放置在物块上

void Grab_11(void);	//从色环抓取物块
void Grab_22(void);	//从色环抓取物块
void Grab_33(void);	//从色环抓取物块

void Place_11(void);	//将物块放置在色环中
void Place_22(void);	//将物块放置在色环中
void Place_33(void);	//将物块放置在色环中

void Place_13(void);	//将物块放置在色环中
void Place_23(void);	//将物块放置在色环中
void Place_32(void);	//将物块放置在色环中


#endif
