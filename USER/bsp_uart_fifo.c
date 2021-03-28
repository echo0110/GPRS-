/*
*********************************************************************************************************
*
*	模块名称 : 串口中断+FIFO驱动模块
*	文件名称 : bsp_uart_fifo.c
*	版    本 : V1.0
*	说    明 : 采用串口中断+FIFO模式实现多个串口的同时访问
*	修改记录 :
*		版本号  日期       作者    说明
*		V1.0    2013-02-01 armfly  正式发布
*		V1.1    2013-06-09 armfly  FiFo结构增加TxCount成员变量，方便判断缓冲区满; 增加 清FiFo的函数
*		V1.2	2014-09-29 armfly  增加RS485 MODBUS接口。接收到新字节后，直接执行回调函数。
*
*	Copyright (C), 2013-2014, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/


#include "sys.h"
#include "bsp_uart_fifo.h"


/* 定义每个串口结构体变量 */


#if UART4_FIFO_EN == 1
	static UART_T g_tUart4;
	static uint8_t g_TxBuf4[UART4_TX_BUF_SIZE];		/* 发送缓冲区 */
	static uint8_t g_RxBuf4[UART4_RX_BUF_SIZE];		/* 接收缓冲区 */
#endif


static void UartVarInit(void);

static void InitHardUart(void);
static void UartSend(UART_T *_pUart, uint8_t *_ucaBuf, uint16_t _usLen);
static uint8_t UartGetChar(UART_T *_pUart, uint8_t *_pByte);
static void UartIRQ(UART_T *_pUart);
static void ConfigUartNVIC(void);






/*
*********************************************************************************************************
*	函数名: UART_Write
*	函数说明: 向串口发送一组数据,数据放到发送数据 缓存区后立即返回 由中断服务子程序完成发送
*	形参: uart_port: (COM1 - COM6)
*			  sbuf: 待发送的缓存区
*			  wLen : 数据长度
*	返回值: 无
*********************************************************************************************************
*/
//static void UART_Write(uart_port,uint8_t *sbuf,uint16_t wLen)
//{
//  UART_T *pUart;
// 	pUart=ComToUart(uart_port);
//	if(pUart==0)
//	{	
//  return;//void型退出函数
//	}
//	UartSend(pUart,sbuf,wLen);
//	 


//}
/*
*********************************************************************************************************
*	函数名字: UartSend
*	功能说明: 填写数据到UART发送缓存区
*	形参: 无
*	返回值: 无
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
//     /*将数据填入发送缓存区*/
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
* 函数名: ComToUart
*	功能说明: 将COM端口转换为UART指针
*	形参: uart_port: 端口号(COM1 - COM6)
*	返回值: uart指针
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
	g_tUart4.uart = UART4;						/* STM32 串口设备 */
	g_tUart4.pTxBuf = g_TxBuf4;					/* 发送缓冲区指针 */
	g_tUart4.pRxBuf = g_RxBuf4;					/* 接收缓冲区指针 */
	g_tUart4.usTxBufSize = UART4_TX_BUF_SIZE;	/* 发送缓冲区大小 */
	g_tUart4.usRxBufSize = UART4_RX_BUF_SIZE;	/* 接收缓冲区大小 */
	g_tUart4.usTxWrite = 0;						/* 发送FIFO写索引 */
	g_tUart4.usTxRead = 0;						/* 发送FIFO读索引 */
	g_tUart4.usRxWrite = 0;						/* 接收FIFO写索引 */
	g_tUart4.usRxRead = 0;						/* 接收FIFO读索引 */
	g_tUart4.usRxCount = 0;						/* 接收到的新数据个数 */
	g_tUart4.usTxCount = 0;						/* 待发送的数据个数 */
	g_tUart4.SendBefor = 0;						/* 发送数据前的回调函数 */
	g_tUart4.SendOver = 0;						/* 发送完毕后的回调函数 */
	g_tUart4.ReciveNew = 0;						/* 接收到新数据后的回调函数 */
#endif
}


/*
*********************************************************************************************************
*	函数名: UartIRQ
*	函数说明: 供中断服务函数调用  串口中断服务函数
*	形参: uart_port : 串口设备
*	返回值: 无
*********************************************************************************************************
*/

static void UartIRQ(UART_T *uart_port)
{




}


/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
