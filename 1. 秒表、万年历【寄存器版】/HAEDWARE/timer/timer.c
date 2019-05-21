/****************��ʱ��ʵ��********************
* ����1��ʵ������ܣ�KEY1���¿�ʼ��ʱ��KEY��һ�α�ʾ��¼��ǰʱ�䣬KEY3��ʾ��ֹ��ʱ��
*		 			ֹͣ��ʱ��KEY2��KEY3����ʱ��
* ����2��ʵ������������
*        ����ʾ�ꡢ�¡��� �� ʱ���֡��룬ͨ�������л���ʾ���ݣ��������Ե������������ں�ʱ��
* Modified by fzhiy at 22:00, 5/20/2019.
***************************************************/

#include "timer.h"
#include "key.h"
#define MAXN 1000 //��������¼��������

//�����ӵ�ʱ���֡���
u8 hour = 0, minute = 0, second = 0, count = 0, t = 0, actCount;
u8 timeRec[3][MAXN];  //��¼5��ʱ���ʱ���� timeRec[0][count]��ʾʱ,timeRec[1][count]��ʾ��,timeRec[2][count]��ʾ��
u8 month[12]={31,28,31,30,31,30,31,31,30,31,30,31};
u32 day = 21, year = 2019, curMonth = 5;      //Ĭ��Ϊ2019-5-21 00-00-00


/*
/// ע�Ͳ���Ϊ����2�������������ֵĴ���
// �ж��Ƿ�Ϊ����
int IsLeapYear(int year){
	if((year%4 == 0 && year%100 != 0) || year %400 == 0){
		return 1;
	}
	return 0;
}

// ��day++�ĺϷ������ж�
void JudgeDay(){  
						int i;
						for(i=0; i<12; i++){
							if(i==0||i==2||i==4||i==6||i==7||i==9||i==11){ //31����·�
								if((day>31)&&(curMonth==i)){
									day=1;
									curMonth++;
									if(curMonth==13){
										curMonth=1;
										year++;
									}
								}
							}else if(i==1){
									if(day>28&&(curMonth==2)){  //2��
										if(IsLeapYear(year)==0){ //�Ҳ�������
											day=1;
											curMonth=3;
										}
									}
								}else { // 30���·�
									if((day>30)&&(curMonth==i+1)){
										day=1;
										curMonth++;
									}
								}
							}
}

// ��day--�ĺϷ��ԵĲ���
void JudgeDay2(){
	int i;	
	if(day==0){
			for(i=0; i<12; i++){
				if(i==0||i==2||i==4||i==6||i==7||i==9||i==11){
						day=31;
				}else if(i==1){
					if(IsLeapYear(year)==1){
						day=29;
					}else {
						day=28;
					}
				}else {
					day=30;
				}
			}
		}
}

void TIM3_IRQHandler( void )
{
		if( TIM3->SR & 0x0001) //����ж�
		{
			second++;
			if( second>59 )
			{
				second = 0;
				minute++;
				if( minute>59 )
				{
					minute = 0;
					hour++;
					if( hour>23 )
					{
						hour = 0;
						day++;
						JudgeDay();
						}
					}
			}
		}
		TIM3->SR &= ~(1<<0); //����жϱ�־λ
}

// ������3�л�ʱ������ڵ��ն˺���
void EXTI0_IRQHandler(void){
	u8 t , cnt = 0;
	delay_ms(10);//����
	if(key3==0){	//����3
		while(1){
		t = KeyScan();
		if(t==3){
			cnt++;
			if(cnt==7){
				break;
			}
		}
		if(cnt>3){
			DisplayDigitalClock2();
		}else {
			DisplayCalendar(year, curMonth, day);
		}
		if(t==2){// �Ӳ���
			if(cnt==1){ // 
				year++;
			}else if(cnt==2){
				curMonth++;
				if(curMonth==13){
					curMonth=1;
					year++;
				}
			}else if(cnt==3){
					day++;
					JudgeDay();
				}else if(cnt>3){
					if(cnt==4){
					hour++;
					if( hour>23 ){
							hour = 0;
							day++;
							JudgeDay();
						}
					}else if(cnt==5){
						minute++;
						if( minute>59 ){
							minute = 0;
							hour++;
							if( hour>23 ){
								hour = 0;
								day++;
								JudgeDay();
							}
						}
					}else if(cnt==6){
						second++;
						if( second>59 )
						{
							second = 0;
							minute++;
							if( minute>59 )
							{
								minute = 0;
								hour++;
								if( hour>23 ){
									hour = 0;
									day++;
									JudgeDay();
								}
							}
						}
					}
				}
		}else if(t==1){// ������
			if(cnt==1) year--;
				else if(cnt==2){
				curMonth--;
				if(curMonth==0){
					curMonth=12;
					year--;
				}
			}else if(cnt==3){
					day--;
					JudgeDay2();
				}else if(cnt>3){
					if(cnt==4){
					if( hour==0 ){
							hour=23;
						}else {
							hour--;
						}
					}else if(cnt==5){
						if( minute==0 )minute=59;
						else minute--;
					}else if(cnt==6){
						if(second==0){	second=59;}
						else {	second--;	}
					}
				}
			}
		}
	}
	EXTI->PR=1<<0;  //���LINE0�ϵ��жϱ�־λ  
}
*/


