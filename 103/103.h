/*************************************************************************************************
                                          
*************************************************************************************************/

#ifndef __103_h
#define __103_h

#include  "stm32f4xx_usart.h"
extern void Serial_Interpret(void);//���ݽ��մ�����
extern void Ack_statid(u8 *sbuf);//�̶�֡�����Ľ���
extern  u8  Makecrc(u8 *str,u8 nSize);
extern  void UART_Send(u8 *str,u8 len);//����4����

//typedef struct tagT_C103_CODE_TABLE
//{
//  WORD			 dev_type;	    /* ???? */
//  T_EVENT_ENTRY  *p_event;	    /* ???? */
//  T_ALARM_ENTRY  *p_alarm;	    /* ???? */
//  T_SET_ENTRY    *p_setting;	/* ???? */
//  WORD			 w_even;		/* ???? */
//  WORD			 w_alarm;	    /* ???? */
//  WORD			 w_setting;	    /* ???? */
//}T_C103_CODE_TABLE


//103����֡��ʽ����  //�̶�֡
typedef struct tagT_C103_FRAME
{
  u8	type;			/* ֡���� */
  u8  len;			/* ����*/
  u8	contral;		/*������ */
  u8	address;		/*��ַ��*/
  u8	crc;			/*֡У��� */
  u8	endbyte;		/*�����ַ�*/
}T_C103_FRAME;


//103Ӧ�÷������ݵ�Ԫ(ASDU)��ʽ
//typedef struct tagT_C103_ASDU
//{
//  BYTE	type;			        /* ???? */
//  BYTE	vsq;		        	/* ??????? */
//  BYTE	cot;		        	/* ???? */
//  BYTE	addr;		        	/* ???? */
//  BYTE	fun;			        /* ???? */
//  BYTE	inf;			        /* ???? */
//  BYTE	data[C103_ASDU_SIZE-7];	/* ????? */
//}T_C103_ASDU;


/*����ÿ�����ڽṹ�����*/
#if  UART1_FIFO_EN==1
     static UART_T g_tUart1;//�������ṹ��Ȼ����ṹ�����
     static uint8_t g_TxBuf1[UART1_TX_BUF_SIZE];		/* ���ͻ�����*/
	   static uint8_t g_RxBuf1[UART1_RX_BUF_SIZE];		/* ���ջ����� */
#endif



#endif
