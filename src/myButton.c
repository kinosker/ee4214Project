/*
 * myButton.c
 *
 *  Created on: Mar 17, 2016
 *      Author: KaiHsiang
 */
#include "myButton.h"
#include "xgpio.h"

int gpPBIntHandler(XGpio gpPB) //Should be very short (in time). In a practical program, don't print etc.
{
	unsigned char val;
	//clear the interrupt flag. if this is not done, gpio will keep interrupting the microblaze.--
	// --Possible to use (XGpio*)arg instead of &gpPB
	XGpio_InterruptClear(&gpPB,1);
	 //Read the state of the push buttons.
	val = XGpio_DiscreteRead(&gpPB, 1);

	if(val & BTNL)
		return FLAG_BARLEFT;
	if(val & BTNR)
		return FLAG_BARRIGHT;

	//xil_printf("PB event, val = %d \r\n", val); // for testing.
}