/****************��ͨ������ʼ������������������ʵ�飩********************
* ͨ�ö�ʱ���жϳ�ʼ��
* ����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
* arr���Զ���װֵ��
* psc��ʱ��Ԥ��Ƶ��
* ����ʹ�õ��Ƕ�ʱ��3!
******************************************************/
void TimerxInit2(u16 arr, u16 psc){
	RCC->APB1ENR |= 1<<1; //TIM3ʱ��ʹ��
	TIM3->ARR = arr;      //�趨�������Զ���װֵ��10Ϊ1ms
	TIM3->PSC = psc;      //Ԥ��Ƶ��7200���õ�10KHZ�ļ���ʱ��
	
	TIM3->DIER |= 1<<0;   //��������ж�
	TIM3->CR1 |= 0x01;    //ʹ�ܶ�ʱ��3
	
	MY_NVIC_Init(1, 3, TIM3_IRQChannel, 2); //��ռ1�������ȼ�3����2
	
	// ���ð����ⲿ�ж�
	RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��
	GPIOC->CRL&=0XFFFFF000;//PC0-2���ó�����	  
	GPIOC->CRL|=0X00000888;
	
	Ex_NVIC_Config(GPIO_C,0,FTIR);//�½��ش���
	Ex_NVIC_Config(GPIO_C,1,FTIR);//�½��ش���
	Ex_NVIC_Config(GPIO_C,2,FTIR);//�½��ش���

	MY_NVIC_Init(0,2,EXTI0_IRQChannel,2);//��ռ2�������ȼ�2����2
}

/************************************************
* 						��ʾ����
************************************************/
void DisplayCalendar(){
	SetLed(0, year/1000);
	delay_ms(1);
	SetLed(1, year/100%10);
	delay_ms(1);
	SetLed(2, year/10%10);
	delay_ms(1);
	SetLed(3, year%10);
	delay_ms(1);
	SetLed(4, curMonth/10);
	delay_ms(1);
	SetLed(5, curMonth%10);
	delay_ms(1);
	SetLed(6, day/10);
	delay_ms(1);
	SetLed(7, day%10);
	delay_ms(1);
}

//=================================================================================


/****************��ͨ������ʼ������********************
* ͨ�ö�ʱ���жϳ�ʼ��
* ����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
* arr���Զ���װֵ��
* psc��ʱ��Ԥ��Ƶ��
* ����ʹ�õ��Ƕ�ʱ��3!
******************************************************/
void TimerxInit(u16 arr, u16 psc)
{
	RCC->APB1ENR |= 1<<1; //TIM3ʱ��ʹ��
	TIM3->ARR = arr;      //�趨�������Զ���װֵ��10Ϊ1ms
	TIM3->PSC = psc;      //Ԥ��Ƶ��7200���õ�10KHZ�ļ���ʱ��
	
	TIM3->DIER |= 1<<0;   //��������ж�
	TIM3->CR1 |= 0x01;    //ʹ�ܶ�ʱ��3
	
	MY_NVIC_Init(1, 3, TIM3_IRQChannel, 2); //��ռ1�������ȼ�3����2

	RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��
	GPIOC->CRL&=0XFFFFF000;//PC0-2���ó�����	  
	GPIOC->CRL|=0X00000888;
	
	Ex_NVIC_Config(GPIO_C,0,FTIR);//�½��ش���
	Ex_NVIC_Config(GPIO_C,1,FTIR);//�½��ش���
	Ex_NVIC_Config(GPIO_C,2,FTIR);//�½��ش���

	MY_NVIC_Init(0,2,EXTI0_IRQChannel,2);//��ռ2�������ȼ�2����2
	MY_NVIC_Init(2,2,EXTI2_IRQChannel,2);//��ռ2�������ȼ�1����2
}

