

/**
 * main.c
 */

// Includes
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"

// MIL Includes
#include "MIL_CAN.h"

// My Includes
#include "JSW_ADC.h"
#include "gpio.h"


// Additional defines listed here for ease of use
#define BIT7_bm (1<<7)
#define BIT6_bm (1<<6)
#define BIT5_bm (1<<5)
#define BIT4_bm (1<<4)
#define BIT3_bm (1<<3)
#define BIT2_bm (1<<2)
#define BIT1_bm (1<<1)
#define BIT0_bm (1<<0)

#define canid 01

int main(void)
{
 // See for example   SVN-Legacy/Subjugator SVN/Firmware/Thruster_Kill_Board/CAN_TX_Test_Bench/main.c

    // Initializes Port B pin 6 (Debug LED)
    gpio_init();



    // Initializes ADC for port D pins 0-2
    JSW_adc_init();

    // Initializes CAN1 for Port A
    MIL_CANPortClkEnable(MIL_CAN_PORT_A);
    MIL_InitCAN(MIL_CAN_PORT_A, CAN1_BASE, 200000);

    uint8_t message = 15;
    uint8_t *msgPT = &message;

    // Send CAN message
    MIL_CANSimpleTX(canid, msgPT, 8, CAN1_BASE);


}
