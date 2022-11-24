#include<stdint.h>
#include "MKL25Z4.h"
#include <stdio.h>
#include "DMA.h"
#include "DAC.h"

uint16_t *store_source;
uint32_t DMA_byte_count = 0;

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

void Init_DMA(uint16_t *source, uint32_t count){

	//copy data for saving
	store_source = source;
	DMA_byte_count = count*2;
	//provide clock to DMA and DMAMUX
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;

	//Disable DMA channel to allow config
	DMAMUX0->CHCFG[0] = 0;

	//Generate DMA Interrupt when done
	//Increment source, transfer words (16bits)
	//Enable peripheral request
	//DMA0->DMA[0].DCR &=	~DMA_DCR_CS_MASK ;
	DMA0->DMA[0].DCR |= DMA_DCR_EINT_MASK | DMA_DCR_SINC_MASK |
			DMA_DCR_SSIZE(2) | DMA_DCR_DSIZE(2) |
			DMA_DCR_ERQ_MASK | DMA_DCR_CS_MASK; //| DMA_DCR_DINC_MASK;

	//configure NVIC for DMA ISR
	NVIC_SetPriority(DMA0_IRQn, 2);
	NVIC_ClearPendingIRQ(DMA0_IRQn);
	NVIC_EnableIRQ(DMA0_IRQn);

	//Set DMA MUX channel to use TPM0 overflow as trigger
	DMAMUX0->CHCFG[0] = DMAMUX_CHCFG_SOURCE(54);
}

/*
 * Brief     : Sets source address, destination address, number of bytes to
 * transfer, clears done flag and enables the flag
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */

void DMA0_start_transfer(){
	//initialize source and destination pointers
	DMA0->DMA[0].SAR = DMA_SAR_SAR((uint32_t) store_source);
	DMA0->DMA[0].DAR = DMA_DAR_DAR((uint32_t) (&(DAC0->DAT[0])));
	//byte count
	DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(DMA_byte_count);
	//clear done flag
	DMA0->DMA[0].DSR_BCR &= ~DMA_DSR_BCR_DONE_MASK;
	//set enable flag
	DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL_MASK;
			//| DMAMUX_CHCFG_TRIG_MASK;

}

/*
 * Brief     : Interrupt that occurs when the buffer is full
 *
 * Parameters: NULL
 *
 * Return    : NULL
 */

void DMA0_IRQHandler(void){
	//clear done flag
	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;
	//start_DMA_again
	DMA0_start_transfer();
}
