/*
 * timer.c
 *
 *  Created on: Jan 25, 2022
 *      Author: Ethan Reussow
 */
//*****************************************************************************
//
// Dependencies
//
//*****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/tm4c123gh6pm.h"
#include "timer.h"
//*****************************************************************************
//
// Macros
//
//*****************************************************************************
#define TIMER_PERIOD 32000000 // Corresponds to a 1 second timer period assuming a 16MHz clock and a prescaler of 0.

//*****************************************************************************
//
// Function Definitions
//
//*****************************************************************************
void timer_init(void) // Configures TIMER A within TIMER0
{

  //Enable the clock for the timer module

    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R0; //Enables clock for the TIMER0 module

  /*The GPTM is configured for One-Shot and Periodic modes by the following sequence:
    1. Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making
    any changes. */

    TIMER0_CTL_R &= ~(1 << 0); // Clears 0th bit

    // IMPORTANT: NEED TO ENABLE TAOTE BIT WHEN TRIGGERING EVENT FOR ADC

  /*2. Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000. (see page 727)*/

    TIMER0_CFG_R = 0; // For a 16/32-bit timer, this value selects the 32-bit timer configuration (see page 728)

  /*3. Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
    a. Write a value of 0x1 for One-Shot mode.
    b. Write a value of 0x2 for Periodic mode.*/

    TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD; //0x02

  /*4. Optionally configure the TnSNAPS, TnWOT, TnMTE, and TnCDIR bits in the GPTMTnMR register
    to select whether to capture the value of the free-running timer at time-out, use an external
    trigger to start counting, configure an additional trigger or interrupt, and count up or down.*/

    TIMER0_TAMR_R |= TIMER_TAMR_TACDIR; // Counts up

  /*5. Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).
   * optional: Use prescaler for timer
   *
   * IMPORTANT: When counting up, this register sets the upper bound for the timeout event.  * */

    /* The following table assumes an 80MHz clock --> period = 12.5ns(see page 711)
    Prescale (16-bit value) | # of Timer Clocks | Max Time | Units
    0x0000                          1               53.687      s
    0x0001                          2               107.374     s
    0x0002                          3               214.748     s

    Thus, for a 1 second delay assuming 16MHz clock, 16,000,000 cycles must pass. */

    TIMER0_TAILR_R = TIMER_PERIOD; //Corresponds to the macro defined above

  /*6. If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register
    (GPTMIMR). */

    // Not required here

  /*7. Set the TnEN bit in the GPTMCTL register to enable the timer and start counting. */

    TIMER0_CTL_R |= TIMER_CTL_TAEN; //0x1

  /*8. Poll the GPTMRIS register or wait for the interrupt to be generated (if enabled). In both cases,
    the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear
    Register (GPTMICR).
    If the TnMIE bit in the GPTMTnMR register is set, the RTCRIS bit in the GPTMRIS register is set,
    and the timer continues counting. In One-Shot mode, the timer stops counting after the time-out
    event. To re-enable the timer, repeat the sequence. A timer configured in Periodic mode reloads
    the timer and continues counting after the time-out event.

    For Timer A in the Timer 0 module look at the TATORIS bit within the GPTMRIS register to see when the timer
    reaches it's count limit.

    to clear the TATORIS bit go into the GPTMICR register and set the TATOCINT bit to clear the aforementioned status bit
    */

}

