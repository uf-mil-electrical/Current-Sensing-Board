

/**
 * main.c
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"

// Additional defines listed here for ease of use
#define BIT7_bm (1<<7)
#define BIT6_bm (1<<6)
#define BIT5_bm (1<<5)
#define BIT4_bm (1<<4)
#define BIT3_bm (1<<3)
#define BIT2_bm (1<<2)
#define BIT1_bm (1<<1)
#define BIT0_bm (1<<0)

int main(void)
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

    // Configures port B pin 6 as an output
    GPIO_PORTB_DIR_R = BIT6_bm;

  /*3. Configure the GPIOAFSEL register to program each bit as a GPIO or alternate pin. If an alternate
    pin is chosen for a bit, then the PMCx field must be programmed in the GPIOPCTL register for
    the specific peripheral required. There are also two registers, GPIOADCCTL and GPIODMACTL,
    which can be used to program a GPIO pin as a ADC or μDMA trigger, respectively.*/

    // Sets every pin in port B as a GPIO pin
    GPIO_PORTB_AFSEL_R = 0;

  /*4. Set the drive strength for each of the pins through the GPIODR2R, GPIODR4R, and GPIODR8R
    registers.*/

    // By Default all GPIO pins have a 2mA drive strength
    GPIO_PORTB_DR2R_R = 0xFF;

  /*5. Program each pad in the port to have either pull-up, pull-down, or open drain functionality through
    the GPIOPUR, GPIOPDR, GPIOODR register. Slew rate may also be programmed, if needed,
    through the GPIOSLR register.*/

    // Makes port B pin 6 have a pull up resistor
    GPIO_PORTB_PUR_R = BIT6_bm;


  /*6. To enable GPIO pins as digital I/Os, set the appropriate DEN bit in the GPIODEN register. To
    enable GPIO pins to their analog function (if available), set the GPIOAMSEL bit in the
    GPIOAMSEL register. */

    // Enables digital functions for port B pin 6
    GPIO_PORTB_DEN_R = BIT6_bm;

  /*7. Program the GPIOIS, GPIOIBE, GPIOEV, and GPIOIM registers to configure the type, event,
    and mask of the interrupts for each port.*/

    // Did not set any registers in step 7


    GPIO_PORTB_DATA_R = 0;
    while(1);
	return 0;
}
