// Write bare-metal program using accessing registers to toggle LED state using user push button.
//  1) - Location of LED (PORT_A, PIN_5 => (PA5))
//  2) - Location of PUSH BUTTON (PORT_C, PIN_13 => (PC13))

              /* -------------   RCC BASE ADDRESS + RCC_APB2ENR OFFSET   -------------   */
#define RCC_BASE_ADDRESS			           (0x40021000)
#define RCC_APB2ENR_OFFSET                     (0x18)

                     /* -------------   GPIOx BASE ADDRESS   -------------   */
#define GPIO_BASE_ADDRESS					   (0x40010800)

                     /* -------------   GPIO REGISTERS OFFSETS   -------------   */
#define GPIO_PORT_OFFSET                       (0x400)
#define GPIO_CRL_OFFSET                        (0x00)
#define GPIO_CRH_OFFSET						   (0x04)
#define GPIO_IDR_OFFSET						   (0x08)
#define GPIO_ODR_OFFSET						   (0x0C)
#define GPIO_BSRR_OFFSET					   (0x10)
#define GPIO_BRR_OFFSET						   (0x14)
#define GPIO_LCKR_OFFSET					   (0x18)

                    /* -------------   GPIO PORTS  -------------   */
#define GPIO_PORT_A                            (0)
#define GPIO_PORT_B                            (1)
#define GPIO_PORT_C                            (2)
#define GPIO_PORT_D                            (3)
#define GPIO_PORT_E                            (4)
#define GPIO_PORT_F                            (5)
#define GPIO_PORT_G                            (6)

                    /* -------------   GPIO PINS   -------------   */
#define GPIO_PIN_0              			   (0)
#define GPIO_PIN_1              			   (1)
#define GPIO_PIN_2                             (2)
#define GPIO_PIN_3              			   (3)
#define GPIO_PIN_4              			   (4)
#define GPIO_PIN_5              			   (5)
#define GPIO_PIN_6                             (6)
#define GPIO_PIN_7                             (7)
#define GPIO_PIN_8              			   (8)
#define GPIO_PIN_9              			   (9)
#define GPIO_PIN_10              			   (10)
#define GPIO_PIN_11                            (11)
#define GPIO_PIN_12              			   (12)
#define GPIO_PIN_13              			   (13)
#define GPIO_PIN_14              			   (14)
#define GPIO_PIN_15              			   (15)

                 /* -------------   GPIO CONFIGURATIONS   -------------   */
// GPIO Input Mode Configuration
#define GPIO_ANALOG_IN_CFG                     (0)
#define GPIO_FLOATING_IN_CFG                   (1)
#define GPIO_PUPD_IN_CFG                       (2)

// GPIO Output Mode Configuration
#define GPIO_PP_OUT_CFG						   (0)
#define GPIO_OD_OUT_CFG                        (1)
#define GPIO_AF_PP_OUT_CFG                     (2)
#define GPIO_AF_OD_OUT_CFG                     (3)

// GPIO Modes Configuration
#define GPIO_IN_MODE				           (0)
#define GPIO_OUT_MODE_MAX_10MHz                (1)
#define GPIO_OUT_MODE_MAX_2MHz                 (2)
#define GPIO_OUT_MODE_MAX_50MHz                (3)

// GPIO PIN Level Configuration
#define GPIO_DIGITAL_LOW					   (0)
#define GPIO_DIGITAL_HIGH                      (1)

volatile unsigned int counter = 0;

int main(void)
{
	// Enable Port clock for GPIOA and GPIOC
	(*(volatile unsigned int *)(RCC_BASE_ADDRESS + RCC_APB2ENR_OFFSET) |= (1U << (GPIO_PORT_A + 2)));
	(*(volatile unsigned int *)(RCC_BASE_ADDRESS + RCC_APB2ENR_OFFSET) |= (1U << (GPIO_PORT_C + 2)));

	// Zero out the 4 pin configuration bits
	(*(volatile unsigned int *)(GPIO_BASE_ADDRESS + (GPIO_PORT_OFFSET*GPIO_PORT_A) + GPIO_CRL_OFFSET) &= ~(0xF << (GPIO_PIN_5*4)));

	// Set the 4 bit value for pin configuration in GPIO_CRL register
	(*(volatile unsigned int *)(GPIO_BASE_ADDRESS + (GPIO_PORT_OFFSET*GPIO_PORT_A) + GPIO_CRL_OFFSET) |= (((GPIO_PP_OUT_CFG*4)+GPIO_OUT_MODE_MAX_2MHz) << (GPIO_PIN_5*4)));

	// Set the 4 bit value for pin configuration in GPIO_CRL register
	(*(volatile unsigned int *)(GPIO_BASE_ADDRESS + (GPIO_PORT_OFFSET*GPIO_PORT_C) + GPIO_CRH_OFFSET) |= (0x10 << ((GPIO_PIN_13*4)-32)));

	while(1)
	{
	  // When the BUTTON at (PC13) get pressed
		if((*(volatile unsigned int *)((GPIO_BASE_ADDRESS + (GPIO_PORT_OFFSET*GPIO_PORT_C) + GPIO_IDR_OFFSET)) & (0x1 << (GPIO_PIN_13))) == 0UL)
		{
			counter = counter + 1;
		}
		if(counter == 1)
		{
			for (volatile unsigned int i = 0; i < 2000000; i++);    // LED will blink @ 2 seconds
			(*(volatile unsigned int *)(GPIO_BASE_ADDRESS + (GPIO_PORT_OFFSET*GPIO_PORT_A) + GPIO_ODR_OFFSET)) ^= (1UL << GPIO_PIN_5);
		}
		else if (counter == 2)
	    {
			for (volatile unsigned int i = 0; i < 1000000; i++);    // LED will blink @ 1 seconds
			(*(volatile unsigned int *)(GPIO_BASE_ADDRESS + (GPIO_PORT_OFFSET*GPIO_PORT_A) + GPIO_ODR_OFFSET)) ^= (1UL << GPIO_PIN_5);
		}

	    else if (counter == 4)
	    {
	    	for (volatile unsigned int i = 0; i < 800000; i++);    // LED will blink @ 0.8 seconds
	    	(*(volatile unsigned int *)(GPIO_BASE_ADDRESS + (GPIO_PORT_OFFSET*GPIO_PORT_A) + GPIO_ODR_OFFSET)) ^= (1UL << GPIO_PIN_5);
	   	}
	    else if (counter == 5)
	    {
	    	for (volatile unsigned int i = 0; i < 500000; i++);    // LED will blink @ 0.5 seconds
	    	(*(volatile unsigned int *)(GPIO_BASE_ADDRESS + (GPIO_PORT_OFFSET*GPIO_PORT_A) + GPIO_ODR_OFFSET)) ^= (1UL << GPIO_PIN_5);
	   	}
	    else if (counter == 6)
	    {
	    	for (volatile unsigned int i = 0; i < 100000; i++);    // LED will blink @ 0.1 seconds
	    	(*(volatile unsigned int *)(GPIO_BASE_ADDRESS + (GPIO_PORT_OFFSET*GPIO_PORT_A) + GPIO_ODR_OFFSET)) ^= (1UL << GPIO_PIN_5);
     	}
		else
		{
			for (volatile unsigned int i = 0; i < 50000; i++);    // LED will blink @ 0.05 seconds
			(*(volatile unsigned int *)(GPIO_BASE_ADDRESS + (GPIO_PORT_OFFSET*GPIO_PORT_A) + GPIO_ODR_OFFSET)) ^= (1UL << GPIO_PIN_5);
			counter = 0;
	    }
	}

}

