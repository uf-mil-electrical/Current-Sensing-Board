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

int main(void)
{
    gpio_init();    // Initializes GPIO
    timer_init();   // Initializes Timer A of Timer 0 module

    while(1) {

     /* If the timeout status bit is set indicating that the timer has reached its count limit
        then the LED will toggle ON/OFF*/
        if ((TIMER0_RIS_R & TIMER_RIS_TATORIS) == TIMER_RIS_TATORIS) {

            GPIO_PORTB_DATA_R = ~(GPIO_PORTB_DATA_R & DEBUG_LED_PIN_bm); // Toggling PIN

            TIMER0_ICR_R = TIMER_ICR_TATOCINT; // Clear the interrupt status bit
        }
    }
	return 0;
}
