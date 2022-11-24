#ifndef _ADC_H_
#define _ADC_H_
#define ADC_TIMER_FREQ  (96000)

/*
 * Brief     : Initializes the TPM1 timer for operating at 96000 KHz frquency
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */

void TPM1_call();

/*
 * Brief     : Initializes the ADC0 module for converting the data coming from DAC
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */
void Init_ADC0();


/*
 * Brief     : Calculates the minimum, maximum and average sample values in the buffer
 *
 * Parameters: BUFFER
 *
 * Return    : NULL
 */

void ADC_analyse(uint16_t *);
#endif
