// (C) 2021 by folkert@vanheusden.com
// released under Apache license v2.0

#define _GNU_SOURCE
#include <dlfcn.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

typedef int (* org_pthread_mutex_lock)(pthread_mutex_t *mutex);
org_pthread_mutex_lock org_pthread_mutex_lock_h = NULL;

int pthread_mutex_lock(pthread_mutex_t *mutex)
{
	if (!org_pthread_mutex_lock_h)
		org_pthread_mutex_lock_h = (org_pthread_mutex_lock)dlsym(RTLD_NEXT, "pthread_mutex_lock");

	if (mutex->__data.__kind == PTHREAD_MUTEX_NORMAL)
		mutex->__data.__kind = PTHREAD_MUTEX_ERRORCHECK;

	int rc = (*org_pthread_mutex_lock_h)(mutex);

	if (rc != 0) {
		int e = errno;

		fprintf(stderr, "Mutex %p lock (by %p) failed with: %s\n", mutex, __builtin_return_address(0), strerror(rc));

		errno = e;
	}

	return rc;
}
