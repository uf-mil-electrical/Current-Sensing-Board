/*
 * gpio.h
 *
 *  Created on: Jan 19, 2022
 *      Author: Ethan Reussow
 */

#ifndef GPIO_H_
#define GPIO_H_
//*****************************************************************************
//
// Dependencies
//
//*****************************************************************************
#include <stdint.h>
#include <stdbool.h>

//*****************************************************************************
//
// Macros
//
//*****************************************************************************
#define BIT7_bm (1<<7) //Equal to 0b10000000
#define BIT6_bm (1<<6) //Equal to 0b01000000
#define BIT5_bm (1<<5) //etc.
#define BIT4_bm (1<<4)
#define BIT3_bm (1<<3)
#define BIT2_bm (1<<2)
#define BIT1_bm (1<<1)
#define BIT0_bm (1<<0) //Equal to 0b00000001
#define DEBUG_LED_ON 0
#define DEBUG_LED_OFF 0x40
#define DEBUG_LED_PIN_bm 0x40
//*****************************************************************************
//
// Function Prototypes
//
//*****************************************************************************
/*------------------------------------------------------------------------------
  gpio_init --

  Description:
    initializes the relevant GPIO modules and ports within the TM4C123GH6PM

  Input(s): N/A
  Output(s): N/A
------------------------------------------------------------------------------*/
void gpio_init(void);

#endif /* GPIO_H_ */