void EXTI2_IRQHandler(void){
	delay_ms(10);//����
	if(key1==0){	//����1
		key1=1;
		second = 0;
		minute = 0;
		hour = 0;
		while(1){
			DisplayDigitalClock(hour, minute, second);
			delay_ms(10);//����
			t=KeyScan();
			if(t==2){	
				timeRec[0][count] = hour;
				timeRec[1][count] = minute;
				timeRec[2][count] = second;
				count++; // ��¼ʱ�����+1
				actCount = count-1; //actCount��ʾʵ�ʼ�¼��ʱ�����
				EXTI->PR=1<<1;  //���LINE1�ϵ��жϱ�־λ  
			}
		}
	}
	EXTI->PR=1<<2;  //���LINE2�ϵ��жϱ�־λ  
}

void EXTI0_IRQHandler(void){
	delay_ms(10);//����
	if(key3==0){	//����3
		while(1){
			DisplayDigitalClock(hour, minute, second);	//��ʱͣ�ڵ�ǰ��ʱʱ��
			t=KeyScan();
			if(t==2){						//�ȷ���ǰһ����¼ʱ��
				while(1){
					DisplayDigitalClock(timeRec[0][count], timeRec[1][count], timeRec[2][count]);
					if(t==2){
						if(count>0){	//�жϼ�¼����
								--count;
						}
						EXTI->PR=1<<1;//���LINE1�ϵ��жϱ�־λ  
					}
					if(t==3){
						if(count<actCount){ //�жϼ�¼����
								++count;
						}
						EXTI->PR=1<<0;//���LINE0�ϵ��жϱ�־λ  
					}
					t=KeyScan();
				}
			}
		}
	}
	EXTI->PR=1<<0;  //���LINE0�ϵ��жϱ�־λ  
}


/****************��ʱ��3���жϺ���********************
* ��ʱ��3���жϺ���
* ÿ���жϣ�second��һ
******************************************************/

void TIM3_IRQHandler( void )
{
		if( TIM3->SR & 0x0001) //����ж�
		{
			second++;
			if( second>59 )
			{
				second = 0;
				minute++;
				if( minute>59 )
				{
					minute = 0;
					hour++;
					if( hour>23 )
						hour = 0;
				}
			}
		}
		TIM3->SR &= ~(1<<0); //����жϱ�־λ
}

/*****************************************************
* ��������ʾ����
******************************************************/
void DisplayDigitalClock(u8 hour, u8 minute, u8 second)
{
	SetLed(0, hour/10);  //��ʾ ʱ
	delay_ms(1);
	SetLed(1, hour%10);
	delay_ms(1);
	SetLed(2, 10);        //��ʾ"-"����
	delay_ms(1);
	SetLed(3, minute/10); //��ʾ ��
	delay_ms(1);
	SetLed(4, minute%10);
	delay_ms(1);
	SetLed(5, 10);        //��ʾ"-"����
	delay_ms(1);
	SetLed(6, second/10); //��ʾ ��
	delay_ms(1);
	SetLed(7, second%10);
	delay_ms(1);
}

void DisplayDigitalClock2()
{
	SetLed(0, hour/10);  //��ʾ ʱ
	delay_ms(1);
	SetLed(1, hour%10);
	delay_ms(1);
	SetLed(2, 10);        //��ʾ"-"����
	delay_ms(1);
	SetLed(3, minute/10); //��ʾ ��
	delay_ms(1);
	SetLed(4, minute%10);
	delay_ms(1);
	SetLed(5, 10);        //��ʾ"-"����
	delay_ms(1);
	SetLed(6, second/10); //��ʾ ��
	delay_ms(1);
	SetLed(7, second%10);
	delay_ms(1);
}

