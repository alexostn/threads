// #include <stdlib.h>
// #include <stdio.h>
// #include <pthread.h>
// #include <unistd.h>

// int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

// void*	routine(void* arg)
// {
// 	int	index = *(int*)arg;//cast to int and derefferences it
// 	printf("%d ", primes[index]);
// 	free(arg);//important free memory inside of routine
// }

// int	main(int ac, char* av[])
// {
// 	pthread_t	th[10];
// 	int	i;
// 	for (i = 0; i < 10; i++)
// 	{
// 		int*	a = malloc(sizeof(int));//dynamically allocated, cause only access to "i" will provoke mistake
// 		*a = i;
// 		if (pthread_create(&th[i], NULL, &routine, a) != 0)
// 			perror("Failed to create thread");
// 	}
// 	for (i = 0; i < 10; i++)
// 	{
// 		if (pthread_join(th[i], NULL) != 0)
// 			perror("Failed to join thread");
// 	}
// }

////PASS POSITION IN ARRAY////
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void* routine(void* arg)
{
    int prime = *(int*)arg;  // Дерассируем указатель на элемент массива
    printf("%d ", prime);
    return NULL;
}

int main(void)
{
    pthread_t th[10];
    for (int i = 0; i < 10; i++)
    {
        // Передаем указатель на соответствующий элемент массива primes
        if (pthread_create(&th[i], NULL, routine, &primes[i]) != 0)
            perror("Failed to create thread");
    }
    for (int i = 0; i < 10; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
            perror("Failed to join thread");
    }
}
