/*
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


#define MAX_RAND_SLEEP    30   // for snatching colour sema


// 5 Priority levels for this processor.
#define PRIO_CONTROLLER 1
//#define PRIO_BAR    2
#define PRIO_BALL       2
#define PRIO_BRICKS     3
#define PRIO_SCORE_ZONE 5


// mailbox declaration
#define MBOX_DEVICE_ID		XPAR_MBOX_0_DEVICE_ID

#define MAX_BRICKS_THREAD 10

 // put me in brick? display?

#define ALL_COL_X   COL_1_X, \ 
                    COL_2_X, \
                    COL_3_X, \
                    COL_4_X, \
                    COL_5_X, \
                    COL_6_X, \
                    COL_7_X, \ 
                    COL_8_X, \
                    COL_9_X, \
                    COL_10_X














typedef struct 
{

  int dir,speed,x,y;

} ball_msg;


/**************** Global Thread Synchronisation variables **********************/

sem_t sem_colour_yellow;
sem_t sem_colour_background;
//pthread_mutex_t mutex_col;
//struct barrier_t barrier_col;


/************************** Function Prototype  ****************************/


int main_prog(void);
int createThreads(void);
void* thread_func_controller();
void* thread_func_ball();
void* thread_func_brick(int col_x);



int main (void) 
{

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

    int mailbox_status = 0;
    static XMbox Mbox; /* Instance of the Mailbox driver */


  	/************************** Mailbox Init ****************************/

  	XMbox_Config *ConfigPtr;


  	ConfigPtr = XMbox_LookupConfig(MBOX_DEVICE_ID );
  	if (ConfigPtr == (XMbox_Config *)NULL) 
    {
      // error handling...
  			 print("-- Error configuring Mailbox Bsp 1 --\r\n");
  			return XST_FAILURE;
  		}

  	mailbox_status = XMbox_CfgInitialize(&Mbox, ConfigPtr, ConfigPtr->BaseAddress);
  	if (Status != XST_SUCCESS) 
    {
      //  error handling...
  		print("-- Error initializing Mailbox : Bsp 1--\r\n");
  		return XST_FAILURE;
  	}


    /************************** Semaphore Init ****************************/

    if (sem_init(&sem_colour_yellow, 0, COL_YELLOW) < 0) // init sem_colour_yellow with 2 resource
    {
      print("Error while initializing semaphore sem.\r\n");
    }

    // initialize the semaphore
    if (sem_init(&sem_colour_background, 0, COL_BACKGROUND) < 0) // init sem_colour_background with 8 resource
    {
      print("Error while initializing semaphore sem.\r\n");
    }

  

}

int createThreads()
{
  /************************** Threading variables ****************************/

  pthread_attr_t attr;

  pthread_t tid_controller, tid_ball, tid_bricks[MAX_BRICKS_THREAD];

  /************************** Scheduling variables ****************************/

  struct sched_param sched_par;

  /************************** Normal variables ****************************/

  int iterator ,thread_status = 0,

  int col_x[] = { ALL_COL_X };

  /************************** Controller Thread Init ****************************/

  pthread_attr_init(&attr);           // get attribute for thread.

  sched_par.sched_priority = PRIO_CONTROLLER; // set priority for mailbox thread
  pthread_attr_setschedparam(&attr, &sched_par);  // update priority attribute

  //create controller thread 
  thread_status += pthread_create(&tid_controller, NULL, (void*) thread_func_controller, NULL );

  /************************** Ball Thread Init ****************************/

  sched_par.sched_priority = PRIO_BALL; // set priority for mailbox thread
  pthread_attr_setschedparam(&attr, &sched_par);  // update priority attribute

  //create controller thread 
  thread_status += pthread_create(&tid_ball, NULL, (void*) thread_func_mailbox, NULL );


  /************************** Brick Threads Init ****************************/


  sched_par.sched_priority = PRIO_BRICKS; // set priority for mailbox thread
  pthread_attr_setschedparam(&attr, &sched_par);  // update priority attribute

  for (iterator = 0 ; iterator < MAX_BRICKS_THREAD ; iterator ++)
  {
      thread_status += pthread_create(&tid_bricks[i], NULL, (void*) thread_func_brick, col_x[i] );
  }


  if (thread_status != 0)
  {
    //  error handling...
      print("-- Error initializing thread : Bsp 1--\r\n");
      return XST_FAILURE;
  }


}

// 1. Controller is the brain ....
void* thread_func_controller()
{
  int colThreads = 10; // how to find this can signal? via queue? 
  int score = 999;
  // got pthread_kill(thread_id , 0) ?? if got use ESRCH to check if still alive..

	// ball_msg ball;

 //  	ball.dir = 10;
 //  	ball.speed = 20;
 //  	ball.x = 30;
 //  	ball.y = 50;

  	while(1)
  	{

      // get current tick (before processing) ...

      // 1. Mailbox block receive (bar location) ** Opposite side must send initial bar location
      //    -  Should i use barrier to synchronise and start all thread?

      // 2. Message Queue to get score ???

      // 3. Change Brick Colour

      // change brick colour by releasing semaphore.. based on score..

      changeBrickColour(score, colThreads);

      // 4. Get bricks?? via msg queue?
      // 5. Get new ball location via msg queue?


      // get current tick (after processing)
      // time to sleep = FPS ticks - processing time.....

      // 6. Sleep
      // 7. Send all updated values via MAILBOX


	}

  //      XMbox_WriteBlocking(&Mbox,&ball, sizeof(ball_msg));

}

void* thread_func_ball()
{
  int dir,speed,x,y;

  while(1)
  {

    // 1. calculate final ball location...
    // 2. send the final ball location to brick
    // barrier or some mechanism to signify complete bricks hit...

    // if > 1 bricks hit... goto 3.1 else 3.2
    
    // 3.1 : slow iteration of ball movement to send ...

    // 3.2 : send ball final location... to controller

  }
}


void* thread_func_brick(int col_x) 
{
  unsigned char bricksLeft = 0b11111111;    // initialize with 8 bricks per column. 
  unsigned int  thread_score = 0;           // score for this thread.

  unsigned int currentColour = COLOR_GREEN; // some default color.
  unsigned int futureColour = COLOR_GREEN; // some default color.

  while (1) 
  {

    // Ball location via mailbox / global / shared memory?


    // 1. Fast boundary calculation...
    //      - send ball hit via mailbox / global / shared memory?
    // some barrier here....

    //  Notify total bricks hit via mailbox / global / shared memory?
    // if hit more than 2 brick. goto 1.1 else 1.2

    // 1.1. Iterative boundary calculation
    //      - send ball hit via mailbox / global / shared memory?
    // some barrier here

    // 1.2. Update bricks/score for this thread/column
    // some barrier here


    // 2. Grab colour here !! GOLD !! or ??
    futureColour = updateBrickColour(currentColour);


    // 3. Send color, future bricks ...  to controller to send via mailbox

    // 4. update current with future
    currentColour = futureColour;


  }


}



// Simple Description : Snatch for 2 semaphore resource, fail then colour same..
unsigned int updateBrickColour(unsigned int currentColour) 
{

  sleep(rand() % MAX_RAND_SLEEP);

  if (sem_trywait(&sem_colour_yellow) == SEM_SUCCESS) {
    // resource snatched !
    return COLOR_YELLOW;
  } else {
    if (sem_trywait(&sem_colour_background) == SEM_SUCCESS) {
      // failed to snatched resource
      return COLOR_GREEN;
    } else {
      // nothing to snatch
      return currentColour;

    }

  }
}





