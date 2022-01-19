/**
 * main.c
 *
 * Written by Ethan Reussow Spring 2022
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "gpio.h"

int main(void)
{
    gpio_init();    // Initializes GPIO

    GPIO_PORTB_DATA_R = 0;

    while(1);
	return 0;
}
