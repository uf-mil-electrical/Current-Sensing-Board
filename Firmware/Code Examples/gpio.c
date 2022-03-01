/*
 * gpio.c
 *
 *  Created on: Jan 19, 2022
 *      Author: Ethan Reussow
 */
//*****************************************************************************
//
// Dependencies
//
//*****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "gpio.h"
//*****************************************************************************
//
// Macros
//
//*****************************************************************************

// NONE
#define AIN7 0x7
#define AIN6 0x6
#define AIN5 0x5

/*register_ = (AIN7 << ADC_SSMUX0_MUX0_S) |
            (AIN6 << ADC_SSMUX1_MUX0_S) |
            (AIN5 << ADC_SSMUX2_MUX0_S);

            need to use for ADC GPIO init stuff I think*/

//*****************************************************************************
//
// Function Definitions
//
//*****************************************************************************
void gpio_init(void)
{
  /*1. Enable the clock to the port by setting the appropriate bits in the RCGCGPIO register (see
    page 340). In addition, the SCGCGPIO and DCGCGPIO registers can be programmed in the
    same manner to enable clocking in Sleep and Deep-Sleep modes.

    The General-Purpose Input/Output Run Mode Clock Gating Control Register (RCGCGPIO) allows
    a module to be provided with clock and access to module registers. Its purpose is to only
    enable the required modules when desired in order to reduce power consumption.*/

    SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R1; // Enables PORTB

    /* If ports A and B were enabled, these are equivalent ways for writing the same value to the register
    SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R1;         // method 2
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;

    SYSCTL_RCGCGPIO_R = 0x3;                        // method 3

    SYSCTL_RCGCGPIO_R = 0b11;                       // method 4
    */

  /*2. Set the direction of the GPIO port pins by programming the GPIODIR register. A write of a 1
    indicates output and a write of a 0 indicates input.*/

    GPIO_PORTB_DIR_R = BIT6_bm; //PORTB Pin 6 is configured as an output

  /*3. Configure the GPIOAFSEL register to program each bit as a GPIO or alternate pin. If an alternate
    pin is chosen for a bit, then the PMCx field must be programmed in the GPIOPCTL register for
    the specific peripheral required. There are also two registers, GPIOADCCTL and GPIODMACTL,
    which can be used to program a GPIO pin as a ADC or μDMA trigger, respectively.*/

    GPIO_PORTB_AFSEL_R = 0; //The associated pin functions as a GPIO and is controlled by the GPIO registers

  /*4. Set the drive strength for each of the pins through the GPIODR2R, GPIODR4R, and GPIODR8R
    registers (see pg. 673-675).*/

    GPIO_PORTB_DR2R_R = 0xFF; //By default all GPIO pins have a 2mA drive strength.

  /*5. Program each pad in the port to have either pull-up, pull-down, or open drain functionality through
    the GPIOPUR, GPIOPDR, GPIOODR register. Slew rate may also be programmed, if needed,
    through the GPIOSLR register.*/

    GPIO_PORTB_PUR_R = BIT6_bm; //Makes pin 6 have a pull up resistor (Does not really matter in this case)

  /*6. To enable GPIO pins as digital I/Os, set the appropriate DEN bit in the GPIODEN register. To
    enable GPIO pins to their analog function (if available), set the GPIOAMSEL bit in the
    GPIOAMSEL register. */

    GPIO_PORTB_DEN_R = BIT6_bm; //Enables digital functions for the corresponding pin

  /*7. Program the GPIOIS, GPIOIBE, GPIOEV, and GPIOIM registers to configure the type, event,
    and mask of the interrupts for each port.*/

    // Did not set any registers in step 7.
}

