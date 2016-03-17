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
#define BUTTON_LEFT_PRESS  4     // Bit 3 of value read
#define BUTTON_RIGHT_PRESS  8     // Bit 4 of value read
#define BUTTON_UP_PRESS  16     // Bit 3 of value read
#define BUTTON_DOWN_PRESS  2     // Bit 4 of value read
#define BUTTON_CENTER_PRESS  1     // Bit 3 of value read
#define BUTTON_INIT 0 // bar moving right

/*****************************************************************************
 **																			 *
 *																			 *
 *					---- Start of Functions Prototype ----					 *
 *																			 *
 *																			 *
 *****************************************************************************/



// return 1 if left button is pressed
char myButton_checkLeft();

// return 1 if right button is pressed
char myButton_checkRight();

// return 1 if up button is pressed
char myButton_checkUp();

// return 1 if down button is pressed
char myButton_checkDown();

// return 1 if center button is pressed
char myButton_checkCenter();

int init_myButton(XGpio *gpPB);
void myButton_int_handler(XGpio *gpPB);

#endif /* MYBUTTON_H_ */
