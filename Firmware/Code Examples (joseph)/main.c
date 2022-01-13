

/**
 * main.c
 */

#include "inc/tm4c123gh6pm.h"

int main(void)
{
    GPIO_PORTB_DATA_R = 0;
    GPIO_PORTB_DIR_R = 0x40;
    while(1);

	return 0;
}
