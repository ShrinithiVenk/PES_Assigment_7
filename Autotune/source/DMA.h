#ifndef _DMA_H_
#define _DMA_H_

/*
 * Brief     : Initializes the DMA (clock gating to DMA and DMAMUX, setting
 * source and destination byte size to transfer at once, sets
 * values as source address increments but destination address is same
 * sets for interrupt and DMAMUX for TPM0)
 *
 * Parameters: source, count
 *
 * Return    : NULL
 */
void Init_DMA(uint16_t *, uint32_t);

/*
 * Brief     : Sets source address, destination address, number of bytes to
 * transfer, clears done flag and enables the flag
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */
void DMA0_start_transfer();

/*
 * Brief     : Interrupt that occurs when the buffer is full
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */

void DMA0_IRQHandler();
#endif
