/*
*********************************************************************************************************
*
*	ģ������ : �����ж�+FIFO����ģ��
*	�ļ����� : bsp_uart_fifo.c
*	��    �� : V1.0
*	˵    �� : ���ô����ж�+FIFOģʽʵ�ֶ�����ڵ�ͬʱ����
*	�޸ļ�¼ :
*		�汾��  ����       ����    ˵��
*		V1.0    2013-02-01 armfly  ��ʽ����
*		V1.1    2013-06-09 armfly  FiFo�ṹ����TxCount��Ա�����������жϻ�������; ���� ��FiFo�ĺ���
*		V1.2	2014-09-29 armfly  ����RS485 MODBUS�ӿڡ����յ����ֽں�ֱ��ִ�лص�������
*
*	Copyright (C), 2013-2014, ���������� www.armfly.com
*
*********************************************************************************************************
*/


#include "sys.h"
#include "bsp_uart_fifo.h"


/* ����ÿ�����ڽṹ����� */


#if UART4_FIFO_EN == 1
	static UART_T g_tUart4;
	static uint8_t g_TxBuf4[UART4_TX_BUF_SIZE];		/* ���ͻ����� */
	static uint8_t g_RxBuf4[UART4_RX_BUF_SIZE];		/* ���ջ����� */
#endif


static void UartVarInit(void);

static void InitHardUart(void);
static void UartSend(UART_T *_pUart, uint8_t *_ucaBuf, uint16_t _usLen);
static uint8_t UartGetChar(UART_T *_pUart, uint8_t *_pByte);
static void UartIRQ(UART_T *_pUart);
static void ConfigUartNVIC(void);






/*
*********************************************************************************************************
*	������: UART_Write
*	����˵��: �򴮿ڷ���һ������,���ݷŵ��������� ���������������� ���жϷ����ӳ�����ɷ���
*	�β�: uart_port: (COM1 - COM6)
*			  sbuf: �����͵Ļ�����
*			  wLen : ���ݳ���
*	����ֵ: ��
*********************************************************************************************************
*/
//static void UART_Write(uart_port,uint8_t *sbuf,uint16_t wLen)
//{
//  UART_T *pUart;
// 	pUart=ComToUart(uart_port);
//	if(pUart==0)
//	{	
//  return;//void���˳�����
//	}
//	UartSend(pUart,sbuf,wLen);
//	 


//}
/*
*********************************************************************************************************
*	��������: UartSend
*	����˵��: ��д���ݵ�UART���ͻ�����
*	�β�: ��
*	����ֵ: ��
*********************************************************************************************************
*/
//static void UartSend(UART_T pUART,uint8_t *sbuf,uint16_t wLen)
//{
//  uint16_t i;
//	for(i=0;i<wLen;i++)
//	{
//	 while(1)
//	  {
//		 __IO uint16_t usCount;
//		 	DISABLE_INT();
//			usRead=uart_port->usTxRead;
//			ENABLE_INT();
//		 if(usCount<uart_port->usTxBufSize)
//		 {
//		   break;
//		 }
//     /*���������뷢�ͻ�����*/
//		 uart_port->pTxBuf[uart->port->usTxWrite]=sBuf[i];
//			DISABLE_INT();
//		 if(++uart_port->usTxWrite>=uart->usTxBufSize)
//		 {
//		  uart_port->usTxWrite=0;
//		 }
//		 uart_port->usTxCount++;
//		 ENABLE_INT();
//		USART_ITConfig(uart_port->uart, USART_IT_TXE, ENABLE);
//     		 
//	 }
//	
//	}

//}



/*
*********************************************************************************************************
* ������: ComToUart
*	����˵��: ��COM�˿�ת��ΪUARTָ��
*	�β�: uart_port: �˿ں�(COM1 - COM6)
*	����ֵ: uartָ��
*********************************************************************************************************
*/
//UART_T *ComToUart(uart_port)
//{
// 
// if (uart_port == UART4)
//	{
//		#if UART4_FIFO_EN == 1
//			return &g_tUart4;
//		#else
//			return 0;
//		#endif
//	}
//	else
//	{
//	 return 0;
//	}
//	
//}


static void UartVarInit(void)
{


#if UART4_FIFO_EN == 1
	g_tUart4.uart = UART4;						/* STM32 �����豸 */
	g_tUart4.pTxBuf = g_TxBuf4;					/* ���ͻ�����ָ�� */
	g_tUart4.pRxBuf = g_RxBuf4;					/* ���ջ�����ָ�� */
	g_tUart4.usTxBufSize = UART4_TX_BUF_SIZE;	/* ���ͻ�������С */
	g_tUart4.usRxBufSize = UART4_RX_BUF_SIZE;	/* ���ջ�������С */
	g_tUart4.usTxWrite = 0;						/* ����FIFOд���� */
	g_tUart4.usTxRead = 0;						/* ����FIFO������ */
	g_tUart4.usRxWrite = 0;						/* ����FIFOд���� */
	g_tUart4.usRxRead = 0;						/* ����FIFO������ */
	g_tUart4.usRxCount = 0;						/* ���յ��������ݸ��� */
	g_tUart4.usTxCount = 0;						/* �����͵����ݸ��� */
	g_tUart4.SendBefor = 0;						/* ��������ǰ�Ļص����� */
	g_tUart4.SendOver = 0;						/* ������Ϻ�Ļص����� */
	g_tUart4.ReciveNew = 0;						/* ���յ������ݺ�Ļص����� */
#endif
}


/*
*********************************************************************************************************
*	������: UartIRQ
*	����˵��: ���жϷ���������  �����жϷ�����
*	�β�: uart_port : �����豸
*	����ֵ: ��
*********************************************************************************************************
*/

static void UartIRQ(UART_T *uart_port)
{




}


/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
