/*************************************************************************************************
                                          
*************************************************************************************************/

#ifndef __103_h
#define __103_h

#include  "stm32f4xx_usart.h"
extern void Serial_Interpret(void);//数据接收处理函数
extern void Ack_statid(u8 *sbuf);//固定帧长报文解析
extern void Ack_Changeable(u8 *sbuf);//可变帧报文解析
extern  u8  Makecrc(u8 *str,u8 nSize);
extern  void UART_Send(u8 *str,u8 len);//串口4发送
extern  void clearBuff(void);
extern void jieshou_handle(void);//可变帧接收处理
extern void store(void);//存总招数据


extern  u8 m_tx_buf[2000];//通讯资源
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
