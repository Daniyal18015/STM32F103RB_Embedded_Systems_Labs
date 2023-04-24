#include <stdint.h>
#include <stdio.h>

          /*------ Including STM32F103RB and other Header File ------*/
#include "stm32f103xb.h"
#include "uart.h"
#include "adc_scm.h"

uint32_t Sensor_Value;

int main(void)
{
	UART2_TX_Init();
	PA1_ADC1_INIT();
	START_SINGLE_CONVERSION_ADC();

	while(1)
	{

		Sensor_Value = ADC_READ();
		printf("Sensor Value : %d \n\r", (int)Sensor_Value);


	}
}


