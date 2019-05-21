/****************定时器实现********************
* 功能1：实现秒表功能（KEY1按下开始计时，KEY按一次表示记录当前时间，KEY3表示终止计时）
*		 			停止计时后，KEY2、KEY3翻看时间
* 功能2：实现万年历功能
*        能显示年、月、日 或 时、分、秒，通过按键切换显示内容，按键可以调整和设置日期和时间
* Modified by fzhiy at 22:00, 5/20/2019.
***************************************************/

#include "timer.h"
#include "key.h"
#define MAXN 1000 //设置秒表记录的最大次数

//数字钟的时，分、秒
u8 hour = 0, minute = 0, second = 0, count = 0, t = 0, actCount;
u8 timeRec[3][MAXN];  //记录5个时间的时分秒 timeRec[0][count]表示时,timeRec[1][count]表示分,timeRec[2][count]表示秒
u8 month[12]={31,28,31,30,31,30,31,31,30,31,30,31};
u32 day = 21, year = 2019, curMonth = 5;      //默认为2019-5-21 00-00-00


/*
/// 注释部分为功能2【万年历】部分的代码
// 判断是否为闰年
int IsLeapYear(int year){
	if((year%4 == 0 && year%100 != 0) || year %400 == 0){
		return 1;
	}
	return 0;
}

// 对day++的合法性做判断
void JudgeDay(){  
						int i;
						for(i=0; i<12; i++){
							if(i==0||i==2||i==4||i==6||i==7||i==9||i==11){ //31天的月份
								if((day>31)&&(curMonth==i)){
									day=1;
									curMonth++;
									if(curMonth==13){
										curMonth=1;
										year++;
									}
								}
							}else if(i==1){
									if(day>28&&(curMonth==2)){  //2月
										if(IsLeapYear(year)==0){ //且不是闰年
											day=1;
											curMonth=3;
										}
									}
								}else { // 30的月份
									if((day>30)&&(curMonth==i+1)){
										day=1;
										curMonth++;
									}
								}
							}
}

// 对day--的合法性的操作
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
		if( TIM3->SR & 0x0001) //溢出中断
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
		TIM3->SR &= ~(1<<0); //清除中断标志位
}

// 处理按键3切换时间和日期的终端函数
void EXTI0_IRQHandler(void){
	u8 t , cnt = 0;
	delay_ms(10);//消抖
	if(key3==0){	//按键3
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
		if(t==2){// 加操作
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
		}else if(t==1){// 减操作
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
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
}
*/


/****************普通按键初始化函数（用于万年历实验）********************
* 通用定时器中断初始化
* 这里时钟选择为APB1的2倍，而APB1为36M
* arr：自动重装值。
* psc：时钟预分频数
* 这里使用的是定时器3!
******************************************************/
void TimerxInit2(u16 arr, u16 psc){
	RCC->APB1ENR |= 1<<1; //TIM3时钟使能
	TIM3->ARR = arr;      //设定计数器自动重装值，10为1ms
	TIM3->PSC = psc;      //预分频器7200，得到10KHZ的计数时钟
	
	TIM3->DIER |= 1<<0;   //允许更新中断
	TIM3->CR1 |= 0x01;    //使能定时器3
	
	MY_NVIC_Init(1, 3, TIM3_IRQChannel, 2); //抢占1，子优先级3，组2
	
	// 配置按键外部中断
	RCC->APB2ENR|=1<<4;     //使能PORTC时钟
	GPIOC->CRL&=0XFFFFF000;//PC0-2设置成输入	  
	GPIOC->CRL|=0X00000888;
	
	Ex_NVIC_Config(GPIO_C,0,FTIR);//下降沿触发
	Ex_NVIC_Config(GPIO_C,1,FTIR);//下降沿触发
	Ex_NVIC_Config(GPIO_C,2,FTIR);//下降沿触发

	MY_NVIC_Init(0,2,EXTI0_IRQChannel,2);//抢占2，子优先级2，组2
}

