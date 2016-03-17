/*
 * myButton.h
 *
 *  Created on: Mar 17, 2016
 *      Author: KaiHsiang
 */

#ifndef MYBUTTON_H_
#define MYBUTTON_H_

#include "xgpio.h"

/*****************************************************************************
 *																			 *
 *																			 *
 *					---- Start of Constant definition ----					 *
 *																			 *
 *																			 *
 ******************************************************************************/
#define BTNL  4     // Bit 3 of value read
#define BTNR  8     // Bit 4 of value read
#define BTNU  16     // Bit 3 of value read
#define BTND  2     // Bit 4 of value read
#define BTNC  1     // Bit 3 of value read
#define FLAG_BARLEFT 1 // bar moving left
#define FLAG_BARRIGHT 0 // bar moving right

/*****************************************************************************
 **																			 *
 *																			 *
 *					---- Start of Functions Prototype ----					 *
 *																			 *
 *																			 *
 *****************************************************************************/

/*****************************************************************************
 **
 * Button Interrupt
 *
 * @param  gpPB is the button in hardware.
 *
 *
 * @return
 *   - FLAG_BARLEFT if LEFT button pressed.
 *   - FLAG_BARRIGHT if RIGHT button pressed.
 *
 *****************************************************************************/

int gpPBIntHandler(XGpio gpPB);

#endif /* MYBUTTON_H_ */
