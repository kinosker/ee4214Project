
#include "xmk.h"
#include "xtft.h"
#include "stdlib.h"
#include "sys/init.h"
#include "xgpio.h"
#include "xparameters.h"
#include "semaphore.h"
#include <pthread.h>
#include <sys/timer.h> //for using sleep. need to set config_time to true
#include <sys/intr.h> //xilkernel api for interrupts
#include <stdio.h>
#include "TFT_Draw.h"
#include "myBarrier.h"
#include "myButton.h"
#define XST_SUCCESS                     0L
#define XST_FAILURE                     1L
// TO DO : read and understand the xilkernel system calls as well as the driver APIs used.

// 5 Priority levels for this processor.
#define PRIO_CONTROLLER 1
#define PRIO_BALL		2
#define PRIO_BAR		3
#define PRIO_COL 		4
#define PRIO_SCORE_ZONE 5


#define SEM_SUCCESS			0
#define UPDATE_COLOUR_SCORE	10
#define MAX_RAND_SLEEP		100 	// for snatching colour sema

/************************** Function Prototypes *****************************/

void* thread_func_controller();
void* thread_func_col(int col_x);

void changeBrickColour(int score,  int colThreads);
unsigned int updateBrickColour(unsigned int currentColour);


void main_prog(void *arg);

/************************** Variable Definitions ****************************/

/************************** Tft variables ****************************/

static XTft InstancePtr;

/************************** Scheduling variables ****************************/

struct sched_param sched_par;

/************************** Threading variables ****************************/

pthread_attr_t attr;

pthread_t tid_controller, tid_col_1, tid_col_2, tid_col_3, tid_col_4, tid_col_5,
		tid_col_6, tid_col_7, tid_col_8, tid_col_9, tid_col_10;


/************************** Thread Synchronisation variables ****************************/
pthread_mutex_t mutex_col;
struct barrier_t barrier_col;
sem_t sem_colour_yellow;
sem_t sem_colour_background;

/************************** Button variables********************************************/
//volatile char bar_Status;
XGpio gpPB; //PB device instance.



volatile int taskrunning;

int main() {
	print("-- Entering main() --\r\n");

	// Initialise VGA Display...
	tft_init(TFT_DEVICE_ID, &InstancePtr);

	//Initialize Xilkernel
	xilkernel_init();

	//Add main_prog as the static thread that will be invoked by Xilkernel
	xmk_add_static_thread(main_prog, 0);

	//Start Xilkernel
	xilkernel_start();

	/* Never reached */
	return 0;
}

