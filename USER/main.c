#include  "timer.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "103.h"
#include "led.h"
#include "beep.h"
#include "key.h"


volatile uint8_t  i;   //47--2017-7-3 19:07

//2017-7-4 16:17����OK ����2������



//VNC

int main(void)    //������϶�ʱ�������ж�  stm32-modbus���Ǹ�
{ 
    
	u8 t;
	u8 len;	
	u16 times=0;  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʱ��ʼ�� 
	//clearBuff();//�建��
	uart_init(115200);	//���ڳ�ʼ��������Ϊ115200--�����ٶȿ�
	//LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ� 
 // TIM3_Int_Init(500-1,8400-1);//500-1����ͨ��//50--//500//10//50//��ʱ��ʱ��84M����Ƶϵ��8400������84M/8400=10Khz�ļ���Ƶ�ʣ�����5000��Ϊ500ms 
	
 	printf("AT\r\n");//�ȷ�AT����GSMģ���Զ���ȡ������Ϊ9600
	delay_ms(1000);
	printf("AT&F\r\n");
	delay_ms(1000);
	printf("AT+CGCLASS=\"B\"\r\n");
	delay_ms(1000);
	
	printf("AT+CGDCONT=1,\"IP\",\"CMNET\"\r\n");
	delay_ms(1000);
	
	printf("AT+CGATT=1\r\n");
	delay_ms(1000);
	
	printf("AT+CLPORT=\"TCP\",\"2000\"\r\n");	
	delay_ms(1000);
	 printf("AT+CIPMODE=1\r\n"); //͸�� 
	
	 printf("AT+CIPSTART=\"TCP\",\"221.226.69.234\",\"6002\"\r\n");	//�޸�ΪҪ���͸���IP�Ͷ˿�
	 delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);
	// TIM3_Int_Init(5000-1,8400-1);//500-1����ͨ��//50--//500//10//50//��ʱ��ʱ��84M����Ƶϵ��8400������84M/8400=10Khz�ļ���Ƶ�ʣ�����5000��Ϊ500ms
  memset(receBuf, 0, 81);
	receCount=0;
	while(1)
	{
		//  printf("AT+CIPMODE=1\r\n"); //͸�� 
		  // delay_ms(1000);
	   // printf("AT+CIPSTART=\"TCP\",\"221.226.69.234\",\"6002\"\r\n");	
		 // delay_ms(1000);
		if(Recevstate==1) //����յ�һ֡����  //receCount=15
		 {
		   Recevstate=0;
			// i=0;
			 jieshou_handle();
//		   while(receCount--)
//			 {
//				 USART_SendData(UART4, receBuf[i++]);
//				 while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET); 
//			 }
       
        receCount=0;    			 
		}
		
		
		//  GPIO_SetBits(GPIOC,GPIO_Pin_8);
		//  delay_ms(1000);
		//	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	
		
//		  USART_SendData(UART4,0x05);
//			printf("AT\r\n");
//      GPIO_ResetBits(GPIOB,GPIO_Pin_5);//���� LED3
		   
	    
		//   printf("AT+CIPMODE=1\r\n"); //͸�� 
		// printf("AT+CIPSTART=\"TCP\",\"123.57.41.13\",\"1005\"\r\n");
		//	delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);

	//		printf("AT+CIPSEND\r\n");  //ÿ�δ��ڷ�ATָ����лصĹ���Ҫ�˳��ص�����
		//	delay_ms(1000);

	//   	printf("CS");
		// USART_SendData(UART4,(0x09+'0'));
		 // while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)!= SET);  
	//		delay_ms(1000);
	//		printf("%c",0x1a);
	//		delay_ms(1000);
		
	//		printf("AT+CIPCLOSE=1\r\n");
	//		  delay_ms(1000);
		
	//		printf("AT+CIPSHUT\r\n");
	//		delay_ms(1000);
	
	}
}




