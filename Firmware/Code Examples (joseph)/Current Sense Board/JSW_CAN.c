/*
 * CAN.c
 *
 *  Created on: Feb 7, 2022
 *      Author: Joseph Wilkinson
 */
#include "inc/tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>

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
    // Initializes CAN1 RX to Port A pin 0 and CAN1 TX to Port A pin 1

    SYSCTL_RCGC0_R = SYSCTL_RCGC0_CAN1; //enables clock to CAN controller
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; //enables clock to portA
    GPIO_PORTA_AFSEL_R = BIT0_bm | BIT1_BM; //PA0 & PA1 -> non-GPIO
    GPIO_PORTA_PCTL_R = GPIO_PCTL_PA0_CAN1RX | GPIO_PCTL_PA1_CAN1TX;//assign correct pins portA->CAN

    CAN1_CTL_R = CAN_CTL_INIT | CAN_CTL_CCE; //starts initialization state and allows write accesses to the CANBIT register

    /* set the CAN Bit Timing (CANBIT) register and configure each
    message object. If a message object is not needed, label it as not valid by clearing the MSGVAL bit
    in the CAN IFn Arbitration 2 (CANIFnARB2) register. Otherwise, the whole message object must
    be initialized, as the fields of the message object may not have valid information, causing unexpected
    results. */

    /*  Notes: CAN devices should be run at 200k bps
    *        and PCBs on the network should have on
    *        board termination resistors  - from Common-Misc\MIL_Tiva_Drivers\MIL_CAN\MIL_CAN.c*/

    CAN1_CTL_R = 0x00; //ends initialization state






    return 0;
}

