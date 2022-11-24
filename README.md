# PES_Assigment_7 AUTOTUNE
The assignment is made using C language on MCUXpresso IDE with KL25Z MCU.

### FILES DESCRIPTION:

The assignment consists of following .c and their corresponding .h files:

             Autotune.c: Contains the main function and the function to change the tones after one second.

             TPM.c: Contains function to initialize the TPM0 module, TPM1 module for DMA transfer. Also contains the function to start the timer.

             DMA.c: Contains the functions to initialize the DMA0 module and transfer the data from a buffer to the DAC. Also contains the DMA Interrupt handler for                  starting over the DMA cycle again when buffer is full.

             DAC.c: contains a function to initialize as well as enable the DAC module for data transfer.

             ADC.c: Contains function to initialize the ADC0 module for converting the data coming from the DAC. It also contains the function to initialize the TPM1                  module used to on interrupt generation to read the samples from ADC. Further, a function to analyse the ADC buffer is also present which computes the                    minimum, maximum and average values of the buffer.

             systick.c: This file has a function that initializes the systick module used for generating one second delay (for a tone to play for one second). The file                also contains the systick handler as the timer is running on interrupt basis.

             Sin.c: This file contains all the functions related to the tones and changing them.
             
             
Also Includes the oscillopscope outputs of the generated tones as sinusoidal outputs.
