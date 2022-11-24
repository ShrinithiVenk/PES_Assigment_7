#include <stdio.h>
#include "MKL25Z4.h"
#include "TPM.h"
#include <stdint.h>
#include "DMA.h"
#include "DAC.h"

/*
 * Brief     : Initializes the TPM0 clock for DMA transfer at 48Khz and
 * Provides clock, sets MOD and presaclar values, and enables DMA request
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */

void Init_TPM0(){
	//Providing clocks to ports and TMP0
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK); //Enable TPM clock
	//disable TPM
	TPM0->SC = 0;
	//TPM0 MOD for 48Khz operation
	TPM0->MOD = (CLK_FREQ/DMA_SAMPLE_FREQ) - 1;
	//set prescaler=1, enable DMA
	TPM0->SC = TPM_SC_DMA_MASK | TPM_SC_PS(0);
}

/*
 * Brief     : Initializes the TPM1 clock at 96Khz
 * Provides clock, sets MOD and presaclar values
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */
void Init_TPM1(){
	//Providing clocks to ports and TMP0
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	//enable clock
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
	//set MOD and pre-scalar according to 96KHz frequency
	TPM1->SC = 0;
	TPM1->MOD = 500-1;
	TPM1->SC |= TPM_SC_PS(0);
	//set debug mode
	TPM1->CONF |= TPM_CONF_DBGMODE(3);
	//start timer
	TPM1->SC |= TPM_SC_CMOD(1);
}

/*
 * Brief     : Starts the TPM0 timer
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */

void start_TPM(){
	//Enable TPM0 counter
	TPM0->SC |= TPM_SC_CMOD(1);
}
