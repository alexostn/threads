#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void* roll_dice()
{
	int	value = (rand() % 6) + 1;
	int* result = malloc(sizeof(int));//needed to repoint
	*result = value;
	//printf("%d\n", value); we do not use anymore
	printf("Thread result:%d\n", value);
	printf("Thread result:%p\n", result);
	pthread_exit((void*) result);//instead of: return (void*) result;
}

int	main(int ac, char* av[])
{
	int* res;
	srand(time(NULL));
	pthread_t	th;
	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
		return (1);
	pthread_exit(0);//means that the THREAD would not execute any of the code below, but NOT TERMINATE THE PROCESS=result visible
	if (pthread_join(th, (void**) &res) != 0)
		return (2);
	printf("Result: %d\n", *res);
	printf("Main res:%p\n", res);
	free(res);//MEMORY WOULD NOT BE FREED
	return (0);
}
/*
pthread_exit(0); INSIDE MAIN DOES NOT KILL THE PROCESS AND LETS ALL THREADS RUNNING
pthread_exit(0);is good if you want to start some threads, and let them running, while MAIN STOPS EXISTANCE 
when they are running andd does not matter if you pthread_join them or not 
PROCESS is going to wait for all the other THREAD to finish

WITHOUT pthread_exit(0); we would wait till main thread finishes execution
WITH pthread_exit(0); we let PROCESS handle it
*/
