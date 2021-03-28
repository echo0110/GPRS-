/*************************************************************************************************
                                          
*************************************************************************************************/

#ifndef __103_h
#define __103_h

#include  "stm32f4xx_usart.h"
extern void Serial_Interpret(void);//数据接收处理函数
extern void Ack_statid(u8 *sbuf);//固定帧长报文解析
extern  u8  Makecrc(u8 *str,u8 nSize);
extern  void UART_Send(u8 *str,u8 len);//串口4发送

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


//103报文帧格式描述  //固定帧
typedef struct tagT_C103_FRAME
{
  u8	type;			/* 帧类型 */
  u8  len;			/* 长度*/
  u8	contral;		/*控制域 */
  u8	address;		/*地址域*/
  u8	crc;			/*帧校验和 */
  u8	endbyte;		/*结束字符*/
}T_C103_FRAME;


//103应用服务数据单元(ASDU)格式
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


/*定义每个串口结构体变量*/
#if  UART1_FIFO_EN==1
     static UART_T g_tUart1;//先声明结构体然后定义结构体变量
     static uint8_t g_TxBuf1[UART1_TX_BUF_SIZE];		/* 发送缓存区*/
	   static uint8_t g_RxBuf1[UART1_RX_BUF_SIZE];		/* 接收缓存区 */
#endif



#endif
