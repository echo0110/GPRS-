/*************************************************************************************************
                                          
*************************************************************************************************/

#ifndef __103_h
#define __103_h

#include  "stm32f4xx_usart.h"
extern void Serial_Interpret(void);//���ݽ��մ�����
extern void Ack_statid(u8 *sbuf);//�̶�֡�����Ľ���
extern void Ack_Changeable(u8 *sbuf);//�ɱ�֡���Ľ���
extern  u8  Makecrc(u8 *str,u8 nSize);
extern  void UART_Send(u8 *str,u8 len);//����4����
extern  void clearBuff(void);
extern void jieshou_handle(void);//�ɱ�֡���մ���
extern void store(void);//����������


extern  u8 m_tx_buf[2000];//ͨѶ��Դ
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







#endif
