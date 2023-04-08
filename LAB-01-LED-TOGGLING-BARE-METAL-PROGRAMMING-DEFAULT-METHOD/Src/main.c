// Program to turn ON on-board LED

// Where the LED is connected on STM32F103RB board (PORT and PIN).

// User LED has location on board (PORT_A and PIN_5)

/* RCC */
#define RCC_START			    (0x40021000)
#define RCC_APB2EN			    (0x18)

/* GPIO Start Address */
#define GPIO_START			    (0x40010800)

/* GPIO Register offsets */
#define GPIO_CRL                (0x00)
#define GPIO_CRH                (0x04)
#define GPIO_IDR                (0x08)
#define GPIO_ODR                (0x0C)
#define GPIO_PORT_OFFSET        (0x400)

/* GPIO ports */
#define GPIO_A                  (0)
#define GPIO_B                  (1)
#define GPIO_C                  (2)
#define GPIO_D                  (3)
#define GPIO_E                  (4)
#define GPIO_F                  (5)
#define GPIO_G                  (6)

/* GPIO pins */
#define GPIO_PIN_0              (0)
#define GPIO_PIN_1              (1)
#define GPIO_PIN_2              (2)
#define GPIO_PIN_3              (3)
#define GPIO_PIN_4              (4)
#define GPIO_PIN_5              (5)
#define GPIO_PIN_6              (6)
#define GPIO_PIN_7              (7)
#define GPIO_PIN_8              (8)
#define GPIO_PIN_9              (9)
#define GPIO_PIN_10             (10)
#define GPIO_PIN_11             (11)
#define GPIO_PIN_12             (12)
#define GPIO_PIN_13             (13)
#define GPIO_PIN_14             (14)
#define GPIO_PIN_15             (15)

/* GPIO configuration */
/* Input mode configuration */
#define GPIO_ANALOG_IN_CFG           (0)
#define GPIO_FLOATING_IN_CFG         (1)
#define GPIO_PUPD_IN_CFG             (2)

/* Output mode configuration */
#define GPIO_PP_OUT_CFG              (0)
#define GPIO_OD_OUT_CFG              (1)
#define GPIO_ALT_PP_OUT_CFG          (2)
#define GPIO_ALT_OD_OUT_CFG          (3)

/* GPIO modes */
#define GPIO_IN_MODE                 (0)
#define GPIO_OUT_MODE_MAX_10MHZ      (1)
#define GPIO_OUT_MODE_MAX_2MHZ       (2)
#define GPIO_OUT_MODE_MAX_50MHZ      (3)

/* Pin levels */
#define GPIO_DIGITAL_LOW             (0)
#define GPIO_DIGITAL_HIGH            (1)


int main(void){

	/* Enable port clock, through RCC_APB2ENR register */
    (*(volatile unsigned int*)(RCC_START + RCC_APB2EN) |= ((1UL) << (GPIO_A+2)));

	/* Configuring GPIO_CRL register */
	/* Zero out the 4 pin configuration bits */
    (*(volatile unsigned int*)(GPIO_START + (GPIO_PORT_OFFSET*GPIO_A) + GPIO_CRL) &= ~((0xF) << (GPIO_PIN_5*4)));

	/* Set the 4 bit value for pin configuration in register */
    (*(volatile unsigned int*)(GPIO_START + (GPIO_PORT_OFFSET*GPIO_A) + GPIO_CRL) |= (((GPIO_PP_OUT_CFG*4)+GPIO_OUT_MODE_MAX_2MHZ) << (GPIO_PIN_5*4)));

   while(1)
    {
		/* Set PA5 high*/
	   *(volatile unsigned int*)(GPIO_START + (GPIO_PORT_OFFSET*GPIO_A) + GPIO_ODR) |= (1UL << GPIO_PIN_5);
    }

}
