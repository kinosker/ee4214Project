#include "myBarrier.h"
#include <pthread.h>

int myBarrier_init(struct barrier_t *barrier, unsigned int maxSize)
{
	int ret;

	barrier->maxSize = maxSize;
 	barrier->currentSize = maxSize;	
	ret = pthread_mutex_init(&(barrier->mutex), NULL ); // note mutex is init to unlocked!
	ret += sem_init(&(barrier->sema), 0, 0);			// initial count of sema is 0

	return ret;
}


void myBarrier_wait(struct barrier_t *barrier)
{

	int i;
    pthread_mutex_lock(&barrier->mutex);   

	barrier->currentSize = barrier->currentSize - 1;

	if(barrier->currentSize == 0)
	{
		for(i = 0 ; i < barrier->maxSize ; i++)
		{
			sem_post(&(barrier->sema));
		}

		barrier->currentSize = barrier->maxSize; // reset back to maxSize of threads to wait.
	}	

	pthread_mutex_unlock(&barrier->mutex);
	sem_wait(&(barrier->sema));
}

void myBarrier_decreaseSize(struct barrier_t *barrier)
{
	barrier->currentSize = barrier->currentSize - 1;
	barrier->maxSize = barrier->maxSize - 1;
}