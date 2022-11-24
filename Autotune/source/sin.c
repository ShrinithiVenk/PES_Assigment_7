#include "sin.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "systick.h"
#include "test_sine.h"
#include "TPM.h"
#include "DMA.h"
#include "fp_trig.h"

#define TRIG_TABLE_STEPS     (32)
#define TRIG_TABLE_STEP_SIZE (HALF_PI/TRIG_TABLE_STEPS)

extern ticktime_t tick;
extern uint16_t A4_Buffer[SIZE_A4];
extern uint16_t D5_Buffer[SIZE_D5];
extern uint16_t E5_Buffer[SIZE_E5];
extern uint16_t A5_Buffer[SIZE_A5];
int16_t samples_per_period, samples_frequency, samples_generated;

/*
 * Brief     : Tests the error and sum of square error in fp_sin() function (values of sin(i))
 * takes no argument and returns void
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */

void test()
{
	test_sin();
}

/*
 * Brief     : Calculates the samples for each tone from the sin function calculated
 * using fp_sin() also calculates the number of samples generated for each tone
 *
 * Parameters: tone, sin_buffer
 *
 * Return    : NULL
 */

void tone_to_samples(tones tone, uint16_t *sin_buffer){
	uint16_t samples;
	switch(tone){
	case A4:
	{
		samples_frequency = 440;
		samples_per_period = (DMA_SAMPLE_FREQ/samples_frequency);
		break;
	}
	case D5:
	{
		samples_frequency = 587;
		samples_per_period = (DMA_SAMPLE_FREQ/samples_frequency);
		break;
	}
	case E5:
	{
		samples_frequency = 659;
		samples_per_period = (DMA_SAMPLE_FREQ/samples_frequency);
		break;
	}
	case A5:
	{
		samples_frequency = 880;
		samples_per_period = (DMA_SAMPLE_FREQ/samples_frequency);
		break;
	}

	}
	samples_generated = SIZE/samples_per_period;
	samples_generated *= samples_per_period;
	for(samples=0; samples<samples_generated; samples++){
	sin_buffer[samples] = TRIG_SCALE_FACTOR + fp_sin((samples % samples_per_period)*(TWO_PI+1)/samples_per_period);
	}
}

/*
 * Brief     : Changes the tone based on systick
 * timer tick takes no arguments and return void
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */

void change_tone(){
	//the input to the compute_samples function is the frequency of the wave
	switch(tick){
	case 0:
	{
		compute_samples(440);
		Init_DMA(A4_Buffer, SIZE_A4);
		DMA0_start_transfer();
		break;
	}
	case 1:
	{
		compute_samples(587);
		Init_DMA(D5_Buffer, SIZE_D5);
		DMA0_start_transfer();
		break;
	}
	case 2:
	{
		compute_samples(659);
		Init_DMA(E5_Buffer, SIZE_E5);
		DMA0_start_transfer();
		break;
	}
	case 3:
	{
		compute_samples(880);
		Init_DMA(A5_Buffer, SIZE_A5);
		DMA0_start_transfer();
		break;
	}
	}
}

/*
 * Brief     : Computes values of the generated samples in DAC buffer as well as
 * samples per period for a tone takes the frequency of the tone in input and returns void
 *
 * Parameters: frequency
 *
 * Return    : NULL
 */

void compute_samples(uint16_t frequency){
	samples_frequency = frequency;
	samples_per_period = (DMA_SAMPLE_FREQ)/frequency;
	samples_generated = SIZE/samples_per_period;
	samples_generated *= samples_per_period;
}
