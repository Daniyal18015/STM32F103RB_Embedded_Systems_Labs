#include <stdint.h>
#include <stdio.h>

          /*------ Including STM32F103RB and other Header File ------*/
#include "stm32f103xb.h"

                      /*------ ENABLING CLOCK FOR PORT_A ------*/
#define GPIOAEN                                   (1U<<2)

                   /*------ ENABLING CLOCK FOR UART2 BUS APB1 ------*/
#define CR1_TE									  (1U<<3)
#define CR1_UE       							  (1U<<13)
#define SR_TXE                                    (1U<<7)
#define UART2EN									  (1U<<17)
#define USART2_REMAP                              (1U<<3)

             /*------ BAUD RATE and PHERIPHERAL CLOCK FREQUENCY DEFINTION ------*/
#define SYSTEM_CLOCK_FREQUENCY					  8000000
#define APB1_CLOCK_FREQUENCY					  SYSTEM_CLOCK_FREQUENCY
#define UART_BAUD_RATE                            115200


                       /*------ UART FUNCTIONS PROTOTYPES ------*/

// Function to initialize USART2_TX
void UART2_TX_Iint(void);

// Function to computer UART Division
static  uint16_t Compute_UART_Div(uint32_t Peripheral_CLK, uint32_t BaudRate);

// Function to set Baud rate for UART according to system peripheral clock frequency
static void UART_Set_BaudRate(USART_TypeDef *USARTTx, uint32_t Peripheral_CLK, uint32_t BaudRate);

// Function to write a character for transmission
void UART2_Write(int charecter);


int __io_putchar(int ch)
{
	UART2_Write(ch);
	return ch;
}

int main(void)
{
	UART2_TX_Iint();

	while(1)
	{
		printf("HELLO FROM STM32F103RB..........\n\r");
	}
}


void UART2_TX_Iint(void)
{
            /*------ Configure UART GPIO PIN ------*/
// ENABLE CLOCK ACCESS TO GPIO_A
	RCC->APB2ENR |= GPIOAEN;

// SET PA2 MODE TO ALTERNATE FUNCTION MODE
	GPIOA->CRL |= (0xA << 8);
	GPIOA->CRL |= (0xF << 8);

// SET PA2 ALTERNATE FUNCTION TYPE TO UART_TX
	AFIO->MAPR &= ~(USART2_REMAP);


            /*------ Configure UART MODULE ------*/
// ENABLE CLOCK ACCESS TO UART2
	RCC->APB1ENR |= UART2EN;

// CONFIGURE BAUDRATE
	UART_Set_BaudRate(USART2, APB1_CLOCK_FREQUENCY, UART_BAUD_RATE);

// CONFIGURE TRANSFER DIRECTION
	USART2->CR1 |= CR1_TE;

// ENABLE UART MODULE
	USART2->CR1 |= CR1_UE;

}

void UART2_Write(int charecter)
{
// Make sure that transmit data register is empty
	while(!((USART2->SR) & (SR_TXE)));

// Write to transmit data register
	USART2->DR = (charecter & 0xFF);
}

static void UART_Set_BaudRate(USART_TypeDef *USARTTx, uint32_t Peripheral_CLK, uint32_t BaudRate)
{
	USARTTx->BRR = Compute_UART_Div(Peripheral_CLK, BaudRate);
}

static  uint16_t Compute_UART_Div(uint32_t Peripheral_CLK, uint32_t BaudRate)
{
	return ((Peripheral_CLK + (BaudRate/2U))/BaudRate);
}
