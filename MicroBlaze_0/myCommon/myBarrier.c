#include "myBarrier.h"


int myBarrier_init(barrier_t *barrier, unsigned int maxSize)
{
	int ret;

	barrier->maxSize = maxSize;
 	barrier->currentSize = maxSize;	
	ret = pthread_mutex_init(&(barrier->mutex), NULL ); // note mutex is init to unlocked!
	ret += sem_init(&(barrier->sema), 0, 0);			// initial count of sema is 0

	return ret;
}

void myBarrier_print(barrier_t *barrier)
{
	xil_printf("barrier->currentSize : %d, maxSize : %d\n", barrier->currentSize, barrier->maxSize);
}

void myBarrier_wait(barrier_t *barrier)
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

void myBarrier_setSize(barrier_t *barrier, unsigned int maxSize)
{
	int diffSize;

	pthread_mutex_lock(&barrier->mutex);

	diffSize = barrier->maxSize -  barrier->currentSize;

	if(barrier->currentSize == barrier->maxSize)
	{
		barrier->maxSize = maxSize; // correct
		barrier->currentSize = barrier->maxSize;

	}
	else
	{
		barrier->maxSize = maxSize; // correct
		barrier->currentSize = barrier->maxSize - diffSize;
	}


	pthread_mutex_unlock(&barrier->mutex);

}


void myBarrier_decreaseSize(barrier_t *barrier)
{
	int i;
	pthread_mutex_lock(&barrier->mutex);

	barrier->maxSize = barrier->maxSize - 1; // correct

	if(barrier->currentSize > barrier->maxSize)
	{
//		print("always here? xcept 1\n");

		barrier->currentSize = barrier->maxSize;
	}
	else
	{
		barrier->currentSize = barrier->currentSize - 1;
	}

	// unlock others if current size is 0..



	if(barrier->currentSize == 0)
	{
		for(i = 0 ; i < barrier->maxSize ; i++)
		{
			sem_post(&(barrier->sema));
		}

		barrier->currentSize = barrier->maxSize; // reset back to maxSize of threads to wait.
	}	

	pthread_mutex_unlock(&barrier->mutex);
}
