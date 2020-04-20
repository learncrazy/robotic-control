#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"


//ALIENTEK ̽����STM32F407������ ʵ��9
//PWM���ʵ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

int main(void)
{ 
	u16 led0pwmval=0;   
  u16 led1pwmval=0;  	
	u8 dir=1;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);//��ʼ�����ڲ�����Ϊ115200
 	TIM3_PWM_Init(200-1,8400-1);	//84M/8400=0.01Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 0.01M/200=50hz. 
   //while(1) //ʵ�ֱȽ�ֵ��0-300��������300���300-0�ݼ���ѭ��
	{
 		delay_ms(10);	 
		//if(dir)led0pwmval+=10;//dir==1 led0pwmval����
		//else led0pwmval-=10;	//dir==0 led0pwmval�ݼ� 
 		//if(led0pwmval>2000)dir=0;//led0pwmval����300�󣬷���Ϊ�ݼ�
		//if(led0pwmval==500)dir=1;	//led0pwmval�ݼ���0�󣬷����Ϊ����
    led0pwmval=195;
		led1pwmval=175;
		TIM_SetCompare1(TIM3,led0pwmval);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		TIM_SetCompare2(TIM3,led1pwmval);	//�޸ıȽ�ֵ���޸�ռ�ձ�
	}
}
