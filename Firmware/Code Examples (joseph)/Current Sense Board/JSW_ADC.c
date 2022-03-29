/*
 * ADC.c
 *
 *  Created on: Jan 25, 2022
 *      Author: Joseph Wilkinson
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
#define BIT7_bm (1<<7)
#define BIT6_bm (1<<6)
#define BIT5_bm (1<<5)
#define BIT4_bm (1<<4)
#define BIT3_bm (1<<3)
#define BIT2_bm (1<<2)
#define BIT1_bm (1<<1)
#define BIT0_bm (1<<0)

#define AIN5_bm 0x5
#define AIN6_bm 0x6
#define AIN7_bm 0x7
//
//*****************************************************************************

// NONE

//*****************************************************************************
//
//  Configures ADC 0 SS 0 to to sample AIN7 (PD0; V), AIN6 (PD1; I1), then AIN5 (PD2; I2)
//
//*****************************************************************************
void JSW_adc_init(void)
{
// ADC inputs are port D pin 0-2; AIN7-5

    // MODULE INITIALIZATION

  /*1. Enable the ADC clock using the RCGCADC register (see page 352).   */

    SYSCTL_RCGCADC_R = BIT0_bm;     // Enables and provides a clock to ADC module 0 in Run mode

  /*2. Enable the clock to the appropriate GPIO modules via the RCGCGPIO register (see page 340).
    To find out which GPIO ports to enable, refer to “Signal Description” on page 801.*/

    SYSCTL_RCGCGPIO_R |= BIT3_bm;    // Enables and provides a clock to GPIO Port D in Run mode.

  /*3. Set the GPIO AFSEL bits for the ADC input pins (see page 671). To determine which GPIOs to
    configure, see Table 23-4 on page 1344.*/

    GPIO_PORTD_AFSEL_R |= BIT0_bm | BIT1_bm | BIT2_bm;   // Sets Port D pins 0-2 as peripheral signals controlled by the alternate hardware function.

  /*4. Configure the AINx signals to be analog inputs by clearing the corresponding DEN bit in the
    GPIO Digital Enable (GPIODEN) register (see page 682).*/

    GPIO_PORTD_DEN_R |= BIT0_bm | BIT1_bm | BIT2_bm;     // Enables digital functions for Port D pins 0-2

  /*5. Disable the analog isolation circuit for all ADC input pins that are to be used by writing a 1 to
    the appropriate bits of the GPIOAMSEL register (see page 687) in the associated GPIO block.
    June 12, 2014 817
    Texas Instruments-Production Data
    Tiva™ TM4C123GH6PM Microcontroller*/

    GPIO_PORTD_AMSEL_R |= BIT0_bm | BIT1_bm | BIT2_bm;   // Enables analog functions for Port D pins 0-2

  /*6. If required by the application, reconfigure the sample sequencer priorities in the ADCSSPRI
    register. The default configuration has Sample Sequencer 0 with the highest priority and Sample
    Sequencer 3 as the lowest priority*/

        // We do not need to change priority of Sample Sequencers


    // SAMPLE SEQUENCER CONFIGURATION

  /*1. Ensure that the sample sequencer is disabled by clearing the corresponding ASENn bit in the
    ADCACTSS register. Programming of the sample sequencers is allowed without having them
    enabled. Disabling the sequencer during programming prevents erroneous execution if a trigger
    event were to occur during the configuration process.*/

    ADC0_ACTSS_R = 0;  // Disables sample sequencers for ADC 0 for programming purposes (enabled in step 7)

  /*2. Configure the trigger event for the sample sequencer in the ADCEMUX register.*/

    ADC0_EMUX_R = ADC_EMUX_EM0_TIMER;    // Sets ADC 0 SS 0 to be triggered by a timer
    // In addition, the trigger must be enabled with the TnOTE bit in the GPTMCTL register (page 737)

  /*3. When using a PWM generator as the trigger source, use the ADC Trigger Source Select
    (ADCTSSEL) register to specify in which PWM module the generator is located. The default
    register reset selects PWM module 0 for all generators.*/

    // Not using PWM as trigger source

  /*4. For each sample in the sample sequence, configure the corresponding input source in the
    ADCSSMUXn register.*/

    // Configures ADC 0 SS 0 to to input AIN7 (PD0; V), AIN6 (PD1; I1), then AIN5 (PD2; I2)
    ADC0_SSMUX0_R = (AIN7_bm << ADC_SSMUX0_MUX0_S) | (AIN6_bm << ADC_SSMUX0_MUX1_S) | (AIN5_bm << ADC_SSMUX0_MUX2_S);

  /*5. For each sample in the sample sequence, configure the sample control bits in the corresponding
    nibble in the ADCSSCTLn register. When programming the last nibble, ensure that the END bit
    is set. Failure to set the END bit causes unpredictable behavior.*/

    ADC0_SSCTL0_R = ADC_SSCTL0_END2;    // Sets the second (index starts at 0) sample as the last sample of the sequence

  /*6. If interrupts are to be used, set the corresponding MASK bit in the ADCIM register.*/

    // The ADC is not generating any interrupts

  /*7. Enable the sample sequencer logic by setting the corresponding ASENn bit in the ADCACTSS
    register.*/

    ADC0_ACTSS_R = ADC_ACTSS_ASEN0;  // Enables sample sequencer 0 for ADC 0
}





