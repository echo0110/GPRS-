/*****************************************************************************

*****************************************************************************/
#include  "string.h"
#include  "103.h"
#include  "math.h"
#include  "stm32f4xx_usart.h"
#include  "usart.h"
#include  "core_cm4.h"
#define  UART_RCV_SIZE 250
//帧格式类型
#define FRAME_T_VOL	0x68	/* 可变帧长*/
#define FRAME_T_CON	0x10  /*固定帧长*/
u8 wLen;
u8 tot_leng;
u8 flag;
void beginSend(void);//串口发送
void Ack_statid(u8 *sbuf);//固定帧长报文解析
void UART_Send(u8 *str,u8 len);//串口4发送
u8  Makecrc(u8 *str,u8 nSize);//计算校验和

/*协议初始化*/




/*数据接收处理函数*/
void Serial_Interpret()   //receBuf[receCount]
{
	 // UART4->CR1&=~(1<<8);//关发送中断
	 if(receCount>=5)
	{
	 	UART4->CR1&=~(1<<5);//关接收中断	
		
  if(receBuf[0]==0x10&&receCount==5&&receBuf[4]==0x16)//||(receBuf[5]==0x10&&receCount==10&&receBuf[9]==0x16))
	{ 
	    switch(receBuf[0])
		 {
			case FRAME_T_CON://固定帧
			 if(receBuf[2]==1)
			 {
			  Ack_statid(receBuf);//固定帧报文处理
				//return;
				// break;
			 }
			// break;
			case FRAME_T_VOL://可变帧
			 if(receBuf[5]==1||receBuf[5]==0xff)
			 {
			 // Ack_Changeable(rbuf,byDevAddr,uart_port);//可变帧报文处理
        return;
			 }
			// break;
			 default:
			  receCount = 0;
			  UART4->CR1|=(1<<5);//开接收中断
	   	 
				//return;
			 break;
  	 }
	 }
 }
		
	
	
}
	 
	
		
	


/*固定帧长报文处理*/
void Ack_statid(u8 *sbuf)
{
//  u8	*crc;
//	BYTE	*apack;
//	BYTE	dev_fun;
//	T_EVENT pEvent;
//	T_DIC	pDIC;
//	T_DATE	t_date;
//	T_SFCC p_sfcc;
//	BOOL	bDI,bEvent,bMeasure,bAlarm,bSFCC;
//	WORD	wLen;
//	WORD	ngd;
//	WORD	dev_id;
//	dev_id=Addr_to_ID(byDevAddr);

	 
	switch(sbuf[1]&0x0f) //复位通信--40  复位计数--47
	{
		  case 0x00://复位通信单元
	     memset(sbuf, 0, 240);
		  // flag=50;
		   sbuf[0]=0x10;
		   sbuf[1]=0x20;
		   sbuf[2]=0x01;
		   wLen=2;
		   sbuf[3]=Makecrc(sbuf,wLen);
		   sbuf[4]=0x16;
		   wLen=5;
		   tot_leng=wLen;
		
	     UART_Send(sbuf,wLen);
		  // break;//有问题待解决-24号
		 
		   
		  
		
//	  case 0x07://复位帧计数
//			   flag = 20;
//		     sbuf[0]=0x10;
//		     sbuf[1]= 0x20;
//		     sbuf[2]= 0x01;
//		      wLen = 2;
//		     sbuf[3] = Makecrc(sbuf,wLen);
//		     sbuf[4] = 0x16;
//		     wLen = 5;
//		     tot_leng = wLen;
//		
//		     UART_Send(sbuf,wLen);
//		     break;

	  //	case 0x0a://请求一级数据
	//	 default://有问题待解决--24
  //		  break;//有问题待解决--24
	
	
	}
	




}






//}


/*计算校验和*/
 u8  Makecrc(u8 *str,u8 nSize)
{
 u8 i;
 u8 J;
 J=0;
 for(i=1;i<=nSize;i++)
	{
	 J+=str[i];
	}
 return J;
}


/*串口4发送*/
void UART_Send(u8 *str,u8 len)
{
	 u8 i;
   for(i=0;i<len;i++)
	{
		
     USART_SendData(UART4, *(str+i)+'0');
	   while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);  //while这个时间等的很久数据还没发出去  已经是下一个中断了
     //USART_SendData(UART4, r\n);	  //可像之前IAR程序那样多发一个数据尝试
	}
}


