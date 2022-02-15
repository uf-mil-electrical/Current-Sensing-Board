

/**
 * CAN.c
 * Testing CAN bus on Current Sense Board
 * Evan Andresen
 */
#include "inc/tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
// To use time library of C
#include <time.h>
#include "MIL_CAN.h"       //FIXME-----------------------------------------------------------

#define CAN1_BASE 0x40040000
#define CUR_SENS_CANID 0xfa

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

int main(void)
{
    /*
    SYSCTL_RCGC0_R = SYSCTL_RCGC0_CAN1; //clock CAN
    SYSCTL_RCGC2_GPIOA = SYSCTL_RCGC2_GPIOA; //clock portA
    GPIO_PORTA_AFSEL_R = 0b00000011; //PA0 & PA1 -> non-GPIO
    GPIO_PORTA_PCTL_R = GPIO_PCTL_PA0_CAN1RX || GPIO_PCTL_PA1_CAN1TX;//assign correct pins portA->CAN
    CAN1_CTL_R = CAN_CTL_INIT; //start software reset
    CAN1_CTL_R = 0x00; //end software reset
    */

    MIL_InitCAN(MIL_CAN_PORT_A, CAN1_BASE, 200000); //InitCAN
    SYSCTL_RCGC0_R = SYSCTL_RCGC0_CAN1; //clock CAN
    GPIO_PORTA_AFSEL_R = 0b00000011; //PA0 & PA1 -> non-GPIO
    MIL_CANPortClkEnable(MIL_CAN_PORT_A);
    uint32_t MSG = 0xbaad;   //message to send
    uint8_t *MSG_ptr = &MSG;    //message pointer



    while(1){       //send msg every 2 seconds
        MIL_CANSimpleTX(CUR_SENS_CANID,MSG_ptr,32, CAN1_BASE);        //canid, Msg_ptr, MsgLen, base------ random canid
        delay(2);
    }
	return 0;
}
