// Program to toggle on-board LED using user button

// Where the LED is connected on STM32F103RB board (PORT_A and PIN_5 (PA5)).

// Where the BUTTON is connected on STM32F103RB board (PORT_C and PIN_13 (PC13))

         /*------ Including STM32F103RB Header File ------*/
#include "stm32f103xb.h"

        /*ENABLING CLOCK FOR PORTA for LED*/

#define GPIOAEN     (1U<<2)

	    /*ENABLING CLOCK FOR PORTA for LED*/
#define GPIOCEN     (1U<<4)

       /*Defining Pins for Mode of Button and LED*/
#define GPIOA_CRL_PIN5_MODE_REG     (20)
#define GPIOC_CRH_PIN13_MODE_REG    (20)

      /* Enabling the bits of BSRR Registers */
#define BIT_SET_PIN_5         (1U << 21)  //  Enable the BS5 Pin for turn ON LED
#define BIT_RESET_PIN_5       (1U << 5) //  Enable the BR5 Pin for turn OFF LED


#define LED_PIN     (1U<<5)
#define BUTTON_PIN  (1U<<13)

int main(void)
{
	RCC->APB2ENR |= GPIOAEN;
	RCC->APB2ENR |= GPIOCEN;

	GPIOA->CRL &= ~(0xF << GPIOA_CRL_PIN5_MODE_REG);    // Set the GPIOA mode to push pull output
    GPIOA->CRL |= (0x01 << GPIOA_CRL_PIN5_MODE_REG);    // Set the Max Clock frequency  to 10MHz

	GPIOC->CRH |= (0x10 << GPIOC_CRH_PIN13_MODE_REG);   // Set the GPIOC mode to Input with pull-up / pull-down



	while(1)
	{
        if(GPIOC->IDR & (BUTTON_PIN))        // if Button Get Press
        {
        	GPIOA->BSRR = BIT_SET_PIN_5;  // The LED state will be in ON state
        }
        else
        {
        	GPIOA->BSRR = BIT_RESET_PIN_5;   // The LED state will be in OFF state
        }
	}
}

