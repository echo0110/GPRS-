#include  "timer.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "103.h"
#include "led.h"
#include "beep.h"
#include "key.h"


volatile uint8_t  i;   //47--2017-7-3 19:07

//2017-7-4 16:17调试OK 可召2级数据



//VNC

int main(void)    //明天加上定时器接收中断  stm32-modbus的那个
{ 
    
	u8 t;
	u8 len;	
	u16 times=0;  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	//clearBuff();//清缓存
	uart_init(115200);	//串口初始化波特率为115200--这样速度快
	//LED_Init();		  		//初始化与LED连接的硬件接口 
 // TIM3_Int_Init(500-1,8400-1);//500-1调试通过//50--//500//10//50//定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数5000次为500ms 
	
 	printf("AT\r\n");//先发AT，让GSM模块自动获取波特率为9600
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
	 printf("AT+CIPMODE=1\r\n"); //透传 
	
	 printf("AT+CIPSTART=\"TCP\",\"221.226.69.234\",\"6002\"\r\n");	//修改为要发送给的IP和端口
	 delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);
	// TIM3_Int_Init(5000-1,8400-1);//500-1调试通过//50--//500//10//50//定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数5000次为500ms
  memset(receBuf, 0, 81);
	receCount=0;
	while(1)
	{
		//  printf("AT+CIPMODE=1\r\n"); //透传 
		  // delay_ms(1000);
	   // printf("AT+CIPSTART=\"TCP\",\"221.226.69.234\",\"6002\"\r\n");	
		 // delay_ms(1000);
		if(Recevstate==1) //如果收到一帧数据  //receCount=15
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
//      GPIO_ResetBits(GPIOB,GPIO_Pin_5);//点亮 LED3
		   
	    
		//   printf("AT+CIPMODE=1\r\n"); //透传 
		// printf("AT+CIPSTART=\"TCP\",\"123.57.41.13\",\"1005\"\r\n");
		//	delay_ms(1000);delay_ms(1000);delay_ms(1000);delay_ms(1000);

	//		printf("AT+CIPSEND\r\n");  //每次串口发AT指令都会有回的过程要滤除回的数据
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




