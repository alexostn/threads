#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//INITIALIZE MUTEX BY THE MEAN OF MACROS

typedef struct s_thread_data
{
	int thread_num;
}	t_thread_data;

void* roll_dice(void* arg)
{
	t_thread_data* data = (t_thread_data*) arg;
	unsigned int seed = data->thread_num + time(NULL); // Unique seed per thread
	int value = (rand_r(&seed) % 6) + 1; // Thread-safe random number generation
	int* result = malloc(sizeof(int)); // allocate memory for result
	*result = value;
	pthread_mutex_lock(&mutex); // Lock mutex before printf
	printf("Thread %d memory adress: %p\n", data->thread_num, result);
	pthread_mutex_unlock(&mutex); // Unlock mutex after printf
	return (void*) result;
}

int main(int ac, char* av[])
{
	pthread_t th[8];
	t_thread_data thread_data[8];
	int* res;
	int i;

	srand(time(NULL));

	for (i = 0; i < 8; i++) // Create threads
	{
		thread_data[i].thread_num = i; // Assign thread number
		if (pthread_create(&th[i], NULL, &roll_dice, &thread_data[i]) != 0)
		{
			perror("Failed to create thread");
			return (1);
		}
		pthread_mutex_lock(&mutex); // Lock mutex before printf
		printf("Thread %d has started\n", i);
		pthread_mutex_unlock(&mutex); // Unlock mutex after printf
	}

	for (i = 0; i < 8; i++) // Join threads
	{
		if (pthread_join(th[i], (void**) &res) != 0)
		{
			perror("Failed to join thread");
			return (2);
		}
		pthread_mutex_lock(&mutex); // Lock mutex before printf
		printf("Thread: %d has finished\n", i);
		printf("Result: %d\n", *res);
		printf("Main res: %p\n", res);
		pthread_mutex_unlock(&mutex); // Unlock mutex after printf
		free(res); // Free the allocated memory
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}
