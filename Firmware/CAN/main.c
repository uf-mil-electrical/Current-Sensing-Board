

/**
 * CAN.c
 * Testing CAN bus on Current Sense Board
 * Evan Andresen
 */
#include "inc/tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
int main(void)
{
    SYSCTL_RCGC0_R = SYSCTL_RCGC0_CAN1; //clock CAN
    SYSCTL_RCGC2_GPIOA = SYSCTL_RCGC2_GPIOA; //clock portA
    GPIO_PORTA_AFSEL_R = 0b00000011; //PA0 & PA1 -> non-GPIO
    GPIO_PORTA_PCTL_R = GPIO_PCTL_PA0_CAN1RX || GPIO_PCTL_PA1_CAN1TX;//assign correct pins portA->CAN
    CAN1_CTL_R = CAN_CTL_INIT; //start software reset
    CAN1_CTL_R = 0x00; //end software reset






	return 0;
}
