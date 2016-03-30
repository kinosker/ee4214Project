/*
 * project_core0.c
 *
 *  Created on: Mar 17, 2016
 *      Author: KaiHsiang
 */

#include "xmk.h"
#include <pthread.h>
#include "semaphore.h"
#include <xparameters.h>
#include "xmbox.h"
#include "xstatus.h"
#include <pthread.h>
#include <errno.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/timer.h>
#include <stdio.h>
#include "sys/init.h"
#include "myCommon.h"
#include "myBarrier.h"

#define MAX_RAND_SLEEP    30   // for snatching colour sema


// 5 Priority levels for this processor.
#define PRIO_CONTROLLER 1
//#define PRIO_BAR    2
#define PRIO_BALL       2
#define PRIO_BRICKS     3
#define PRIO_SCORE_ZONE 5


// mailbox declaration
#define MBOX_DEVICE_ID    XPAR_MBOX_0_DEVICE_ID

#define MSGQ_ID_BALL   1
#define MSGQ_ID_BRICK  2
#define MSGQ_ID_BAR    3



 #define FPS_MS  1/FPS * 1000




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



typedef struct
{

  int x,y;

} bar_msg;

typedef struct
{
  int columnNumber;
  int bricksLeft;
  uint colour;

}brick_msg;

typedef struct
{
  int size; // how many brick msg is in the struct
  brick_msg allMsg[MAX_BRICKS_THREAD];

}allBricks_msg;


typedef struct
{
  int score;                   // score to be updated
  ball_msg msg_ball;           // ball location to be update.
  allBricks_msg msg_Allbricks; // bricks to be updated

}allProcessor_msg;



/**************** Global Thread Synchronisation variables **********************/

sem_t sem_colour_yellow;
sem_t sem_colour_background;

barrier_t barrier_ballBrick;  // synchronise all bricks and ballthreads.
barrier_t barrier_bricks;  // synchronise all bricks threads.
barrier_t barrier_score;  // synchronise all bricks threads score calculation.
barrier_t barrier_colour;  // signal that the colours resources for the bricks is ready


pthread_mutex_t score_mutex;



/**************** Global variables **********************/

int  score = 0;                   // score that is accessible by all threads.
ball_msg global_ballBrick;       //  tempBall location to be used by brick threads.
int global_bricksHit = 0;         // bricks hit to be used by brick threads.

/************************** Function Prototype  ****************************/


int main_prog(void);
void* thread_func_controller();
void* thread_func_ball();
void* thread_func_brick(int col_x);
int init_mailBox(XMbox *MboxPtr);
int init_threads();
unsigned int myCommon_ticks_to_ms(unsigned int ticks);
unsigned int updateBrickColour(unsigned int currentColour);


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

    /************************** Mutex Init ****************************/

    if (pthread_mutex_init (&score_mutex, NULL) != 0)
    {
      print ("Error when initializing mutex");
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


    /************************** Barrier Init ****************************/

    if( myBarrier_init(&barrier_score, MAX_BRICKS_THREAD + 1) != 0) // barrier to signal that score is updated.
    {
      xil_printf("Error when initializing barrier...\r\n");
    }

    if( myBarrier_init(&barrier_colour, MAX_BRICKS_THREAD + 1) != 0) // barrier to signal colour resource is ready . bricks + controller
    {
        xil_printf("Error when initializing barrier...\r\n");
    }

    if( myBarrier_init(&barrier_ballBrick, MAX_BRICKS_THREAD + 1) != 0) // barrier to synchronise ball and brick thread. bricks + balls
    {
        xil_printf("Error when initializing barrier...\r\n");
    }


    if( myBarrier_init(&barrier_bricks, MAX_BRICKS_THREAD) != 0) // barrier to synchronise all bricks thread..
    {
        xil_printf("Error when initializing barrier...\r\n");
    }






    /************************** Threads Init ****************************/

    init_threads();



}

int init_mailBox(XMbox *MboxPtr)
{
    XMbox_Config *ConfigPtr;

    int mailbox_status = 0;

    /************************** Mailbox Init ****************************/



    ConfigPtr = XMbox_LookupConfig(MBOX_DEVICE_ID );
    if (ConfigPtr == (XMbox_Config *)NULL)
    {
      // error handling...
         print("-- Error configuring Mailbox Bsp 1 --\r\n");
        return XST_FAILURE;
      }

    mailbox_status = XMbox_CfgInitialize(MboxPtr, ConfigPtr, ConfigPtr->BaseAddress);
    if (mailbox_status != XST_SUCCESS)
    {
      //  error handling...
      print("-- Error initializing Mailbox : Bsp 1--\r\n");
      return XST_FAILURE;
    }
}

