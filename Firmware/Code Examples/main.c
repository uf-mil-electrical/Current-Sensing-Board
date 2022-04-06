/**
 * main.c
 *
 * Written by Ethan Reussow Spring 2022
 */
#include <stdint.h>
#include <stdbool.h>

// User defined .h files
#include "gpio.h"
#include "timer.h"
#include "JSW_ADC.h"

// MIL .h files
#include "MIL_CAN.h"

// Tiva .h files
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"  // used for CAN1_BASE reference

/* To resolve issue with "Error #10234-D: unresolved symbols remain" when including the MIL_CAN .h file,
 * 1. go to... Project --> Properties --> Build --> Arm Linker --> File Search Path
 * 2. within the "include library file or command file (--include, -I)" box,
 * 3. click the "Add..." button, "Browse", move to your tivaware_c_series folder within you ti folder,
 * 4. within the tivaware folder move to driverlib/ccs/Debug/driverlib.lib and select this file.
 * 5. "Apply and close"
 * 6. Rebuild project and verify the error is gone.
 */

int main(void)
{
    gpio_init();    // Initializes GPIO
    timer_init();   // Initializes Timer A of Timer 0 module
    JSW_adc_init();

    //Temporarily changed to a 8bit result
    uint8_t adc_raw_data = 0xFFFF; // initial value to see if a new value has been assigned
    uint8_t *msgPT = &adc_raw_data;

    while(1) {

     /* If the timeout status bit is set indicating that the timer has reached its count limit
        then the LED will toggle ON/OFF*/
        if (TIMER0_RIS_R & TIMER_RIS_TATORIS) {

            GPIO_PORTB_DATA_R = ~(GPIO_PORTB_DATA_R & DEBUG_LED_PIN_bm); // Toggling PIN

            TIMER0_ICR_R = TIMER_ICR_TATOCINT; // Clear the interrupt status bit
        }

        while (!(ADC0_SSFSTAT0_R & ADC_SSFSTAT0_EMPTY)) { // if the ADC FIFO0 register is not empty, retrieve data from FIFO register

            adc_raw_data = ADC0_SSFIFO0_R;
        }

        MIL_CANSimpleTX(5, msgPT, 2, CAN1_BASE);

    }
	return 0;
}
