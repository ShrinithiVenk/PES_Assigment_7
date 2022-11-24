#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "TPM.h"
#include "DMA.h"
#include "sin.h"
#include "DAC.h"
#include "ADC.h"
#include <stdlib.h>
#include "systick.h"
#include "autocorrelate.h"
#include "fp_trig.h"



/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 *
 * Author: Shrinithi Venkatesan
 *
 * References and Credits:
 * Dean book chapter on adc,dca and dma.
 * https://github.com/alexander-g-dean/ESF
 * https://github.com/Maitreyee2095/PES-Assignment-7
 */

uint16_t A4_Buffer[SIZE_A4];
uint16_t D5_Buffer[SIZE_D5];
uint16_t E5_Buffer[SIZE_E5];
uint16_t A5_Buffer[SIZE_A5];
extern uint16_t adc_buffer[SIZE];
extern int16_t samples_per_period, samples_frequency, samples_generated;

//Main Function
int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
#endif
	//basic initialization
	uint16_t i, adc_freq;
	Init_DAC0();
	tone_to_samples(D5, D5_Buffer);
	tone_to_samples(E5, E5_Buffer);
	tone_to_samples(A5, A5_Buffer);
	tone_to_samples(A4, A4_Buffer);
	__enable_irq();
	Init_DMA(A4_Buffer, SIZE_A4);
	Init_TPM0();
	start_TPM();
	DMA0_start_transfer();
	Init_ADC0();
	Init_SysTick();
	Init_TPM1();

	/* Enter an infinite loop. */

	while(1){
		//accumulating the ADC samples in the buffer
		ADC0->SC1[0] = ADC_SC1_ADCH(23);
		while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK));
		adc_buffer[i] = ADC0->R[0];
		i++;
		if(i==SIZE){
			int period = autocorrelate_detect_period(&adc_buffer[0], 1024, kAC_16bps_unsigned);//compute the period of adc buffer using autocorrelate
			adc_freq = ADC_TIMER_FREQ/period;
			printf("\r\nSamples generated = %d at %d Hz \r\nComputed period = %d samples", samples_generated, samples_frequency, samples_per_period);
			ADC_analyse(adc_buffer);//compute mininum, maximum, and average value of the adc buffer
			printf("\r\nPeriod = %d \r\nFrequency of ADC = %u \n", period, adc_freq);
			change_tone();
			i=0;
		}
	}
	return 0 ;
}
