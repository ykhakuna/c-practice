/*
 * thread_test.c
 *
 *  Created on: Sep 22, 2014
 *      Author: yk
 *  1. create two threads to write sth into logfile, see what happen
 *  2. create more threads, one thread is for logfile operation
 *  the other threads write sth into a buffer (IPCs here), then signal
 *  the logfile thread to write
 *
 *  this code just tests the pthread condition
 *  the condition mode is
 *  thread 1
 *  pthread_mutex_lock(&mutex);
 *  pthread_cond_wait(&cond_variable, &mutex);
 *  do sth...
 *  pthread_mutex_unlock(&mutex);
 *
 *  thread 2
 *  pthread_mutex_lock(&mutex);
 *  condition fill up...
 *  pthread_cond_signal(&cond_variable);
 *  pthread_mutex_unlock(&mutex);
 */

#include "logfile.h"

#include <pthread.h>

//#include <ipc.h>

#define FILE_NAME "log"
#define RUN_TIMES 5

void *thread_func1(void *ptr);
void *thread_func2(void *ptr);
void *log_thread(void *ptr);

char buf[256]={0};

pthread_mutex_t buf_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buf_empty = PTHREAD_COND_INITIALIZER;

int main() {
	pthread_t t1, t2, t_log;
	int ret;

	ret = pthread_create(&t1, NULL, &thread_func1, NULL);
	if (ret != 0) {
		printf("create thread1 failed\n");
		return ret;
	}

	ret = pthread_create(&t2, NULL, &thread_func2, NULL);
	if (ret != 0) {
		printf("create thread2 failed\n");
		return ret;
	}

	ret = pthread_create(&t_log, NULL, &log_thread, NULL);
	if (ret != 0) {
		printf("create log thread failed\n");
		return ret;
	}

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t_log, NULL);
	
	exit(EXIT_SUCCESS);
}

void *log_thread(void *ptr){
	while(1){
		pthread_mutex_lock(&buf_mutex);
		if(strcmp(buf,"\0")){
			write_log_file(FILE_NAME, buf);
			memset(&buf,0,sizeof(buf));
		}
		pthread_cond_signal(&buf_empty);
		pthread_mutex_unlock(&buf_mutex);
	}
}
void *thread_func1(void *ptr) {
	int i;
	for (i = 0; i < RUN_TIMES; i++) {
//		pthread_mutex_lock(&log_mutex);
		pthread_mutex_lock(&buf_mutex);
		pthread_cond_wait(&buf_empty, &buf_mutex);
		sprintf(buf, "thread1 write into logfile.\n");
		printf("thread1 write into logfile.\n");
//		write_log_file(FILE_NAME, buf);
		pthread_mutex_unlock(&buf_mutex);
//		pthread_mutex_unlock(&log_mutex);
		usleep(1 + (int) (10.0 * rand() / RAND_MAX + 1));
	}
}

void *thread_func2(void *ptr) {
        int i;
        for (i = 0; i < RUN_TIMES; i++) {
//                pthread_mutex_lock(&log_mutex);
                pthread_mutex_lock(&buf_mutex);                           
                pthread_cond_wait(&buf_empty, &buf_mutex);
		sprintf(buf, "thread %ld write into logfile.\n", pthread_self());
		printf("thread2 write into logfile.\n");
                pthread_mutex_unlock(&buf_mutex);
//                pthread_mutex_unlock(&log_mutex);
                
                usleep(1 + (int) (10.0 * rand() / RAND_MAX + 1));
        }
}

