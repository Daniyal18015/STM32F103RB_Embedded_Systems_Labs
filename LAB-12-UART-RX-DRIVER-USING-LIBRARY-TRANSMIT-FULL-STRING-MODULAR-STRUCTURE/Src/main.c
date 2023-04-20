#include <stdint.h>
#include <stdio.h>

          /*------ Including STM32F103RB and other Header File ------*/
#include "stm32f103xb.h"
#include "uart.h"

#define GPIOAEN			(1U<<2)
#define LED_PIN			(1U<<5)

char key;

int main(void)
{
	RCC->APB2ENR |= GPIOAEN;
	GPIOA->CRL   &= ~(0xF<<20);
	GPIOA->CRL   |= (0x01<<20);

	UART2_RX_TX_Init();

	while(1)
	{
		key = UART2_READ();

		if(key == '1')
		{
			GPIOA->ODR |= LED_PIN;
		}
		else
		{
			GPIOA->ODR &= ~LED_PIN;
		}
	}
}


