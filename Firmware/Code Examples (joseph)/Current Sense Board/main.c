

/**
 * main.c
 */

// Includes
#include <stdbool.h>
#include <stdint.h>
/*
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
*/

#include "inc/tm4c123gh6pm.h"

// MIL Includes
#include "MIL_CAN.h"

#include "timer.h"
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

#define canid 15
#define CAN1_BASE 0x40041000
#define DEBUG_LED_PIN_bm 0x40

int main(void)
{
 // See for example   SVN-Legacy/Subjugator SVN/Firmware/Thruster_Kill_Board/CAN_TX_Test_Bench/main.c

    gpio_init();    // Initializes Port B pin 6 (Debug LED)
    JSW_adc_init();    // Initializes ADC for port D pins 0-2
    timer_init();   // Initializes Timer A of Timer 0 module


    // Initializes CAN1 for Port A
    MIL_CANPortClkEnable(MIL_CAN_PORT_A);
    MIL_InitCAN(MIL_CAN_PORT_A, CAN1_BASE, 200000);

    uint8_t adc_raw_data = 0xFF; // initial value to see if a new value has been assigned
    uint8_t *msgPT = &adc_raw_data;

    // Send CAN message
 //   MIL_CANSimpleTX(canid, msgPT, 8, CAN1_BASE);

    while(1) {

      /* If the timeout status bit is set indicating that the timer has reached its count limit
         then the LED will toggle ON/OFF*/
         if (TIMER0_RIS_R & TIMER_RIS_TATORIS) {

             GPIO_PORTB_DATA_R = ~(GPIO_PORTB_DATA_R & DEBUG_LED_PIN_bm); // Toggling PIN

             TIMER0_ICR_R = TIMER_ICR_TATOCINT; // Clear the interrupt status bit
         }

         while (!(ADC0_SSFSTAT0_R & ADC_SSFSTAT0_EMPTY)) { // if the ADC FIFO0 register is not empty, retrieve data from FIFO register

             adc_raw_data = ADC0_SSFIFO0_R;

             MIL_CANSimpleTX(canid, msgPT, 2, CAN1_BASE);    // Send CAN message

         }
    }
    return 0;
}
