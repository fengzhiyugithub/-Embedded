/****************¶¨Ê±Æ÷********************
* 
*******************************************/

#ifndef _TIMER_H
#define _TIMER_H

#include "sys.h"
#include "delay.h"
#include "led.h"

void TimerxInit(u16 arr, u16 psc); //¶¨Ê±Æ÷³õÊ¼»¯
void TimerxInit2(u16 arr, u16 psc); //¶¨Ê±Æ÷³õÊ¼»¯(ÓÃÓÚÍòÄêÀúÊÔÑé)
void DisplayDigitalClock(u8 hour, u8 minute, u8 second); //ÏÔÊ¾Êı×ÖÊ±ÖÓ

void DisplayCalendar(); //ÏÔÊ¾ÈÕÀúÈÕÆ
void JudgeDay();// ¶ÔÌìÊıµÄºÏ·¨ĞÔ²Ù×÷
void DisplayDigitalClock2();//ÏÔÊ¾Êı×ÖÊ±ÖÓ

#endif



