#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "pwm.h"

int main(void)
{ 
 
	u8 len;	    //�������ݵĸ���
	u16 times=0;  
	u16 led0pwmval=0; //��һ·pwm�ź�ռ�ձ�
  u16 led1pwmval=0; //�ڶ�·pwm�ź�ռ�ձ�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʱ��ʼ�� 
	TIM3_PWM_Init(200-1,8400-1);	//84M/8400=0.01Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 0.01M/200=50hz. 
	uart_init(115200);	//���ڳ�ʼ��������Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�  
	while(1)
	{
		if(USART_RX_STA&0x8000)  //�Ƿ����������ɣ�1000��0000�� 0000�� 0000��
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ��ȣ�0011�� 1111�� 1111�� 1111��
			if(len==2)   //ֻ�е��Է��͵���2������ʱ����ִ�в���
			{
				led0pwmval = USART_RX_BUF[0];
				led1pwmval = USART_RX_BUF[1];
				TIM_SetCompare1(TIM3,led0pwmval);	//�޸ıȽ�ֵ���޸�ռ�ձ�
				TIM_SetCompare2(TIM3,led1pwmval);	//�޸ıȽ�ֵ���޸�ռ�ձ�
				USART_RX_STA=0;   //���������ݣ�������ݽ������־
				printf("\r\n����������\r\n");
			}
			else{
					printf("\r\n�������������������!\r\n");
				USART_RX_STA=0;   //���������ݣ�������ݽ������־
			}
		}else
		{
			times++;
			if(times%5000==0)
			{
				printf("\r\nALIENTEK ̽����STM32F407������ ����ʵ��\r\n");
				printf("����ԭ��@ALIENTEK\r\n\r\n\r\n");
			}
			if(times%200==0)printf("����������,�Իس�������\r\n");  
			if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
			delay_ms(10);   
		}
	}
}

