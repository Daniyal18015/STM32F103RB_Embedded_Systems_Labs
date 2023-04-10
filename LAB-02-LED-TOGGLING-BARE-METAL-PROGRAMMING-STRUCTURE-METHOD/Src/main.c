#include <stdint.h>

#define PHERIPHERAL_BASE_ADDRESS            0x40000000UL
#define APB2PHERIPHEAL_BASE_ADDRESS      	0x40010000UL
#define GPIOA_BASE_ADDRESS					0x40010800UL
#define RCC_BASE_ADDRESS                    0x40021000UL
#define RCC_APB2EN_REG                      (*(volatile unsigned int *)(RCC_BASE_ADDRESS + 0x18UL))
#define GPIOA_MODE_REG						(*(volatile unsigned int *)(GPIOA_BASE_ADDRESS + 0x00UL))
#define GPIOA_ODR_REG                       (*(volatile unsigned int *)(GPIOA_BASE_ADDRESS + 0x0CUL))

#define GPIOAEN                             (1U << 2)
#define LED_PIN 							(1U << 5)



typedef struct{

	volatile uint32_t CR[2];
	volatile uint32_t Dummy;
	volatile uint32_t ODR;
}GPIO_Typedef;

#define GPIO ((GPIO_Typedef *)GPIOA_BASE_ADDRESS)

typedef struct{
	volatile uint32_t Dummy[6];
	volatile uint32_t RCC_APB2ENR;
}RCC_Typedef;

#define RCC ((RCC_Typedef *)RCC_BASE_ADDRESS)


int main(void)
{
	RCC->RCC_APB2ENR |= (1U << GPIOAEN);

	GPIO->CR[2] &= ~(0xF << 20);
	GPIO->CR[2] |= (0x01 << 20);

	while(1)
	{
		 for(int i = 0; i < 1000000; i++){}
		GPIO->ODR ^= LED_PIN;


	}
}
