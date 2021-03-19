#include "UART.h"

#include <stm32f4xx.h>
#include "GPIO.h"
#include "../Services_layers/queue.h"


void (*callback_ptr)(uint8_t data);

void uart2_pin_conf(void)
{
	gpio_init(GPIOA);
	gpio_pin_conf_mode(GPIOA,2,ALT_FUNC);
	gpio_output_speed(GPIOA,2,HIGH_gp);
	gpio_altrenate_func(GPIOA,2,7);
	gpio_pull_up_down(GPIOA,2,PULLUP);
	gpio_pin_conf_mode(GPIOA,3,ALT_FUNC);
	gpio_pull_up_down(GPIOA,3,PULLUP);
	gpio_altrenate_func(GPIOA,3,7);

}
void UART_INIT_2(void (*ptr)(uint8_t data) )
{

	RCC->AHB1ENR |=0xf;
	RCC->APB1ENR |=(1<<17);
	USART2->CR1= 0;
	USART2->BRR = 7|(24<<4);
	USART2->CR3 |= (1<<7);
	USART2->CR1 |= (1<<13);
	USART2->CR1 |= (1<<2);
	USART2->CR1 |= (1<<3);
	USART2->CR1 |= (1<<5);
	NVIC_EnableIRQ(USART2_IRQn);

	uart2_pin_conf();
	callback_ptr = ptr ;
}



void USART2_IRQHandler(void)
{
	uint8_t data = USART2->DR;
	if (callback_ptr)
	{
		callback_ptr(data) ;
	}

}

