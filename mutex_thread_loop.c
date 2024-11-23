#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int	mails = 0;
pthread_mutex_t	mutex;									//1.DECLARE MUTEX
// int	lock = 0;			//to imagine how mutex works	

void*	routine()
{
	for (int i = 0; i < 100000000; i++)
	{
		pthread_mutex_lock(&mutex);						//2.LOCK MUTEX(inside function)
		// if (lock == 1){	//to imagine how mutex works
		// lock = 1;		//to imagine how mutex works
		mails++;
		pthread_mutex_unlock(&mutex);					//3.UNLOCK MUTEX(inside function)
		// lock = 0;} 		//to imagine how mutex works
		// read mails
		// increment
		// write mails
	}
}

int	main(int ac, char* av[])
{
	pthread_t th[4];//array of threads
	int	i;

	pthread_mutex_init(&mutex, NULL);					//4.INITIALIZE MUTEX(in main)
	for (i = 0; i < 4; i++)						//Ist LOOP
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("Failed tocreate thread");
			return (1);
		}
		printf("Thread %d has started\n", i);
	}
	for (i = 0; i < 4; i++)						//IInd LOOP
	{
		if (pthread_join(th[i], NULL) != 0)
			return (2);
		printf("Thread %d has finished\n", i);
	}
	pthread_mutex_destroy(&mutex);						//5.DESTROY MUTEX(in main)
	printf("Number of mails: %d\n", mails);
	return (0);
}
/*
Desirable result:
Thread 0 has started
Thread 1 has started
Thread 2 has started
Thread 3 has started
Thread 0 has finished
Thread 1 has finished
Thread 2 has finished
Thread 3 has finished
*/