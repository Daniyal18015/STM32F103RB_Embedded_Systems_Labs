// Program to toggle on-board LED using user button

// Where the LED is connected on STM32F103RB board (PORT_A and PIN_5 (PA5)).

// Where the BUTTON is connected on STM32F103RB board (PORT_C and PIN_13 (PC13))

         /*------ Including STM32F103RB Header File ------*/
#include "stm32f103xb.h"

        /*ENABLING CLOCK FOR PORTA for LED*/

#define GPIOAEN                                   (1U<<2)

	    /*ENABLING CLOCK FOR PORTA for LED*/
#define GPIOCEN                                   (1U<<4)

       /*Defining Pins for Mode of Button and LED*/
#define GPIOA_CRL_PIN5_MODE_REG                    (20)
#define GPIOC_CRH_PIN13_MODE_REG                   (20)

      /* Enabling the bits of BSRR Registers */
#define BIT_SET_PIN_5                              (1U << 21)          //  Enable the BS5 Pin for turn ON LED
#define BIT_RESET_PIN_5                            (1U << 5)           //  Enable the BR5 Pin for turn OFF LED


#define LED_PIN                                    (1U<<5)
#define BUTTON_PIN                                 (1U<<13)

int main(void)
{
	RCC->APB2ENR |= GPIOAEN;
	RCC->APB2ENR |= GPIOCEN;

	GPIOA->CRL &= ~(0xF << GPIOA_CRL_PIN5_MODE_REG);            // Set the GPIOA mode to push pull output
    GPIOA->CRL |= (0x01 << GPIOA_CRL_PIN5_MODE_REG);            // Set the Max Clock frequency  to 10MHz

	GPIOC->CRH |= (0x10 << GPIOC_CRH_PIN13_MODE_REG);           // Set the GPIOC mode to Input with pull-up / pull-down



	int counter = 0;
		while (1)
		{


			if (((GPIOC->IDR & (BUTTON_PIN))) == 0)                      // When Button get Press
			{
				counter = counter + 1;                                   // There will be increment by 1 when button get press
			}
			if (counter == 1)
			{
				for (volatile unsigned int i = 0; i < 2000000; i++);     // if counter == 1, LED will blinks at rate 2 sec
				GPIOA->ODR ^= LED_PIN;
			}

			else if (counter == 2)
			{
				for (volatile unsigned int i = 0; i < 1000000; i++);     // if counter == 1, LED will blinks at rate 1 sec
			    GPIOA->ODR ^= LED_PIN;
			}

			else if (counter == 3)
			{
			    for (volatile unsigned int i = 0; i < 800000; i++);     // if counter == 1, LED will blinks at rate 0.8 sec
				GPIOA->ODR ^= LED_PIN;
			}
			else if (counter == 4)
			{
			    for (volatile unsigned int i = 0; i < 500000; i++);     // if counter == 1, LED will blinks at rate 0.5 sec
				GPIOA->ODR ^= LED_PIN;
			}
			else if (counter == 5)
			{
			    for (volatile unsigned int i = 0; i < 100000; i++);     // if counter == 1, LED will blinks at rate 0.1 sec
				GPIOA->ODR ^= LED_PIN;
			}
			else {
				for (volatile unsigned int i = 0; i < 50000; i++);     // if counter == 1, LED will blinks at rate 0.05 sec
				GPIOA->ODR ^= LED_PIN;
				counter = 0;
		    }
		}
}
