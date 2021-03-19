#ifndef  uart
#define  uart

#include <stm32f4xx.h>

void UART_SEND (USART_TypeDef *usart, uint8_t data);

void UART_INIT_2(void (*ptr)(uint8_t data) );

void UART_INIT_1(void);

void UART_INIT_3(void);

void UART_Write_Array(USART_TypeDef *usart,unsigned char *arr  ,int size);

uint8_t uart_2_queue_read (void);
uint8_t uart_2_queue_get_size (void);

#endif