/************************************************
* 						显示日期
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


/****************普通按键初始化函数********************
* 通用定时器中断初始化
* 这里时钟选择为APB1的2倍，而APB1为36M
* arr：自动重装值。
* psc：时钟预分频数
* 这里使用的是定时器3!
******************************************************/
void TimerxInit(u16 arr, u16 psc)
{
	RCC->APB1ENR |= 1<<1; //TIM3时钟使能
	TIM3->ARR = arr;      //设定计数器自动重装值，10为1ms
	TIM3->PSC = psc;      //预分频器7200，得到10KHZ的计数时钟
	
	TIM3->DIER |= 1<<0;   //允许更新中断
	TIM3->CR1 |= 0x01;    //使能定时器3
	
	MY_NVIC_Init(1, 3, TIM3_IRQChannel, 2); //抢占1，子优先级3，组2

	RCC->APB2ENR|=1<<4;     //使能PORTC时钟
	GPIOC->CRL&=0XFFFFF000;//PC0-2设置成输入	  
	GPIOC->CRL|=0X00000888;
	
	Ex_NVIC_Config(GPIO_C,0,FTIR);//下降沿触发
	Ex_NVIC_Config(GPIO_C,1,FTIR);//下降沿触发
	Ex_NVIC_Config(GPIO_C,2,FTIR);//下降沿触发

	MY_NVIC_Init(0,2,EXTI0_IRQChannel,2);//抢占2，子优先级2，组2
	MY_NVIC_Init(2,2,EXTI2_IRQChannel,2);//抢占2，子优先级1，组2
}

void EXTI2_IRQHandler(void){
	delay_ms(10);//消抖
	if(key1==0){	//按键1
		key1=1;
		second = 0;
		minute = 0;
		hour = 0;
		while(1){
			DisplayDigitalClock(hour, minute, second);
			delay_ms(10);//消抖
			t=KeyScan();
			if(t==2){	
				timeRec[0][count] = hour;
				timeRec[1][count] = minute;
				timeRec[2][count] = second;
				count++; // 记录时间个数+1
				actCount = count-1; //actCount表示实际记录的时间个数
				EXTI->PR=1<<1;  //清除LINE1上的中断标志位  
			}
		}
	}
	EXTI->PR=1<<2;  //清除LINE2上的中断标志位  
}

void EXTI0_IRQHandler(void){
	delay_ms(10);//消抖
	if(key3==0){	//按键3
		while(1){
			DisplayDigitalClock(hour, minute, second);	//计时停在当前计时时间
			t=KeyScan();
			if(t==2){						//先翻看前一个记录时间
				while(1){
					DisplayDigitalClock(timeRec[0][count], timeRec[1][count], timeRec[2][count]);
					if(t==2){
						if(count>0){	//判断记录下限
								--count;
						}
						EXTI->PR=1<<1;//清除LINE1上的中断标志位  
					}
					if(t==3){
						if(count<actCount){ //判断记录上限
								++count;
						}
						EXTI->PR=1<<0;//清除LINE0上的中断标志位  
					}
					t=KeyScan();
				}
			}
		}
	}
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
}


/****************定时器3的中断函数********************
* 定时器3的中断函数
* 每次中断，second加一
******************************************************/

void TIM3_IRQHandler( void )
{
		if( TIM3->SR & 0x0001) //溢出中断
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
		TIM3->SR &= ~(1<<0); //清除中断标志位
}

/*****************************************************
* 数字钟显示函数
******************************************************/
void DisplayDigitalClock(u8 hour, u8 minute, u8 second)
{
	SetLed(0, hour/10);  //显示 时
	delay_ms(1);
	SetLed(1, hour%10);
	delay_ms(1);
	SetLed(2, 10);        //显示"-"符号
	delay_ms(1);
	SetLed(3, minute/10); //显示 分
	delay_ms(1);
	SetLed(4, minute%10);
	delay_ms(1);
	SetLed(5, 10);        //显示"-"符号
	delay_ms(1);
	SetLed(6, second/10); //显示 秒
	delay_ms(1);
	SetLed(7, second%10);
	delay_ms(1);
}

void DisplayDigitalClock2()
{
	SetLed(0, hour/10);  //显示 时
	delay_ms(1);
	SetLed(1, hour%10);
	delay_ms(1);
	SetLed(2, 10);        //显示"-"符号
	delay_ms(1);
	SetLed(3, minute/10); //显示 分
	delay_ms(1);
	SetLed(4, minute%10);
	delay_ms(1);
	SetLed(5, 10);        //显示"-"符号
	delay_ms(1);
	SetLed(6, second/10); //显示 秒
	delay_ms(1);
	SetLed(7, second%10);
	delay_ms(1);
}

