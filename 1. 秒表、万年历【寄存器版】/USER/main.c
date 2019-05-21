/******************************定时中断实现数字钟************************
* 数字钟
* 通过控制定时中断实现数字钟
******************************************************************/

#include "timer.h"
#include "key.h"

/***************************主函数*****************************/
int main()
{
//	u8 t;
	Stm32_Clock_Init( 6 ); 
	delay_init( 72 );
	TimerxInit( 10,7199 ); ////10Khz的计数频率，计数到10表示1ms
	//TimerxInit2( 10000,7199 ); ////10Khz的计数频率，计数到10000表示1s
	LED_Init();
	LED_SEL = 0;
	while(1)
	{
			DisplayDigitalClock(0,0,0);
			
		// 以下注释部分为功能2【万年历】的代码
		/*DisplayDigitalClock2();
			t = KeyScan();
			if(t==2){
				while(1){
					DisplayCalendar();
					t = KeyScan();
					if(t==1){
						break;
					}
				}
			}*/
	}	
}