void main_prog(void *arg) {
	int ret, Status;;

	// initialize the semaphore
	if (sem_init(&sem_colour_yellow, 0, COL_YELLOW)  < 0) // init sem_colour_yellow with 2 resource
	{
		print("Error while initializing semaphore sem.\r\n");
	}

	// initialize the semaphore
	if (sem_init(&sem_colour_background, 0, COL_BACKGROUND)  < 0) // init sem_colour_background with 8 resource
	{
		print("Error while initializing semaphore sem.\r\n");
	}

	// initialize barrier
	ret = myBarrier_init(&barrier_col, COL_BRICKS + 1); // barrier is for # of col threads + controller thread (1)
	if (ret != 0) {
		xil_printf("-- ERROR (%d) init barrier...\r\n", ret);
	}



	// initialize mutex
	ret = pthread_mutex_init(&mutex_col, NULL );
	if (ret != 0) {
		xil_printf("-- ERROR (%d) init uart_mutex...\r\n", ret);
	}

	init_myButton(&gpPB);


	print("startinitDraw");
	tft_intialDraw(&InstancePtr);
	print("end init");

	tft_updateSpeed(&InstancePtr, 54);
	tft_updateBricksLeft(&InstancePtr, 0);
	tft_updateScore(&InstancePtr, 5);

	pthread_attr_init(&attr);						// get attribute for thread.

	//pthread_barrier_init(&barrier, NULL, 11); // barrier of size 11, for 10 col threads + 1 update display

	/************************** Controller Threads Init ****************************/

	sched_par.sched_priority = PRIO_CONTROLLER; // set priority for controller thread
	pthread_attr_setschedparam(&attr, &sched_par); 	// update priority attribute

	//start controller thread 1
	ret = pthread_create(&tid_controller, NULL, (void*) thread_func_controller,
			NULL );
	if (ret != 0) {
		xil_printf("-- ERROR (%d) launching thread_func_1...\r\n", ret);
	} else {
		xil_printf("Controller Thread launched with ID %d \r\n",
				tid_controller);
	}

	/************************** Column Threads Init ****************************/

	sched_par.sched_priority = PRIO_COL; 	// set priority for columns thread
	pthread_attr_setschedparam(&attr, &sched_par); 	// update priority attribute

	//start col thread 1
	ret = pthread_create(&tid_col_1, NULL, (void*) thread_func_col, COL_1_X);
	if (ret != 0) {
		xil_printf("-- ERROR (%d) launching thread_func_col_1...\r\n", ret);
	} else {
		xil_printf("Col Thread 1 launched with ID %d \r\n", tid_col_1);
	}

	//start col thread 2
	ret = pthread_create(&tid_col_2, NULL, (void*) thread_func_col, COL_2_X);
	if (ret != 0) {
		xil_printf("-- ERROR (%d) launching thread_func_col_2...\r\n", ret);
	} else {
		xil_printf("Col Thread 2 launched with ID %d \r\n", tid_col_2);
	}

	//start thread 3
	ret = pthread_create(&tid_col_3, NULL, (void*) thread_func_col, COL_3_X);
	if (ret != 0) {
		xil_printf("-- ERROR (%d) launching thread_func_col_3...\r\n", ret);
	} else {
		xil_printf("Col Thread 3 launched with ID %d \r\n", tid_col_3);
	}

	//start thread 4
	ret = pthread_create(&tid_col_4, NULL, (void*) thread_func_col, COL_4_X);
	if (ret != 0) {
		xil_printf("-- ERROR (%d) launching thread_func_col_4...\r\n", ret);
	} else {
		xil_printf("Col Thread 4 launched with ID %d \r\n", tid_col_4);
	}

	//start thread 5
	ret = pthread_create(&tid_col_5, NULL, (void*) thread_func_col, COL_5_X);
	if (ret != 0) {
		xil_printf("-- ERROR (%d) launching thread_func_col_5...\r\n", ret);
	} else {
		xil_printf("Col Thread 5 launched with ID %d \r\n", tid_col_5);
	}

	ret = pthread_create(&tid_col_6, NULL, (void*) thread_func_col, COL_6_X);
	if (ret != 0) {
		xil_printf("-- ERROR (%d) launching thread_func_col_6...\r\n", ret);
	} else {
		xil_printf("Col Thread 6 launched with ID %d \r\n", tid_col_6);
	}

	ret = pthread_create(&tid_col_7, NULL, (void*) thread_func_col, COL_7_X);
	if (ret != 0) {
		xil_printf("-- ERROR (%d) launching thread_func_col_7...\r\n", ret);
	} else {
		xil_printf("Col Thread 7 launched with ID %d \r\n", tid_col_7);
	}

	ret = pthread_create(&tid_col_8, NULL, (void*) thread_func_col, COL_8_X);
	if (ret != 0) {
		xil_printf("-- ERROR (%d) launching thread_func_col_8...\r\n", ret);
	} else {
		xil_printf("Col Thread 8 launched with ID %d \r\n", tid_col_8);
	}

	ret = pthread_create(&tid_col_9, NULL, (void*) thread_func_col, COL_9_X);
	if (ret != 0) {
		xil_printf("-- ERROR (%d) launching thread_func_col_9...\r\n", ret);
	} else {
		xil_printf("Col Thread 9 launched with ID %d \r\n", tid_col_9);
	}

	ret = pthread_create(&tid_col_10, NULL, (void*) thread_func_col, COL_10_X);
	if (ret != 0) {
		xil_printf("-- ERROR (%d) launching thread_func_col_10...\r\n", ret);
	} else {
		xil_printf("Col Thread 10 launched with ID %d \r\n", tid_col_10);
	}
}

