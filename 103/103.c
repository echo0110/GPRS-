/*****************************************************************************

*****************************************************************************/
#include  "string.h"
#include  "103.h"
#include  "math.h"
#include  "stm32f4xx_usart.h"
#include  "usart.h"
#include  "core_cm4.h"
#define  UART_RCV_SIZE 250
//֡��ʽ����
#define FRAME_T_VOL	0x68	/* �ɱ�֡��*/
#define FRAME_T_CON	0x10  /*�̶�֡��*/
u8 wLen;
u8 tot_leng;
u8 flag;
void beginSend(void);//���ڷ���
void Ack_statid(u8 *sbuf);//�̶�֡�����Ľ���
void UART_Send(u8 *str,u8 len);//����4����
u8  Makecrc(u8 *str,u8 nSize);//����У���

/*Э���ʼ��*/




/*���ݽ��մ�����*/
void Serial_Interpret()   //receBuf[receCount]
{
	 // UART4->CR1&=~(1<<8);//�ط����ж�
	 if(receCount>=5)
	{
	 	UART4->CR1&=~(1<<5);//�ؽ����ж�	
		
  if(receBuf[0]==0x10&&receCount==5&&receBuf[4]==0x16)//||(receBuf[5]==0x10&&receCount==10&&receBuf[9]==0x16))
	{ 
	    switch(receBuf[0])
		 {
			case FRAME_T_CON://�̶�֡
			 if(receBuf[2]==1)
			 {
			  Ack_statid(receBuf);//�̶�֡���Ĵ���
				//return;
				// break;
			 }
			// break;
			case FRAME_T_VOL://�ɱ�֡
			 if(receBuf[5]==1||receBuf[5]==0xff)
			 {
			 // Ack_Changeable(rbuf,byDevAddr,uart_port);//�ɱ�֡���Ĵ���
        return;
			 }
			// break;
			 default:
			  receCount = 0;
			  UART4->CR1|=(1<<5);//�������ж�
	   	 
				//return;
			 break;
  	 }
	 }
 }
		
	
	
}
	 
	
		
	


/*�̶�֡�����Ĵ���*/
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

	 
	switch(sbuf[1]&0x0f) //��λͨ��--40  ��λ����--47
	{
		  case 0x00://��λͨ�ŵ�Ԫ
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
		  // break;//����������-24��
		 
		   
		  
		
//	  case 0x07://��λ֡����
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

	  //	case 0x0a://����һ������
	//	 default://����������--24
  //		  break;//����������--24
	
	
	}
	




}






//}


/*����У���*/
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


/*����4����*/
void UART_Send(u8 *str,u8 len)
{
	 u8 i;
   for(i=0;i<len;i++)
	{
		
     USART_SendData(UART4, *(str+i)+'0');
	   while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);  //while���ʱ��ȵĺܾ����ݻ�û����ȥ  �Ѿ�����һ���ж���
     //USART_SendData(UART4, r\n);	  //����֮ǰIAR���������෢һ�����ݳ���
	}
}


