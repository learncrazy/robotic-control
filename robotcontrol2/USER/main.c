#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "pwm.h"

int main(void)
{ 
 
	u8 len;	    //接受数据的个数
	u16 times=0;  
	u16 led0pwmval=0; //第一路pwm信号占空比
  u16 led1pwmval=0; //第二路pwm信号占空比
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	TIM3_PWM_Init(200-1,8400-1);	//84M/8400=0.01Mhz的计数频率,重装载值500，所以PWM频率为 0.01M/200=50hz. 
	uart_init(115200);	//串口初始化波特率为115200
	LED_Init();		  		//初始化与LED连接的硬件接口  
	while(1)
	{
		if(USART_RX_STA&0x8000)  //是否接收数据完成（1000，0000， 0000， 0000）
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度（0011， 1111， 1111， 1111）
			if(len==2)   //只有电脑发送的是2个数据时，才执行操作
			{
				led0pwmval = USART_RX_BUF[0];
				led1pwmval = USART_RX_BUF[1];
				TIM_SetCompare1(TIM3,led0pwmval);	//修改比较值，修改占空比
				TIM_SetCompare2(TIM3,led1pwmval);	//修改比较值，修改占空比
				USART_RX_STA=0;   //处理完数据，清除数据接受完标志
				printf("\r\n处理数据中\r\n");
			}
			else{
					printf("\r\n输入参数错误，重新输入!\r\n");
				USART_RX_STA=0;   //处理完数据，清除数据接受完标志
			}
		}else
		{
			times++;
			if(times%5000==0)
			{
				printf("\r\nALIENTEK 探索者STM32F407开发板 串口实验\r\n");
				printf("正点原子@ALIENTEK\r\n\r\n\r\n");
			}
			if(times%200==0)printf("请输入数据,以回车键结束\r\n");  
			if(times%30==0)LED0=!LED0;//闪烁LED,提示系统正在运行.
			delay_ms(10);   
		}
	}
}

