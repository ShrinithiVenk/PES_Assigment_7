#ifndef _SIN_H_
#define _SIN_H_

#include <stdint.h>

#define SIZE 			(1024)
#define SIZE_A4 		(981)
#define SIZE_D5 		(972)
#define SIZE_E5 		(1008)
#define SIZE_A5 		(972)

#define TRIG_SCALE_FACTOR  (2037)
#define HALF_PI            (3200)  // pi * TRIG_SCALE_FACTOR / 2
#define PI                 (6399)  // pi * TRIG_SCALE_FACTOR
#define THREE_HALF_PI 		(9599)
#define TWO_PI            (12799)  // 2 * pi * TRIG_SCALE_FACTOR
#define DAC_SIZE			(4095)

//tones
typedef enum {
    A4, D5, E5, A5} tones ;


/*
 * Brief     : Tests the error and sum of square error in fp_sin() function (values of sin(i))
 * takes no argument and returns void
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */

void test();


/*
 * Brief     : Calculates the samples for each tone from the sin function calculated
 * using fp_sin() also calculates the number of samples generated for each tone
 *
 * Parameters: tone, sin_buffer
 *
 * Return    : NULL
 */

void tone_to_samples(tones, uint16_t *);

/*
 * Brief     : Changes the tone based on systick
 * timer tick takes no arguments and return void
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */
void change_tone();

/*
 * Brief     : Computes values of the generated samples in DAC buffer as well as
 * samples per period for a tone takes the frequency of the tone in input and returns void
 *
 * Parameters: frequency
 *
 * Return    : NULL
 */
void compute_samples(uint16_t);
#endif