int init_threads()
{
  /************************** Threading variables ****************************/

  pthread_attr_t attr;

  pthread_t tid_controller, tid_ball, tid_bricks[MAX_BRICKS_THREAD];

  /************************** Scheduling variables ****************************/

  struct sched_param sched_par;

  /************************** Normal variables ****************************/

  int  thread_status = 0, iterator;

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
  thread_status += pthread_create(&tid_ball, NULL, (void*) thread_func_controller, NULL );


  /************************** Brick Threads Init ****************************/


  sched_par.sched_priority = PRIO_BRICKS; // set priority for mailbox thread
  pthread_attr_setschedparam(&attr, &sched_par);  // update priority attribute

  for (iterator = 0 ; iterator < MAX_BRICKS_THREAD ; iterator ++)
  {
      thread_status += pthread_create(&tid_bricks[iterator], NULL, (void*) thread_func_brick, (void*)col_x[iterator] );
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

  static XMbox Mbox; /* Instance of the Mailbox driver */
  int msgQ_brick_id, msgQ_ball_id, msgQ_bar_id;

  unsigned int startTime_ms, endTime_ms, leftOverTime_ms;

  int colThreadsLeft = 10; // how to find this can signal? via queue?

  // got pthread_kill(thread_id , 0) ?? if got use ESRCH to check if still alive..

  bar_msg bar_recv;
  ball_msg ball_recv;
  brick_msg brick_recv;
  allBricks_msg allBricks_recv;

  allProcessor_msg allProcessor_send;



    /************************** Mailbox Init ****************************/

    init_mailBox(&Mbox);

    /************************** Message Q Init ****************************/

    msgQ_ball_id = msgget (MSGQ_ID_BALL, IPC_CREAT);  // gain access to q or create if not yet valid.
    msgQ_brick_id = msgget (MSGQ_ID_BRICK, IPC_CREAT); // gain access to q or create if not yet valid.
    msgQ_bar_id = msgget (MSGQ_ID_BAR, IPC_CREAT);    // gain access to q or ...


    while(1)
    {


      // get current tick (before processing) ...
      startTime_ms = myCommon_ticks_to_ms(xget_clock_ticks());


      // 1. Mailbox block receive (bar location) ** Opposite side must send initial bar location
      XMbox_ReadBlocking(&Mbox, &bar_recv, sizeof(bar_msg));

      // send to ball thread, (Implicitly launch all threads.)
      if( msgsnd( msgQ_bar_id, &bar_recv, sizeof(bar_msg), 0) < 0 )
      {
            // Error handling.
            print ("Error in sending message from ball thread");
      }





      // 2. Wait for score to be updated using score_mutex
      myBarrier_wait(&barrier_score); // wait for score to be updated by bricks thread.


      // 3. Change Brick Colour, release barrier for them to update colour
      //changeBrickColour(score, colThreadsLeft);       // change brick colour by releasing semaphore.. based on score..
      myBarrier_wait(&barrier_colour); // signal all bricks threads, they are ready to be updated with new colour




      // 4. Get final ball location via msg queue?
      if( msgrcv( msgQ_ball_id, &ball_recv, sizeof(ball_msg), 0,0 ) != sizeof(ball_msg) )
      {
          // Error handling.
          print ("Error in receiving message from bricks thread");
      }

      // 5. Get final bricks location via msg queue? blocking!
      if (msgQueue_receiveBricks(msgQ_brick_id, colThreadsLeft, &allBricks_recv))
      {
          // Error handling.
          print ("Error in receiving message from bricks thread");
      }

      // 6. Get current tick (after processing)
      endTime_ms = myCommon_ticks_to_ms(xget_clock_ticks());
      leftOverTime_ms = FPS_MS - startTime_ms - endTime_ms;  // time to sleep = FPS ticks - processing time.....

      // 7. Sleep(time left)
      sleep(leftOverTime_ms);


      // 8. Send all updated values via MAILBOX
      allProcessor_send.score = score;
      allProcessor_send.msg_Allbricks = allBricks_recv;
      allProcessor_send.msg_ball = ball_recv;

      XMbox_WriteBlocking(&Mbox, &allProcessor_send, sizeof(allProcessor_msg));

  }

}

void* thread_func_ball()
{
  int dir,speed,x,y;
  int msgQ_ball_id, msgQ_bar_id;

  ball_msg ball_send, ball_temp;
  bar_msg bar_recv;



  msgQ_ball_id = msgget (MSGQ_ID_BALL, IPC_CREAT); // gain access to q or create if not yet valid.
  msgQ_bar_id = msgget (MSGQ_ID_BAR, IPC_CREAT);    // gain access to q or ...

  while(1)
  {

    // 0. Init no bricks hit...
    global_bricksHit = 0;

    // msgQ wait for bar position?
    if( msgrcv( msgQ_bar_id, &bar_recv, sizeof(bar_msg), 0,0 ) != sizeof(bar_msg) )
    {
          // Error handling.
          print ("Error in receiving message from bricks thread");
    }

    // 1. calculate final ball location...

    // ball location = final ball location calculated..

    // 1.1 check if hit bar???!?


    // 2. send the final ball location to brick
    global_ballBrick = ball_temp; // update the global ball for brick thread..
    myBarrier_wait(&barrier_ballBrick); // barrier to signify the completion of calculate ball location




    // if > 1 bricks hit... goto 3.1 else 3.2

    myBarrier_wait(&barrier_ballBrick); // wait for calculation of how many bricks got hit...


    // 3.1 : slow iteration of ball movement to send ...
    if (global_bricksHit > 1)
    {
       // slow iteration....
       // for (;;)
    }



    // 3.2 : send ball final location... to controller
    //ball_send = ball_temp; // final location!!!

    if( msgsnd( msgQ_ball_id, &ball_send, sizeof(ball_msg), 0) < 0 )
    {
          // Error handling.
          print ("Error in sending message from ball thread");
    }

  }
}


void* thread_func_brick(int col_x)
{
  brick_msg brick_send;

  unsigned char bricksLeft = 0b11111111;    // initialize with 8 bricks per column.
  unsigned int  thread_score = 0;           // score for this thread.

  unsigned int colour = COLOR_GREEN; // some default color.

  int msgQ_brick_id;

  msgQ_brick_id = msgget (MSGQ_ID_BRICK, IPC_CREAT); // gain access to q or create if not yet valid.


  while (bricksLeft)
  {

    // Ball location via mailbox / global / shared memory?
	  myBarrier_wait(&barrier_ballBrick); // wait for ball location to be updated...
    // use  global_ballBrick for later...


    // 0. Init
    thread_score = 0; // reset thread_score accumulated for this frame.

    // 1. Fast boundary calculation...
    //      - receive ball location hit via mailbox / global / shared memory?

    // fastBoundaryCalc (global_ballBrick, ..... )

    // Mutex Lock;    global_bricksHit += ??; MutexUnlock;


    // some barrier here to signify
    //  Notify total bricks hit via mailbox / global / shared memory?
    // if hit more than 2 brick. goto 1.1 else 1.2
    myBarrier_wait(&barrier_ballBrick); // signify that the bricks hit is completed.


    // 1.1. Iterative boundary calculation
    //      - send ball hit via mailbox / global / shared memory?


    // some barrier here ? need ma? i think dont needd... blockin at controller...
    //myBarrier_wait(&barrier_bricks); // wait for all bricks thread to update



    // 1.2. Update bricks/score for this thread/column
    pthread_mutex_lock(&score_mutex);
    score += thread_score;
    pthread_mutex_unlock(&score_mutex);

    // Barrier to wait for score and colour to be updated here
    myBarrier_wait(&barrier_score); // wait for all bricks thread to update score.
    myBarrier_wait(&barrier_colour); // wait for colour resources to be available.


    // 2. Grab colour here !! GOLD !! or ??
    colour = updateBrickColour(colour);


    // 3. Send color, future bricks to controller, which in turn send it to other core via mailbox

    brick_send.colour = colour;
    brick_send.bricksLeft = bricksLeft;
    brick_send.columnNumber = 0; // temp...

    if( msgsnd( msgQ_brick_id, &brick_send, sizeof(brick_msg), 0) < 0 )
    {
          // Error handling.
          print ("Error in sending message from bricks thread");
    }


} // end of while(1) for thread


  // implicit thread exit when bricksleft = 0....

  // 1. decrease size of the barrier.
  myBarrier_decreaseSize(&barrier_score);
  myBarrier_decreaseSize(&barrier_colour);
  myBarrier_decreaseSize(&barrier_ballBrick);

  // 2. A way to notify controller thread if pthread function to check failed.

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


int msgQueue_receiveBricks(int msgQ_brick_id, int colThreads, allBricks_msg *allBricks_recv)
{
  int iterator;

  for(iterator = 0 ; iterator < colThreads ; iterator++)
  {
    if( msgrcv( msgQ_brick_id, &(allBricks_recv->allMsg[iterator]), sizeof(brick_msg), 0,0 ) != sizeof(brick_msg))
    {
      return XST_FAILURE;
    }
  }

  allBricks_recv->size = colThreads;

  return XST_SUCCESS;
}


unsigned int myCommon_ticks_to_ms(unsigned int ticks)
{
    return (ticks * (SYSTMR_INTERVAL / SYSTMR_CLK_FREQ_KHZ));
}





