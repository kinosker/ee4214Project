#ifndef MY_BARRIER_H
#define MY_BARRIER_H


#include <pthread.h>
#include "semaphore.h"


/*****************************************************************************
 *																			 *
 *																			 *
 *					---- Start of Constant definition ----					 *
 *																			 *
 *																			 *
 ******************************************************************************/
 #define BARRIER_SUCCESS 0
 #define BARRIER_FAILURE -1


/*****************************************************************************
 *																			 *
 *																			 *
 *					---- Start of Struct definition ----					 *
 *																			 *
 *																			 *
 ******************************************************************************/

typedef struct barrier_t
{
  	int currentCount, maxCount;
	pthread_mutex_t mutex;
	sem_t sema;

};




/*****************************************************************************
 **																			 *
 *																			 *
 *					---- Start of Functions Prototype ----					 *
 *																			 *
 *																			 *
 *****************************************************************************/

/*****************************************************************************
 **
 * Initialise the barrier
 *
 * @param  count is the numbers of threads inside the barrier
 * @param  barrier is the barrier to initialise.
 *
 *
 * @return
 *   - BARRIER_SUCCESS if successful.
 *   - BARRIER_FAILURE if unsuccessful.
 *
 *****************************************************************************/
int myBarrier_init(struct barrier_t *barrier, unsigned int count);


/*****************************************************************************
 **
 * Wait for all threads to reach the barrier
 *
 * @param  barrier is the barrier to be used.
 *
 *
 * @return
 *   - NONE
 *
 *****************************************************************************/
void myBarrier_wait(struct barrier_t *barrier);

#endif
