#ifndef __UART_H
#define __UART_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define Usart2_TX_LEN 100
#define Usart2_RX_LEN 60
extern UART_HandleTypeDef huart2;
extern __IO uint8_t Usart2_TX_Buf[Usart2_TX_LEN];//串口2发送数据数组
extern __IO uint8_t Usart2_RX_Buf[Usart2_RX_LEN];//串口2接收数据数组
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
void MX_USART2_Init(void);//串口2初始化函数

#define Uart4_TX_LEN 30
#define Uart4_RX_LEN 30
extern UART_HandleTypeDef huart4;
extern __IO uint8_t Uart4_TX_Buf[Uart4_TX_LEN];//串口4发送数据数组
extern __IO uint8_t Uart4_RX_Buf[Uart4_RX_LEN];//串口4接收数据数组
extern DMA_HandleTypeDef hdma_uart4_rx;
extern DMA_HandleTypeDef hdma_uart4_tx;
void MX_UART4_Init(void);//串口4初始化

void UsartReceive_IDLE(UART_HandleTypeDef *huart);//串口接收空闲中断函数

void dma_printf(const char *format, ...);//DMA发送方式printf()函数
	
#ifdef __cplusplus
}
#endif

#endif
