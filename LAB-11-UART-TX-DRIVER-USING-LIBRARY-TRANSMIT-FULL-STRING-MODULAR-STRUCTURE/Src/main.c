#include <stdint.h>
#include <stdio.h>

          /*------ Including STM32F103RB and other Header File ------*/
#include "stm32f103xb.h"
#include "uart.h"



int main(void)
{
	UART2_TX_Iint();

	while(1)
	{
		printf("HELLO FROM STM32F103RB..........\n\r");
	}
}


