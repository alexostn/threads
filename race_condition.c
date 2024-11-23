#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int	mails = 0;
pthread_mutex_t	mutex;
// int	lock = 0;			//to imagine how mutex works	

void*	routine()
{
	for (int i = 0; i < 100000000; i++)
	{
		pthread_mutex_lock(&mutex);
		// if (lock == 1){	//to imagine how mutex works
		// lock = 1;		//to imagine how mutex works
		mails++;
		pthread_mutex_unlock(&mutex);
		// lock = 0;} 		//to imagine how mutex works
		// read mails
		// increment
		// write mails
	}
}

int	main(int ac, char* av[])
{
	pthread_t p1;
	pthread_t p2;
	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&p1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&p2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(p1, NULL) != 0)
		return (3);
	if (pthread_join(p2, NULL) != 0)
		return (4);
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return (0);
}