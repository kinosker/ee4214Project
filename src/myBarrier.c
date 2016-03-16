#include "myBarrier.h"


int myBarrier_init(unsigned int count, struct barrier_t *barrier)
{
	int ret;

	barrier->maxCount = count;
 	barrier->currentCount = count;	
	ret = pthread_mutex_init(&(barrier->mutex), NULL ); // note mutex is init to unlocked!
	ret += sem_init(&(barrier->sema), 0, 0);			// initial count of sema is 0

	return ret;
}


void myBarrier_wait(struct barrier_t *barrier)
{

    pthread_mutex_lock(&barrier->mutex);   

	barrier->currentCount = barrier->currentCount - 1;

	if(barrier->currentCount == 0)
	{
		for(int i = 0 ; i < barrier->maxCount ; i++)
		{
			sem_post(&(barrier->sema));
		}

		barrier->currentCount = barrier->maxCount; // reset back to maxCount of threads to wait.
	}	

	pthread_mutex_unlock(&barrier->mutex);
	sem_wait(&(barrier->sema));
  
}
