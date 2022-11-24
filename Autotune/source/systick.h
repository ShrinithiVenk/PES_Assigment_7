#ifndef _SYSTICK_H_
#define _SYSTICK_H_

typedef uint32_t ticktime_t;

/*
 * Brief     : Systick timer Initialization
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */
void Init_SysTick();

/*
 * Brief     : Interrupt Handler
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */
void SysTick_Handler();
#endif