void* thread_func_controller() {

	// semaphore release
	int score = 0;
	int colThreads = COL_BRICKS; // Number of column threads = how many column of bricks.

	while(1)
	{
		// mailbox should be here....
		// update score should be here, print score somwhere else...

		// score updated => update colour.. then fire all col threads.


		myBarrier_wait(&barrier_col); // "fire" all col threads


		pthread_mutex_lock (&mutex_col);
		if(myButton_checkLeft())
		{
			tft_moveBarLeft(&InstancePtr);
		}

		if(myButton_checkRight())
		{
			tft_moveBarRight(&InstancePtr);
		}
		pthread_mutex_unlock (&mutex_col);

		sleep(400);

		changeBrickColour(++score, colThreads);


	}

}

void* thread_func_col(int col_x) {
	unsigned int currentColour = COLOR_GREEN; // some default color.
	unsigned int futureColour = COLOR_GREEN; // some default color.

	unsigned char currentBricks = 0; 		  // start with 0 bricks..
	unsigned char futureBricks = 0b11111111; // after updateColumn will have 8 col brick!!!
	unsigned char randBricks;

	unsigned int thread_ScoreAccumulated = 0;

	while (1) {
		// some msg q or ....... semaphore.... or .....
		// check if ball hit brick => update score, future brick
		// check if picked randomly => update colour
		// test print

		myBarrier_wait(&barrier_col); // wait for all col threads to reach here... and controller thread to reach wait.

		futureColour = updateBrickColour(currentColour);


		pthread_mutex_lock (&mutex_col);
		xil_printf ("\r\nThis is Col :  %d \r", col_x);
		tft_updateColumn(&InstancePtr, col_x, currentBricks, futureBricks,currentColour, futureColour);

		currentColour = futureColour;
		currentBricks = futureBricks;

		randBricks = rand() % 256;

		if(randBricks < currentBricks)
			futureBricks = randBricks;

		xil_printf ("\r\nend is Col :  %d \r", col_x);
		pthread_mutex_unlock (&mutex_col);




		//pthread_exit(0);
	}

}


// Simple Description : Release semaphore resource for brick colour change.
void changeBrickColour(int score, int colThreads)
{
	int i, semaRelease;

	print("Starting Here\r\n");
	xil_printf("score: %d", score);
	if (score % 10 == 0)
	{
		print("inside loop liao");
		//release 2 semaphore yellow colour resources!!!

		if(colThreads > COL_YELLOW)
		{
			// some col need to be green
			semaRelease = colThreads - COL_YELLOW;
			for(i = 0; i < semaRelease ; i++)
			{
				// release semaphore to change to background
				sem_post(&sem_colour_background);
			}
		}

		if(colThreads < COL_YELLOW)
		{
			// lesser thread than column to be yellow.. release lesser sema.
			for(i = 0; i < colThreads ; i++)
			{
				// release semaphore to change to background
				sem_post(&sem_colour_yellow);
			}
		}
		else
		{
			for(i = 0; i < COL_YELLOW ; i++)
			{
				// release semaphore to change to background
				sem_post(&sem_colour_yellow);
			}
		}
	}
}

// Simple Description : Snatch for 2 semaphore resource, fail then colour same..
unsigned int updateBrickColour(unsigned int currentColour)
{


	sleep (rand() % MAX_RAND_SLEEP);

	if(sem_trywait(&sem_colour_yellow) == SEM_SUCCESS)
	{
		// resource snatched !
		return COLOR_YELLOW;	
	}
	else
	{
		if(sem_trywait(&sem_colour_background) == SEM_SUCCESS)
		{
			// failed to snatched resource
			return COLOR_GREEN;
		}
		else
		{
			// nothing to snatch
			return currentColour;

		}

	}



}



