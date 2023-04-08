// Program to turn ON on-board LED

// Where the LED is connected on STM32F103RB board (PORT and PIN).

// User LED has location on board (PORT_A and PIN_5)

/* Including of STM32f103RB Board Header File */
#include "stm32f103xb.h"

/* Enabling the MCU Clock for accessing GPIO Peripheral */
#define GPIOAEN               (1U << 2)

/* Enabling the On-board LED */
#define LED_PIN               (1U << 5)

/* Defining Pin for GPIO Mode Register */
#define GPIOA_PIN5_MODE_REG        (20)

int main(void)
{

	RCC->APB2ENR |= GPIOAEN;
	GPIOA->CRL &= ~(0xF << GPIOA_PIN5_MODE_REG); // Set the GPIOA mode to push pull output
	GPIOA->CRL |= (0x01 << GPIOA_PIN5_MODE_REG); // Set the Max Clock frequency  to 10MHz
	while(1)
	{
         for(int i = 0;  i < 1000000; i++)
         {}
         GPIOA->ODR ^= LED_PIN;     // Toggling the state of LED after 1 second.
	}
}
