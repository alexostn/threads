// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <sys/types.h>

// int	main(int ac, char *av[])
// {
// 	int	x = 1;
// 	int	pid = fork();//создаёт новый процесс, который является копией текущего процесса
// 	if (pid == -1) //Если fork() вернёт -1, это означает, что произошла ошибка при создании нового процесса (например, нехватка ресурсов)
// 		return (1);//ERROR
// 	if (pid == 0)
// 		x++;
// 	sleep(2);
// 	printf("Hello from processes and process id%d with value of%d\n", getpid(), x);//different processes
// 	if (pid != 0) //Функция возвращает:0 в дочернем процессе.
// 		wait(NULL);//FOR CHILD PROCESS TO FINISH
// 	return (0);
// }
/*in fork we duplicate variables for each process and can modify them separately*/
//////////////////////////////////////////////////////
/*all threads instead can access all variables, they have common set of variables*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int	x = 1;//both threads access the same x

void* routine()
{
	x++;
	sleep(2);
	printf("Hello form threads with process:%d with value of%d\n", getpid(), x);//means ID of the same process can contain multiple threads
}
void* routine2()
{
	x++;
	sleep(2);
	printf("Hello form threads with process:%d with value of%d\n", getpid(), x);//means ID of the same process can contain multiple threads
}
int	main(int ac, char *av[])
{
	pthread_t t1;
	pthread_t t2;
	if (pthread_create(&t1, NULL, &routine, NULL))
		return 1;
	if (pthread_create(&t2, NULL, &routine2, NULL))
	return 2;
	if (pthread_join(t1, NULL))
		return 3;
	if (pthread_join(t1, NULL))
		return 4;
	return 0;
}
/*return values are different to better understand in which place is an error, in case of error f.ex:\
./program
if [ $? -eq 1 ]; then
    echo "Ошибка при создании первого потока"
elif [ $? -eq 2 ]; then
    echo "Ошибка при создании второго потока"
elif [ $? -eq 3 ]; then
    echo "Ошибка при ожидании первого потока"
elif [ $? -eq 4 ]; then
    echo "Ошибка при ожидании второго потока"
fi

*/