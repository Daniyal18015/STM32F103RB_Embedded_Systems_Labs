#ifndef UART_H_
#define UART_H_

#include <stdint.h>


             /*------ Including STM32F103RB and other Header File ------*/
#include "stm32f103xb.h"

         /*------ Function Prototype to Initiate UART Transmission mode ------*/
void UART2_TX_Init(void);

		/*------ Function Prototype to Read UART Receive Data Register ------*/
char UART2_READ(void);

   /*------ Function Prototype to Initiate UART Transmission-Receiver mode ------*/
void UART2_RX_TX_Init(void);



#endif /* UART_H_ */
