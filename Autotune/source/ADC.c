#include <stdio.h>
#include "MKL25Z4.h"
#include "sin.h"
#include"tpm.h"

#define ADC_SIZE	(65535)
#define ADC_POS 	23

uint16_t adc_buffer[SIZE];

/*
 * Brief     : Initializes the ADC0 module for converting the data coming from DAC
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */

void Init_ADC0(){
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	//select analog pin
	PORTE->PCR[ADC_POS] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[ADC_POS] |= PORT_PCR_MUX(0);
	//clock is busclock/2 and ADIV=2
	ADC0->CFG1 &= ~ADC_CFG1_ADLPC_MASK;
	ADC0->CFG1 |= ADC_CFG1_ADIV(1) | ADC_CFG1_MODE(3) |
			ADC_CFG1_ADICLK(1);
	//select default reference clock
	ADC0->SC2 = ADC_SC2_REFSEL(0) | ADC_SC2_ADTRG_MASK;
	//configure for hardware trigger with TPM1
	SIM->SOPT7 &= ~SIM_SOPT7_ADC0PRETRGSEL_MASK;
	SIM->SOPT7 |= SIM_SOPT7_ADC0ALTTRGEN_MASK |
			SIM_SOPT7_ADC0TRGSEL(9);
}

/*
 * Brief     : Calculates the minimum, maximum and average sample values in the buffer
 *
 * Parameters: BUFFER
 *
 * Return    : NULL
 */

void ADC_analyse(uint16_t *BUFFER){
	uint16_t min_idx=0, max_idx=0, avg_val=0, i=SIZE;
	uint32_t total=0;
	while(i--)
		{
		if(BUFFER[i]<BUFFER[min_idx])
			min_idx = i; //calculates minimum value
		if(BUFFER[i]>BUFFER[max_idx])
			max_idx = i; //calculates maximum value
		total = total + BUFFER[i];
		}
	avg_val = total/SIZE; //calculates average of max and min
	printf("\r\nMININUM value  = %u \r\nMAXIMUM value = %u \r\nAverage value = %u" , BUFFER[min_idx], BUFFER[max_idx], avg_val);
}

/*
 * Brief     : Initializes the TPM1 timer for operating at 96000 KHz frquency
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */

void TPM1_call()
{
Init_TPM1();
}

