#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* routine(void* arg)
{
	printf("Thread is running with custom stack size\n");
	return NULL;
}

int main()
{
	pthread_t t1;
	pthread_attr_t attr;
	size_t stack_size = 16 * 1024; // Указываем размер стека (16 КБ)

	// Инициализируем атрибуты
	pthread_attr_init(&attr);

	// Устанавливаем размер стека
	pthread_attr_setstacksize(&attr, stack_size);

	// Создаём поток с заданным атрибутом
	if (pthread_create(&t1, &attr, &routine, NULL))
	{
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	// Очищаем атрибуты
	pthread_attr_destroy(&attr);

	// Ожидаем завершения потока
	pthread_join(t1, NULL);

	return 0;
}
