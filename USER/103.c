/*****************************************************************************

*****************************************************************************/

#include  "103.h"
#include  "math.h"
#include  "stm32f4xx_usart.h"
#include  "usart.h"
#include  "core_cm4.h"
#include  "stdio.h"
#include  "string.h"
#include  "delay.h"
#define  UART_RCV_SIZE 250
//֡��ʽ����
#define FRAME_T_VOL	0x68	/* �ɱ�֡��*/
#define FRAME_T_CON	0x10  /*�̶�֡��*/
u8 wLen,Wsize;
u8 tot_leng;
u8 flag;
void beginSend(void);//���ڷ���
void Ack_statid(u8 *sbuf);//�̶�֡�����Ľ���
void Ack_Changeable(u8 *sbuf);//�ɱ�֡���Ľ���
void UART_Send(u8 *str,u8 len);//����4����
u8  Makecrc(u8 *str,u8 nSize);//����У���
void store(void);//����������
u8  rx_buf[2000];//ͨѶ��Դ--����
u8 tx_buf[2000];//ͨѶ��Դ--����
//103����֡��ʽ����  //�̶�֡
typedef struct //tagT_C103_FRAME
{
  u8	type;			/* ֡���� */
  u8  len;			/* ����*/
  u8	contral;		/*������ */
  u8	address;		/*��ַ��*/
  u8	crc;			/*֡У��� */
  u8	endbyte;		/*�����ַ�*/
} FRAME; //����ṹ��



 
 //FRAME *p_frame;
// strcpy(p_frame->type,0);
 
  

/*103Ӧ�÷������ݵ�Ԫ(ASDU)��ʽ */
 typedef struct tagT_ASDU
{
  u8	type;			        /* ???? */
  u8  vsq;		        	/* ??????? */
  u8 	cot;		        	/* ???? */
  u8 	addr;		        	/* ???? */
  u8	fun;			        /* ???? */
  u8	inf;			        /* ???? */
 
 // u8	data[C103_ASDU_SIZE-7];	/* ????? */
} ASDU;  //����ṹ��
 //ASDU  *p_frame; //����ṹ��ָ��


void jieshou_handle(void);

/*Э���ʼ��*/




/*���ݽ��մ�����*/
void Serial_Interpret()   //receBuf[receCount]
{ 
	  
	  FRAME p_frame;
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
			  Ack_Changeable(receBuf);//�ɱ�֡���Ĵ���
       // return;
			 }
			 tx_buf[0]=p_frame.type;
			 tx_buf[1]=p_frame.len;
			 tx_buf[2]=p_frame.len;
			 tx_buf[3]=p_frame.type;
			 tx_buf[4]=p_frame.contral;
			 tx_buf[5]=0x01;
			 tx_buf[4+p_frame.len]=Makecrc(&tx_buf[4],p_frame.len);
			 Wsize=p_frame.len+6;
			 UART_Send(tx_buf,wLen);
			 
			 
			 
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
	}
	




}

/*�ɱ�֡�����Ĵ���*/
void Ack_Changeable(u8 *rbuf)
{
 


}







//}


/*����У���*/
 u8  Makecrc(u8 *str,u8 nSize)
{
 u8 i;
 u8 J;
 J=0;
 for(i=0;i<nSize;i++)
	{
	 J+=str[i];
	}
 return J;
}


/*����4����*/
void UART_Send(u8 *str,u8 len)
{
	 u8 i;
	// printf("AT+CIPSEND\r\n");
   for(i=0;i<len;i++)
	{
		 
     USART_SendData(UART4, *(str+i));
	   while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);  //while���ʱ��ȵĺܾ����ݻ�û����ȥ  �Ѿ�����һ���ж���
     //USART_SendData(UART4, r\n);	  //����֮ǰIAR���������෢һ�����ݳ���
	}
	//printf("%c",0x1a);
}


//����ջ���
void clearBuff(void)
{
	 u8 j=0;
    for(j=0;j<receCount;j++)
    {
        receBuf[j]=0x00;
    }
    j=0;
}

