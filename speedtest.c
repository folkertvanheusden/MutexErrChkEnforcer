#define _GNU_SOURCE
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define N 3ll

uint64_t get_ns()
{
	struct timespec tp;

	if (clock_gettime(CLOCK_REALTIME, &tp) == -1) {
		perror("clock_gettime");
		return 0;
	}

        return tp.tv_sec * 1000ll * 1000ll * 1000ll + tp.tv_nsec;
}

int main(int argc, char *argv[])
{
	{
		uint64_t cnt1 = 0;
		pthread_mutex_t l1 = PTHREAD_MUTEX_INITIALIZER;
		uint64_t start1 = get_ns();

		do {
			pthread_mutex_lock(&l1);
			cnt1++;
			pthread_mutex_unlock(&l1);
		}
		while(get_ns() - start1 <= N * 1000000000ll);

		printf("normal: %f\n", cnt1 / (double)N);
	}

	{
		uint64_t cnt1 = 0;
		pthread_mutex_t l1 = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
		uint64_t start1 = get_ns();

		do {
			pthread_mutex_lock(&l1);
			cnt1++;
			pthread_mutex_unlock(&l1);
		}
		while(get_ns() - start1 <= N * 1000000000ll);

		printf("errorcheck: %f\n", cnt1 / (double)N);
	}

	{
		uint64_t cnt1 = 0;
		pthread_mutex_t l1 = PTHREAD_ADAPTIVE_MUTEX_INITIALIZER_NP;
		uint64_t start1 = get_ns();

		do {
			pthread_mutex_lock(&l1);
			cnt1++;
			pthread_mutex_unlock(&l1);
		}
		while(get_ns() - start1 <= N * 1000000000ll);

		printf("adaptive: %f\n", cnt1 / (double)N);
	}

	{
		uint64_t cnt1 = 0;
		pthread_mutex_t l1 = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
		uint64_t start1 = get_ns();

		do {
			pthread_mutex_lock(&l1);
			cnt1++;
			pthread_mutex_unlock(&l1);
		}
		while(get_ns() - start1 <= N * 1000000000ll);

		printf("recursive: %f\n", cnt1 / (double)N);
	}

	return 0;
}
