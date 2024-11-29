/*
car1: lock->cond_wait->unlock
car2: lock->cond_wait->unlock
fueler1:lock
car3: lock(waiting on lock)
car4: lock(waiting on lock)
*/

// #include <stdlib.h>
// #include <stdio.h>
// #include <pthread.h>
// #include <unistd.h>
// #include <errno.h>

// pthread_mutex_t mutexFuel;
// pthread_cond_t condFuel;
// int	fuel = 0;//as long as it is GLOBAL VAR, MUTEX is needed

// void*	fuel_filling(void* arg)
// {
// 	for(int i = 0; i < 5; i++)
// 	{
// 		pthread_mutex_lock(&mutexFuel);
// 		fuel += 30;
// 		printf("Filled fuel...%d\n", fuel);
// 		pthread_mutex_unlock(&mutexFuel);
// 		pthread_mutex_lock(&mutexFuel);//добавил
// 		pthread_cond_broadcast(&condFuel);
// 		pthread_mutex_unlock(&mutexFuel);//добавил
// 		sleep(1);
// 	}
// }

// void*	car(void* arg)
// {
// 	pthread_mutex_lock(&mutexFuel);
// 	while (fuel < 40)
// 	{
// 		printf("No fuel. Waiting. . .\n");
// 		pthread_cond_wait(&condFuel, &mutexFuel);
// 		// equivalent to:
// 		// pthread_mutex_unlock(&mutexFuel);
// 		// wait for signal on condFuel
// 		// pthread_mutex_lock(&mutexFuel);
// 	}
// 	fuel -= 40;
// 	printf("Got fuel now left: %d\n", fuel);
// 	pthread_mutex_unlock(&mutexFuel);
// }

// int	main(int ac, char* av[])
// {
// 	pthread_t	th[6];
// 	pthread_mutex_init(&mutexFuel, NULL);
// 	pthread_cond_init(&condFuel, NULL);
// 	for (int i = 0; i < 6; i++)
// 	{
// 		if (i == 4 || i == 5)
// 		{
// 			if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0)
// 				perror("Failed to create a thread");
// 		}
// 		else
// 		{
// 			if (pthread_create(&th[i], NULL, &car, NULL) != 0)
// 				perror("Failed to create a thread");
// 		}
// 	}
// 	for (int i; i < 6; i++)
// 	{
// 		if (pthread_join(th[i], NULL) != 0)
// 			perror("Failed to join thread");
// 	}
// 	pthread_mutex_destroy(&mutexFuel);
// 	pthread_cond_destroy(&condFuel);
// 	return(0);

// }

///////////////////////////////////////////////////////////////original:
// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <errno.h>

// pthread_mutex_t mutexFuel;
// pthread_cond_t condFuel;
// int fuel = 0;

// void* fuel_filling(void* arg) {
//     for (int i = 0; i < 5; i++) {
//         pthread_mutex_lock(&mutexFuel);
//         fuel += 30;
//         printf("Filled fuel... %d\n", fuel);
//         pthread_mutex_unlock(&mutexFuel);
// 		pthread_cond_broadcast(&condFuel);
// 		// pthread_mutex_lock(&mutexFuel);
// 		// pthread_cond_signal(&condFuel);  // Используем signal вместо broadcast
// 		// pthread_mutex_unlock(&mutexFuel);
//         sleep(1);
//     }
// }

// void* car(void* arg) {
//     pthread_mutex_lock(&mutexFuel);
//     while (fuel < 40) {
//         printf("No fuel. Waiting...\n");
//         pthread_cond_wait(&condFuel, &mutexFuel);
//         // Equivalent to:
//         // pthread_mutex_unlock(&mutexFuel);
//         // wait for signal on condFuel
//         // pthread_mutex_lock(&mutexFuel);
//     }
//     fuel -= 40;
//     printf("Got fuel. Now left: %d\n", fuel);
//     pthread_mutex_unlock(&mutexFuel);
// }

// int main(int argc, char* argv[]) {
//     pthread_t th[6];
//     pthread_mutex_init(&mutexFuel, NULL);
//     pthread_cond_init(&condFuel, NULL);
//     for (int i = 0; i < 6; i++) {
//         if (i == 4 || i == 5) {
//             if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0) {
//                 perror("Failed to create thread");
//             }
//         } else {
//             if (pthread_create(&th[i], NULL, &car, NULL) != 0) {
//                 perror("Failed to create thread");
//             }
//         }
//     }

//     for (int i = 0; i < 6; i++) {
//         if (pthread_join(th[i], NULL) != 0) {
//             perror("Failed to join thread");
//         }
//     }
//     pthread_mutex_destroy(&mutexFuel);
//     pthread_cond_destroy(&condFuel);
//     return 0;
// }
/////////////////////////////////////////////END OF ORIGINAL//////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
int fuel = 0; // As long as it is a global var, mutex is needed

void* fuel_filling(void* arg)
{
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mutexFuel);
        fuel += 30;
        printf("Filled fuel...%d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
		pthread_mutex_lock(&mutexFuel);
        pthread_cond_broadcast(&condFuel);
		pthread_mutex_unlock(&mutexFuel);//добавил
        sleep(1);
    }
}

void* car(void* arg)
{
    int car_id = *((int*)arg);  // Get the unique car ID
    free(arg); // Free the allocated memory for car_id

    pthread_mutex_lock(&mutexFuel);
    while (fuel < 40)
    {
        printf("Car %d: No fuel. Waiting...\n", car_id); // Print the car waiting
        pthread_cond_wait(&condFuel, &mutexFuel);
    }
    fuel -= 40;
    printf("Car %d: Got fuel now left: %d\n", car_id, fuel); // Print the car refueled
    pthread_mutex_unlock(&mutexFuel);
}

int main(int ac, char* av[])
{
    pthread_t th[6];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_cond_init(&condFuel, NULL);

    for (int i = 0; i < 6; i++)
    {
        if (i == 4 || i == 5)
        {
            // Fueler threads
            if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0)
                perror("Failed to create a thread");
        }
        else
        {
            // Car threads
            int* car_id = malloc(sizeof(int)); // Allocate memory for car ID
            if (car_id == NULL)
            {
                perror("Failed to allocate memory for car ID");
                exit(1);
            }
            *car_id = i + 1;  // Assign a unique car ID (1, 2, 3, etc.)

            if (pthread_create(&th[i], NULL, &car, car_id) != 0) // Pass the car ID to the thread
                perror("Failed to create a thread");
        }
    }

    for (int i = 0; i < 6; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
            perror("Failed to join thread");
    }

    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return 0;
}
