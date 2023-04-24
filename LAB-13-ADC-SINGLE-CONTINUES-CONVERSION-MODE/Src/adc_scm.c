
//-------------------------------- SYSTEM + USER DEFINED HEADER FILES ------------------------------
#include "stm32f103xb.h"
#include <stdio.h>
#include <stdint.h>
#include "adc_scm.h"

//-------------------- SYMBOLIC NAME DEFINATIONS FOR ADC PARAMETERS INITIALIZATION -----------------
#define GPIOAEN			   (1U<<2)
#define ADC1EN			   (1U<<9)
#define ADC1_ETRGREG_REMAP (1U<<18)
#define ADC1_CH1           (1U<<0)
#define ADC1_SEQ_LEN       (0x00)
#define ADC1_CR2_ADON      (1U<<0)
#define ADC1_CR2_SWSTART   (1U<<22)
#define ADC1_CR2_CONT       (1U<<1)
#define ADC1_SR_EOC        (1U<<1)

////-------------------------------- SYSTEM + USER DEFINED HEADER FILES------------------------------

void PA1_ADC1_INIT(void)
{
	     /*---- Configure ADC GPIO Pin ----*/
// Enable Clock Access to GPIOA
	RCC->APB2ENR |= GPIOAEN;

// Set PA1 mode as analog mode
	GPIOA->CRL  &= ~(0xFF<<6);
	GPIOA->CRL  &= ~(0xFF<<4);


        /*---- Configure ADC Module AND PARAMETERS*/
// Enable Clock Access to ADC
	RCC->APB2ENR |= ADC1EN;

// Set ADC Sequence Start
	ADC1->SQR3 = ADC1_CH1;

// Set ADC Sequence Length
	ADC1->SQR1 = ADC1_SEQ_LEN;



}

void START_SINGLE_CONVERSION_ADC(void)
{
// Enable ADC Module
	ADC1->CR2 |= ADC1_CR2_CONT;
    ADC1->CR2 |= ADC1_CR2_ADON;
    ADC1->CR2 |= ADC1_CR2_ADON;
// Start ADC conversion mode
	ADC1->CR2 |= ADC1_CR2_SWSTART;
}

uint32_t ADC_READ(void)
{
// Wait for the completion of ADC conversion
	while(!((ADC1->SR) & (ADC1_SR_EOC))){}

// Read converted result
	return (ADC1->DR);
}