/*һ֡���ݽ��մ�����--�ɱ�֡*/
void jieshou_handle() 
{
	  FRAME p_frame;
//	 if(receBuf[0]==0x10&&receBuf[1]==0x40&&receCount==5&&receBuf[4]==0x16)   //�ȸ�λͨ��
//	 {
//		 // printf("AT+CIPSEND\r\n");
//	   tx_buf[0]=0x10;
//		 tx_buf[1]=0x00;
//		 tx_buf[2]=receBuf[2];
//		 wLen=2;
//		 tx_buf[3]=Makecrc(&tx_buf[1],wLen);
//		 tx_buf[4]=0x16;
//		  wLen=5;
//		 UART_Send(tx_buf,wLen);
//		 
//		// printf("%c",0x1a);
//		// delay_ms(500);
//	 
//	 }
   if(receBuf[0]==0x10&&receBuf[1]==0x47&&receCount==5&&receBuf[4]==0x16)//��λ����
	{
	   tx_buf[0]=0x10;
		 tx_buf[1]=0x00;//  00 ACD DFC ������
		 tx_buf[2]=receBuf[2];
		 wLen=2;
		 tx_buf[3]=Makecrc(&tx_buf[1],wLen);
		 tx_buf[4]=0x16;
		 wLen=5;
		// printf("AT+CIPSEND\r\n");
		 UART_Send(tx_buf,wLen);
	  //  printf("%c",0x1a);
	}
	else	if(receBuf[0]==0x10&&receBuf[1]==0x49&&receCount==5&&receBuf[4]==0x16)   //������·49
 	 {
//		 // printf("AT+CIPSEND\r\n");
	   tx_buf[0]=0x10;
		 tx_buf[1]=0x0B;
		 tx_buf[2]=receBuf[2];
		 wLen=2;
		 tx_buf[3]=Makecrc(&tx_buf[1],wLen);
		 tx_buf[4]=0x16;
		  wLen=5;
		 UART_Send(tx_buf,wLen);
		 
//		// printf("%c",0x1a);
//		// delay_ms(500);
//	 
 	 }
  else if(receBuf[0]==0x68&&receCount==15&&receBuf[14]==0x16) //�ܲ�ѯ
	{
		
		    store();
		   
	     tx_buf[0]=0x10;
		   tx_buf[1]=0x10;
		   tx_buf[2]=receBuf[5];
		   wLen=2;
		   tx_buf[3]=Makecrc(&tx_buf[1],wLen);
		   tx_buf[4]=0x16;
		   wLen=5;
		 //  tot_leng=wLen;
		  // printf("AT+CIPSEND\r\n");
  		 UART_Send(tx_buf,wLen);
		  //printf("%c",0x1a);
		p_frame.type=0x68;
   	p_frame.len=receBuf[1];
	  p_frame.contral=receBuf[4];//������
	  p_frame.address=receBuf[5];//��ַ��
	  //p_frame.crc=receBuf[p_frame.len+4];//CRC
	}
	else if(receBuf[0]==0x10&&receBuf[1]==0x5b&&receCount==5&&receBuf[4]==0x16) //��ַ01��2������
	{
	     tx_buf[0]=p_frame.type;//0x68
			 tx_buf[1]=(3*2+7*2+2); //0x16
			 tx_buf[2]=(3*2+7*2+2); //0x16  ASDU+2
			 tx_buf[3]=p_frame.type;//0x68
			 tx_buf[4]=0x08;//0x08  //�����ݰ���Ӧ����֡--������
			 tx_buf[5]=p_frame.address;
		   tx_buf[6]=0x32;
		   tx_buf[7]=0x07;
		   tx_buf[8]=0x02;
		   tx_buf[9]=p_frame.address;
		   tx_buf[10]=0x01;//FUN
		   tx_buf[11]=0x5c;//INF
		   tx_buf[12]=0xf8;
		   tx_buf[13]=0xff;
		
		   tx_buf[14]=0xf8;
		   tx_buf[15]=0xff;
		   
		   tx_buf[16]=0x00;
		   tx_buf[17]=0x00;
		
		   tx_buf[18]=0xf8;
		   tx_buf[19]=0xff;
			 
			 tx_buf[20]=0xf8;
		   tx_buf[21]=0xff;
			 
			 
			 tx_buf[22]=0xf8;
		   tx_buf[23]=0xff;
			 
			 tx_buf[24]=0xf8;
		   tx_buf[25]=0xff;
			 
		
		   
			 tx_buf[26]=Makecrc(&tx_buf[4],22);
			 tx_buf[27]=0x16;
			 Wsize=22+6;
			 UART_Send(tx_buf,Wsize);
			 
	}
}


/*��һ�����е����ݴ�����*/
void store(void)
{
  
  
	//if(p_frame.crc==Makecrc(&receBuf[4],p_frame.len&&p_frame.address)) //У��ͨ��
	{
	// return size;
	}
	

}

