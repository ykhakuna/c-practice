/*
 * thread_test.c
 *
 *  Created on: Sep 22, 2014
 *      Author: yk
 *  1. create two threads to write sth into logfile, see what happen
 *  2. create more threads, one thread is for logfile operation
 *  the other threads write sth into a buffer (IPCs here), then signal
 *  the logfile thread to write
 */

#include "logfile.h"

#include <pthread.h>

//#include <ipc.h>

#define FILE_NAME "log"

void *thread_func(void *ptr);
char buf[256]={0};

pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
	pthread_t t1, t2;
	int ret;

	ret = pthread_create(&t1, NULL, &thread_func, NULL);
	if (ret != 0) {
		printf("create thread1 failed\n");
		return ret;
	}

	ret = pthread_create(&t2, NULL, &thread_func, NULL);
	if (ret != 0) {
		printf("create thread2 failed\n");
		return ret;
	}

	pthread_join(t1, NULL);

	pthread_join(t2, NULL);

	exit(EXIT_SUCCESS);
}

void *thread_func(void *ptr) {
	int i;
	for (i = 0; i < 5; i++) {
		pthread_mutex_lock(&log_mutex);
		sprintf(buf, "thread %d write into logfile.\n", pthread_self());
		write_log_file(FILE_NAME, buf);
		pthread_mutex_unlock(&log_mutex);
		usleep(100000 + (int) (100000.0 * rand() / RAND_MAX + 1));
	}
}
