#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"


//ALIENTEK 探索者STM32F407开发板 实验9
//PWM输出实验-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

int main(void)
{ 
	u16 led0pwmval=0;   
  u16 led1pwmval=0;  	
	u8 dir=1;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);//初始化串口波特率为115200
 	TIM3_PWM_Init(200-1,8400-1);	//84M/8400=0.01Mhz的计数频率,重装载值500，所以PWM频率为 0.01M/200=50hz. 
   //while(1) //实现比较值从0-300递增，到300后从300-0递减，循环
	{
 		delay_ms(10);	 
		//if(dir)led0pwmval+=10;//dir==1 led0pwmval递增
		//else led0pwmval-=10;	//dir==0 led0pwmval递减 
 		//if(led0pwmval>2000)dir=0;//led0pwmval到达300后，方向为递减
		//if(led0pwmval==500)dir=1;	//led0pwmval递减到0后，方向改为递增
    led0pwmval=195;
		led1pwmval=175;
		TIM_SetCompare1(TIM3,led0pwmval);	//修改比较值，修改占空比
		TIM_SetCompare2(TIM3,led1pwmval);	//修改比较值，修改占空比
	}
}
