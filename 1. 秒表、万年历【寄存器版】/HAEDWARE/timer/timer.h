/****************��ʱ��********************
* 
*******************************************/

#ifndef _TIMER_H
#define _TIMER_H

#include "sys.h"
#include "delay.h"
#include "led.h"

void TimerxInit(u16 arr, u16 psc); //��ʱ����ʼ��
void TimerxInit2(u16 arr, u16 psc); //��ʱ����ʼ��(��������������)
void DisplayDigitalClock(u8 hour, u8 minute, u8 second); //��ʾ����ʱ��

void DisplayCalendar(); //��ʾ�������
void JudgeDay();// �������ĺϷ��Բ���
void DisplayDigitalClock2();//��ʾ����ʱ��

#endif



