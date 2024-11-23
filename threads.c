#include <pthread.h>
#include <stdio.h>
// #include <stdlib.h>
#include <unistd.h>

void* routine()
{
	printf("Test from threads\n");
	sleep(3);
	printf("Ending thread\n");
}

int	main(int ac, char *av[])
{
	pthread_t t1;
	pthread_t t2;
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (1);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}