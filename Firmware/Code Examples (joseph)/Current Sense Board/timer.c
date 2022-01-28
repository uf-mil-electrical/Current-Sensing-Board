/*
 * timer.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Joseph
 */
//*****************************************************************************
//
// Dependencies
//
//*****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
//*****************************************************************************
//
// Macros
//
//*****************************************************************************

// NONE

//*****************************************************************************
//
// Function Definitions
//
//*****************************************************************************
void timer_init(void)
{
  /*1. Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making
    any changes.*/


  /*2. Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000. */


  /*3. Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):*/


    /*a. Write a value of 0x1 for One-Shot mode. */

    /*b. Write a value of 0x2 for Periodic mode.*/

  /*4. Optionally configure the TnSNAPS, TnWOT, TnMTE, and TnCDIR bits in the GPTMTnMR register
    to select whether to capture the value of the free-running timer at time-out, use an external
    trigger to start counting, configure an additional trigger or interrupt, and count up or down.*/



  /*5. Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).
    722 June 12, 2014
    Texas Instruments-Production Data
    General-Purpose Timers*/

  /*6. If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register
    (GPTMIMR).*/


  /*7. Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.*/

  /*8. Poll the GPTMRIS register or wait for the interrupt to be generated (if enabled). In both cases,
    the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear
    Register (GPTMICR).*/



}




