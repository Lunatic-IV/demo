#ifndef __UART_H
#define __UART_H
#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define Usart2_TX_LEN 100
#define Usart2_RX_LEN 60
extern UART_HandleTypeDef huart2;
extern __IO uint8_t Usart2_TX_Buf[Usart2_TX_LEN];//����2������������
extern __IO uint8_t Usart2_RX_Buf[Usart2_RX_LEN];//����2������������
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
void MX_USART2_Init(void);//����2��ʼ������

#define Uart4_TX_LEN 30
#define Uart4_RX_LEN 30
extern UART_HandleTypeDef huart4;
extern __IO uint8_t Uart4_TX_Buf[Uart4_TX_LEN];//����4������������
extern __IO uint8_t Uart4_RX_Buf[Uart4_RX_LEN];//����4������������
extern DMA_HandleTypeDef hdma_uart4_rx;
extern DMA_HandleTypeDef hdma_uart4_tx;
void MX_UART4_Init(void);//����4��ʼ��

void UsartReceive_IDLE(UART_HandleTypeDef *huart);//���ڽ��տ����жϺ���

void dma_printf(const char *format, ...);//DMA���ͷ�ʽprintf()����
	
#ifdef __cplusplus
}
#endif

#endif
