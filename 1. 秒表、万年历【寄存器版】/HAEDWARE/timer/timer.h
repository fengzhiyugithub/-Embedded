/****************定时器********************
* 
*******************************************/

#ifndef _TIMER_H
#define _TIMER_H

#include "sys.h"
#include "delay.h"
#include "led.h"

void TimerxInit(u16 arr, u16 psc); //定时器初始化
void TimerxInit2(u16 arr, u16 psc); //定时器初始化(用于万年历试验)
void DisplayDigitalClock(u8 hour, u8 minute, u8 second); //显示数字时钟

void DisplayCalendar(); //显示日历日�
void JudgeDay();// 对天数的合法性操作
void DisplayDigitalClock2();//显示数字时钟

#endif



