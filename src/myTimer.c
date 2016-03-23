// /*
//  * project_core0.c
//  *
//  *  Created on: Mar 17, 2016
//  *      Author: -1
//  */



#include "xparameters.h"
#include "xtmrctr_l.h"
#include "xil_io.h"
#include "xintc.h"

#define FPS 25

#define TIMER_TCR 		0x08 //Timer/Counter Register 1
#define TIMER_TCSR1_T1INT 	0x00000100 	// Timer1 Interrupt bit position (8) 
#define TIMER_CTR_NUMBER 0
#define XPAR_AXI_TIMER_1_PERIOD  1/XPAR_AXI_TIMER_1_CLOCK_FREQ_HZ
#define TIMING_INTERVAL 	1/FPS
#define LOAD_TIME	TIMING_INTERVAL/ XPAR_AXI_TIMER_1_PERIOD - 4

//   TIMING_INTERVAL = (TLR + 4) x AXI_CLOCK_PERIOD


static XTmrCtr xTickTimerInstance; // timer instance




void myTimer_clear_interrupt()
{
	// clear timer 1 interrupt, write ... get register then set it at bit position 8 to clear interrupt

	Xil_Out32( XPAR_AXI_TIMER_1_BASEADDR + TIMER_TCSR, Xil_In32(XPAR_AXI_TIMER_1_BASEADDR+TIMER_TCSR) | TIMER_TCSR1_T1INT);
}

void myTimer_int_handler()
{
	myTimer_clear_interrupt
}





void myTimer_init()
{

/*
1. Clear the timer enable bits in control registers (TCSR0 and TCSR1).
2. Write the lower 32-bit timer/counter load register (TLR0).
3. Write the higher 32-bit timer/counter load register (TLR1).
4. Set the CASC bit in Control register TCSR0.
5. Set other mode control bits in control register (TCSR0) as needed.
6. Enable the timer in Control register (TCSR0).
*/



		int status;

		/* Initialise the timer/counter. */
		status = XTmrCtr_Initialize( &xTickTimerInstance, XPAR_AXI_TIMER_1_DEVICE_ID ); 


		/* Configure the timer interrupt handler.  This installs the handler
		directly, rather than through the Xilinx driver.  This is done for
		efficiency. */
		XTmrCtr_SetHandler( &xTickTimerInstance, ( void * ) myTimer_int_handler, NULL );


		/* Set the period for the timer interrupt to happen */
		XTmrCtr_SetResetValue( &xTickTimerInstance, TIMER_CTR_NUMBER, LOAD_TIME );


		/* Enable the interrupts.  Auto-reload mode is used to generate a
			periodic tick.  Note that interrupts are disabled when this function is
			called, so interrupts will not start to be processed until the first
			task has started to run. */
		XTmrCtr_SetOptions( &xTickTimerInstance, TIMER_CTR_NUMBER, ( XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION | XTC_DOWN_COUNT_OPTION ) );

		

		/* Start the timer. */
		XTmrCtr_Start( &xTickTimerInstance, TIMER_CTR_NUMBER );


}




