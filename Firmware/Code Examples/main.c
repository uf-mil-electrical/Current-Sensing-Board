/**
 * main.c
 *
 * Written by Ethan Reussow Spring 2022
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "gpio.h"
#include "timer.h"
#include "JSW_ADC.h"

int main(void)
{
    gpio_init();    // Initializes GPIO
    timer_init();   // Initializes Timer A of Timer 0 module
    JSW_adc_init();

    uint16_t adc_raw_data = 0xFFFF; // initial value to see if a new value has been assigned

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
    }
	return 0;
}
