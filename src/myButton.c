/*
 * myButton.c
 *
 *  Created on: Mar 17, 2016
 *      Author: KaiHsiang
 */

#include "xgpio.h"
#include "xmk.h"
#include "xparameters.h"
#include "myButton.h"
#include <sys/timer.h>
#include <sys/process.h>
#include <sys/decls.h>
#include <sys/xtrace.h>

volatile char buttonPress = BUTTON_INIT, prevButtonPress = BUTTON_INIT, buttonFlag;
unsigned int myButton_deboubceTime, myButton_currentTime = 0;
unsigned int myButton_leftPressTime = 0, myButton_rightPressTime = 0;


// Debouncing function. Returns TRUE if this interrupt was not caused by a bouncing switch
int debounce(unsigned int *debounceTime, unsigned int currentTime) {

	if ((currentTime - *debounceTime) > 100) 
	{
		*debounceTime = currentTime;
		return 1;
	} else {
		return 0;
	}
}

// return "hold time" in ms if left button is pressed
// return 0 if left button is not pressed
int myButton_checkLeft() 
{
	if (buttonPress & BUTTON_LEFT_PRESS)
	{
		myButton_currentTime =  myButton_ticks_to_ms(xget_clock_ticks()); // get current time elapsed in ms
		return myButton_leftPressTime - myButton_currentTime;
	}
	else
	{
		return 0;
	}
}


// return "hold time" in ms if left button is pressed
// return 0 if left button is not pressed
int myButton_checkRight() 
{
	if (buttonPress & BUTTON_LEFT_PRESS)
	{
		myButton_currentTime =  myButton_ticks_to_ms(xget_clock_ticks()); // get current time elapsed in ms
		return myButton_rightPressTime - myButton_currentTime;
	}
	else
	{
		return 0;
	}
}

// return 1 if up button is pressed
char myButton_checkUp() {
	return (buttonPress & BUTTON_UP_PRESS);
}

// return 1 if down button is pressed
char myButton_checkDown() {
	return (buttonPress & BUTTON_DOWN_PRESS);
}

// return 1 if center button is pressed
char myButton_checkCenter() {
	return (buttonPress & BUTTON_CENTER_PRESS);
}

void myButton_int_handler(XGpio *gpPB) //Should be very short (in time). In a practical program, don't print etc.
{
	//clear the interrupt flag. if this is not done, gpio will keep interrupting the microblaze.--

	//add debounce

	myButton_currentTime =  myButton_ticks_to_ms(xget_clock_ticks()); // get current time elapsed in ms

	if (debounce(&myButton_deboubceTime, myButton_currentTime)) 
	{
		//Read the state of the push buttons.
		buttonPress = XGpio_DiscreteRead(gpPB, 1);
		xil_printf("button value: %d\r\n", buttonPress);

		if(buttonPress & BUTTON_LEFT_PRESS & (~prevButtonPress)) // left press and prevButton not press (110)
		{
			myButton_leftPressTime = myButton_currentTime;
		}

		if(buttonPress & BUTTON_RIGHT_PRESS & (~prevButtonPress)) // right press and prevButton not press (110)
		{
			myButton_rightPressTime = myButton_currentTime;
		}

		prevButtonPress = buttonPress;

	} else
		xil_printf("bounce\r\n");

	XGpio_InterruptClear(gpPB, 1);

}

int init_myButton(XGpio *gpPB) {

	//initialize button
	xil_printf("Initializing PB\r\n");
	XGpio_Initialize(gpPB, XPAR_GPIO_0_DEVICE_ID);
	XGpio_SetDataDirection(gpPB, 1, 0x000000FF);

	//initialize interrupt
	XGpio_InterruptGlobalEnable(gpPB);
	XGpio_InterruptEnable(gpPB, 1);

	register_int_handler(
			XPAR_MICROBLAZE_0_AXI_INTC_AXI_GPIO_0_IP2INTC_IRPT_INTR,
			myButton_int_handler, gpPB);
	enable_interrupt(XPAR_MICROBLAZE_0_AXI_INTC_AXI_GPIO_0_IP2INTC_IRPT_INTR);

}

unsigned int myButton_ticks_to_ms(unsigned int ticks) {
	return (ticks * (SYSTMR_INTERVAL / SYSTMR_CLK_FREQ_KHZ));
}
