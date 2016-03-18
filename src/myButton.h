/*
 * myButton.h
 *
 *  Created on: Mar 17, 2016
 *      Author: KaiHsiang
 */

#ifndef MYBUTTON_H_
#define MYBUTTON_H_


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


 #define BUTTON_UPDATED 	1
 #define BUTTON_NOT_UPDATED 0

/*****************************************************************************
 **																			 *
 *																			 *
 *					---- Start of Functions Prototype ----					 *
 *																			 *
 *																			 *
 *****************************************************************************/


/*****************************************************************************
 **
 * Check whether the left button is pressed
 *
 * @return
 *   -> 1 if button pressed.
 *   -> 0 if not pressed
 *
 *
 ******************************************************************************/
char myButton_checkLeft();

/*****************************************************************************
 **
 * Check whether the right button is pressed
 *
 * @return
 *   -> 1 if button pressed.
 *   -> 0 if not pressed
 *
 *
 ******************************************************************************/
char myButton_checkRight();

/*****************************************************************************
 **
 * Check whether the up button is pressed
 *
 * @return
 *   -> 1 if button pressed.
 *   -> 0 if not pressed
 *
 *
 ******************************************************************************/
char myButton_checkUp();

/*****************************************************************************
 **
 * Check whether the down button is pressed
 *
 * @return
 *   -> 1 if button pressed.
 *   -> 0 if not pressed
 *
 *
 ******************************************************************************/
char myButton_checkDown();

/*****************************************************************************
 **
 * Check whether the centre button is pressed
 *
 * @return
 *   -> 1 if button pressed.
 *   -> 0 if not pressed
 *
 *
 ******************************************************************************/
char myButton_checkCenter();

/*****************************************************************************
 **
 * Initialize the hardware button
 *
 * @param *gpPB
 *
 * @return
 *   -> 1 if initialize success
 *   -> 0 if not suuccess
 *
 *
 ******************************************************************************/
int init_myButton(XGpio *gpPB);

/*****************************************************************************
 **
 * Interrupt that handle button when button is pressed
 *
 * @param *gpPB
 *
 ******************************************************************************/
void myButton_int_handler(XGpio *gpPB);

/*****************************************************************************
 **
 * Determine if the button is pressed through debouncing technique
 *
 * @param *debounceTime is the last debounced press time.
 * @param currentTime is the current time
 * 					
 *
 *
 * @return
 *   -> 1 if not debounce
 *   -> 0 if debounce happens
 *
 *
 ******************************************************************************/
int debounce(unsigned int *debounceTime, unsigned int currentTime) ;

unsigned int myButton_ticks_to_ms (unsigned int ticks);

#endif /* MYBUTTON_H_ */
