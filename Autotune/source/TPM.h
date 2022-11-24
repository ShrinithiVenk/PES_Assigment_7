#ifndef _TPM_H_
#define _TPM_H_

#define CLK_FREQ			(48000000L)
#define DMA_SAMPLE_FREQ		(48000)

/*
 * Brief     : Initializes the TPM0 clock for DMA transfer at 48Khz and
 * Provides clock, sets MOD and presaclar values, and enables DMA request
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */
void Init_TPM0();

/*
 * Brief     : Initializes the TPM1 clock at 96Khz
 * Provides clock, sets MOD and presaclar values
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */
void Init_TPM1();
/*
 * Brief     : Starts the TPM0 timer
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */
void start_TPM();
#endif
