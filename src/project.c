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
#define XST_SUCCESS                     0L
#define XST_FAILURE                     1L
// TO DO : read and understand the xilkernel system calls as well as the driver APIs used.

/************************** Function Prototypes *****************************/


//int changeBarColor(int threadID, u32 colour);
//void* thread_func_1 () ;
//void* thread_func_2 () ;
//void* thread_func_3 () ;
//void* thread_func_4 () ;
//void* thread_func_5 () ;
//void* thread_func_6 () ;
//void* thread_func_7 () ;
//void* thread_func_8 () ;
void do_something(int max, int ID);
/************************** Variable Definitions ****************************/

XGpio gpPB; //PB device instance.
static XTft InstancePtr;

// declare the semaphore
sem_t sem;
pthread_t tid1, tid2, tid3, tid4, tid5, tid6, tid7, tid8;
pthread_mutex_t mutex;
volatile int taskrunning;

void main_prog(void *arg) {
	int ret;

	// initialize the semaphore
	if (sem_init(&sem, 1, 5) < 0) {
		print("Error while initializing semaphore sem.\r\n");
	}

	// initialize mutex
	ret = pthread_mutex_init(&mutex, NULL );
	if (ret != 0) {
		xil_printf("-- ERROR (%d) init uart_mutex...\r\n", ret);
	}

	print("startinitDraw");
	tft_intialDraw(&InstancePtr);
	print("end init");

	tft_updateSpeed(&InstancePtr, 99);
	tft_updateBricksLeft(&InstancePtr, 89);
	tft_updateScore(&InstancePtr, 994);

}


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