//void do_something(int max, int ID) {
//  sem_wait(&sem);
//  int i;
//  count++;
//  pthread_mutex_lock (&mutex);
//
//    changeBarColor(ID, COLOR_RED);
//    xil_printf ("\r\nNew Column Turn Red !! Red Columns Count :  %d \r", count);
//
//  pthread_mutex_unlock (&mutex);
//  if (taskrunning != ID) {
//      taskrunning = ID;}
//  pthread_mutex_lock (&mutex);
//  xil_printf ("\r\n Column %d Turn Red !! \r\n", ID);
//  pthread_mutex_unlock (&mutex);
//  for(i=0; i< max; i++)
//  {
//	  sleep(3);
//  }
//
//
//  sleep(MIN_DELAY);
//
//  count--;
//
//    pthread_mutex_lock (&mutex);
//        changeBarColor(ID, COLOR_BLUE);
//        xil_printf ("\r\n Column %d back to normal !! Red Columns Count :  %d \r",ID,count);
//     pthread_mutex_unlock (&mutex);
//
//   sem_post(&sem);
//}

//void* thread_func_1 () {
//  while(1) {
//
//    do_something((rand() % MAX_RAND_DELAY), 1);
//  }
//}
//
//
//void* thread_func_2 () {
//  while(1) {
//	  do_something((rand() % MAX_RAND_DELAY), 2);
//  }
//}
//
//
//void* thread_func_3 () {
//  while(1) {
//	  do_something((rand() % MAX_RAND_DELAY), 3);
//  }
//}
//
//
//void* thread_func_4 () {
//  while(1) {
//	  do_something((rand() % MAX_RAND_DELAY), 4);
//  }
//}
//
//void* thread_func_5 () {
//  while(1) {
//	  do_something((rand() % MAX_RAND_DELAY), 5);
//  }
//}
//
//void* thread_func_6 () {
//  while(1) {
//	  do_something((rand() % MAX_RAND_DELAY), 6);
//  }
//}
//void* thread_func_7 () {
//  while(1) {
//	  do_something((rand() % MAX_RAND_DELAY), 7);
//  }
//}
//void* thread_func_8 () {
//  while(1) {
//	  do_something((rand() % MAX_RAND_DELAY), 8);
//  }
//}
//
//
///*****************************************************************************/
///**
//* Change Bar color based on thread id
//*
//* @param  threadID is the id for the thread
//* @param  color is the color to change the column brick
//*
//* @return
//*   - XST_SUCCESS if successful.
//*   - XST_FAILURE if unsuccessful.
//*
//*
//******************************************************************************/
//int changeBarColor(int threadID, u32 colour)
//{
//
//  switch (threadID)
//  {
//    case 1:
//            TftDrawLine(&TftInstance, T1_BAR_X, ALL_BAR_Y, T1_BAR_X, ALL_BAR_Y + ALL_BAR_HEIGHT, colour); // column 1
//            break;
//
//    case 2:
//            TftDrawLine(&TftInstance, T2_BAR_X, ALL_BAR_Y, T2_BAR_X, ALL_BAR_Y + ALL_BAR_HEIGHT, colour); // column 2
//            break;
//    case 3:
//            TftDrawLine(&TftInstance, T3_BAR_X, ALL_BAR_Y, T3_BAR_X, ALL_BAR_Y + ALL_BAR_HEIGHT, colour); // column 3
//            break;
//    case 4:
//            TftDrawLine(&TftInstance, T4_BAR_X, ALL_BAR_Y, T4_BAR_X, ALL_BAR_Y + ALL_BAR_HEIGHT, colour); // column 4
//            break;
//    case 5:
//            TftDrawLine(&TftInstance, T5_BAR_X, ALL_BAR_Y, T5_BAR_X, ALL_BAR_Y + ALL_BAR_HEIGHT, colour); // column 5
//            break;
//    case 6:
//            TftDrawLine(&TftInstance, T6_BAR_X, ALL_BAR_Y, T6_BAR_X, ALL_BAR_Y + ALL_BAR_HEIGHT, colour); // column 6
//            break;
//    case 7:
//            TftDrawLine(&TftInstance, T7_BAR_X, ALL_BAR_Y, T7_BAR_X, ALL_BAR_Y + ALL_BAR_HEIGHT, colour); // column 7
//            break;
//    case 8:
//            TftDrawLine(&TftInstance, T8_BAR_X, ALL_BAR_Y, T8_BAR_X, ALL_BAR_Y + ALL_BAR_HEIGHT, colour); // column 8
//            break;
//
//    default: ;
//  }
//
//
//}

