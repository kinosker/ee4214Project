/*
 * myButton.c
 *
 *  Created on: Mar 17, 2016
 *      Author: KaiHsiang
 */
#include "myButton.h"
#include "xgpio.h"
#include "xparameters.h"


volatile char buttonPress = BUTTON_INIT;


// return 1 if left button is pressed
char myButton_checkLeft()
{
	return (buttonPress & BUTTON_LEFT_PRESS);
}

// return 1 if right button is pressed
char myButton_checkRight()
{
	return (buttonPress & BUTTON_RIGHT_PRESS);
}

// return 1 if up button is pressed
char myButton_checkUp()
{
	return (buttonPress & BUTTON_UP_PRESS);

}

// return 1 if down button is pressed
char myButton_checkDown()
{
	return (buttonPress & BUTTON_DOWN_PRESS);
}

// return 1 if center button is pressed
char myButton_checkCenter()
{
	return (buttonPress & BUTTON_CENTER_PRESS);
}






void myButton_int_handler(XGpio *gpPB) //Should be very short (in time). In a practical program, don't print etc.
{
	//clear the interrupt flag. if this is not done, gpio will keep interrupting the microblaze.--


	//add debounce

    print("Starting INT\r\n");
	// --Possible to use (XGpio*)arg instead of &gpPB
	XGpio_InterruptClear(gpPB,1);
	 //Read the state of the push buttons.
	buttonPress = XGpio_DiscreteRead(gpPB, 1);
}


int init_myButton(XGpio *gpPB)
{

	//initialize button
	xil_printf("Initializing PB\r\n");
	XGpio_Initialize(gpPB, XPAR_GPIO_0_DEVICE_ID);
	XGpio_SetDataDirection(gpPB, 1, 0x000000FF);

	//initialize interrupt
	XGpio_InterruptGlobalEnable(gpPB);
	XGpio_InterruptEnable(gpPB,1);

	register_int_handler(XPAR_MICROBLAZE_0_AXI_INTC_AXI_GPIO_0_IP2INTC_IRPT_INTR, myButton_int_handler, gpPB);
	enable_interrupt(XPAR_MICROBLAZE_0_AXI_INTC_AXI_GPIO_0_IP2INTC_IRPT_INTR);

}
