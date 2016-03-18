`/*
 * project_core0.c
 *
 *  Created on: Mar 17, 2016
 *      Author: KaiHsiang
 */

#include "xmk.h"
#include <xparameters.h>
#include "xmbox.h"
#include "xstatus.h"
#include <pthread.h>
#include <errno.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/timer.h>
#include <stdio.h>



#defined PRIOR_MAILBOX_SEND 1
// mailbox declaration
//#define MY_CPU_ID 1
#define MY_CPU_ID XPAR_CPU_ID
#define MBOX_DEVICE_ID		XPAR_MBOX_0_DEVICE_ID






/************************** Variable Definitions ****************************/

/************************** Threading variables ****************************/

pthread_attr_t attr;

pthread_t tid_mailbox;


/************************** Scheduling variables ****************************/

struct sched_param sched_par;


/************************** Thread Synchronisation variables ****************************/
static XMbox Mbox;	/* Instance of the Mailbox driver */





typedef struct 
{

  int dir,speed,x,y;

} ball_msg;


int main_prog(void);

int main (void) {

	print("-- Entering main() uB1 SENDER--\r\n");
	xilkernel_init();
	xmk_add_static_thread(main_prog,0);
	xilkernel_start();
  	//Start Xilkernel
	xilkernel_main ();
  
  	//Control does not reach here

  	return 1;
  
}

int main_prog(void) 
{   // This thread is statically created (as configured in the kernel configuration) and has priority 0 (This is the highest possible)

  int ret;
 


  	/************************** Mailbox Init ****************************/

  	XMbox_Config *ConfigPtr;
  	int Status;



  	ConfigPtr = XMbox_LookupConfig(MBOX_DEVICE_ID );
  		if (ConfigPtr == (XMbox_Config *)NULL) {
  			 print("-- Error configuring Mbox uB1 Sender--\r\n");
  			return XST_FAILURE;
  		}

  	Status = XMbox_CfgInitialize(&Mbox, ConfigPtr, ConfigPtr->BaseAddress);
  		if (Status != XST_SUCCESS) {
  				 print("-- Error initializing Mbox uB1 Sender--\r\n");
  				return XST_FAILURE;


  	pthread_attr_init(&attr);						// get attribute for thread.

  

  	/************************** Controller Threads Init ****************************/

	sched_par.sched_priority = PRIOR_MAILBOX_SEND; // set priority for mailbox thread
	pthread_attr_setschedparam(&attr, &sched_par); 	// update priority attribute

	//start controller thread 1
	ret = pthread_create(&tid_mailbox, NULL, (void*) thread_func_mailbox,
			NULL );
	if (ret != 0) 
	{
		xil_printf("-- ERROR (%d) launching thread_func_mailbox...\r\n", ret);
	}
	 else 
	{
		xil_printf("Controller Thread launched with ID %d \r\n",
				tid_mailbox);
	}
   
	


}


// 1. mailbox thread should send when msgQ is received from calc threads... (Eg: calculation done for ball speed, dir, location)
// 2. mailbox thread should recv from tft processor on updates of rebounce and bar location. 
void* thread_func_mailbox()
{

	ball_msg ball;

  	ball.dir = 10;
  	ball.speed = 20;
  	ball.x = 30;
  	ball.y = 50;

  	while(1)
  	{

		XMbox_WriteBlocking(&Mbox,&ball, sizeof(ball_msg));
		sleep(1000;)

		ball.x = rand() % 200;
		ball.y = rand() % 200;


	}


}


