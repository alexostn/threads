#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void*	routine(void* arg)
{
	int	index = *(int*)arg;
	int	sum = 0;
	for (int j = 0; j < 5; j++)
	{
		sum += primes[index + j];
	}
	printf("Local sum:%d\n", sum);//to check, what is happening inside
	*(int*)arg = sum;
	return(arg);
}
/*to transfer it in main either 
1)malloc new or 2)return existing allocated (arg)
Good way handle memory send to thread and free returned value
*/

int	main(int argc, char* argv[])
{
	pthread_t	th[2];
	int	i;
	for (i = 0; i < 2; i++)
	{
		int* a = malloc(sizeof(int));//needed to pass some values through
		*a = i * 5;//for half of array
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
			perror("Failed to create thread");
	}
	int	globalSum = 0;
	for (i = 0; i < 2; i++)
	{
		int*	r;
		if (pthread_join(th[i], (void**)&r) != 0)//you need to cast (void**)&r
			perror("Failed to join thread");
			globalSum += *r; //*r dereffferrence of r
		free(r);
	}
	printf("Global sum: %d\n", globalSum);
	return (0);
}
