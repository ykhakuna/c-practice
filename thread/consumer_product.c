#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/ipc.h>

#define MYFIFO	"myfifo"
#define BUFFER_SIZE	3
#define UNIT_SIZE	5
#define RUN_TIME 30
#define DELAY_TIME_LEVEL	5.0

int fd;
time_t end_time;
sem_t mutex, fill, avail;
static int ava_count, fill_count, m_count;

void *producer(void *arg) {
	int real_write;
	int delay_time = 0;

	while (time(NULL) < end_time) {
		delay_time = (int) (rand() * DELAY_TIME_LEVEL / (RAND_MAX) / 2.0) + 1;
		sleep(delay_time);
		sem_wait(&avail);
		sem_wait(&mutex);
		printf("\nProducer: delay = %d\n", delay_time);

		if ((real_write = write(fd, "hello", UNIT_SIZE)) == -1) {
			if (errno == EAGAIN) {
				printf("The FIFO has not been read yet, Please try later\n");
			}
		} else {
			printf("Write %d to the FIFO\n", real_write);
		}
		sem_post(&fill);
		sem_post(&mutex);
		sem_getvalue(&fill, &fill_count);
		sem_getvalue(&mutex, &m_count);
		printf("fill semaphore is: %d ;mutex is:%d\n", fill_count,m_count);
	}
	pthread_exit(NULL);
}

void *customer(void *arg) {
	unsigned char read_buffer[UNIT_SIZE];
	int real_read;
	int delay_time;

	while (time(NULL) < end_time) {
		delay_time = (int) (rand() * DELAY_TIME_LEVEL / (RAND_MAX)) + 1;
		sleep(delay_time);

		sem_wait(&fill);
		sem_wait(&mutex);
		memset(read_buffer, 0, 15);
		printf("\nCustomer: delay = %d\n", delay_time);

		if ((real_read = read(fd, read_buffer, UNIT_SIZE)) == -1) {
			if (errno == EAGAIN) {
				printf("No data yet\n");
			}
		}
		printf("Read %s from FIFO\n", read_buffer);
		sem_post(&avail);

		sem_post(&mutex);
		sem_getvalue(&avail, &ava_count);
		sem_getvalue(&mutex, &m_count);
		printf("avail semaphore is: %d; mutex is:%d\n", ava_count,m_count);
	}
	pthread_exit(NULL);
}

int main() {
	pthread_t thrd_prd_id, thrd_cst_id;
	pthread_t mon_th_id;
	int ret;

	srand(time(NULL));
	end_time = time(NULL) + RUN_TIME;

	if ((mkfifo(MYFIFO, O_CREAT | O_EXCL) < 0) && (errno != EEXIST)) {
		printf("Cannot create fifo\n");
		return errno;
	}

	fd = open(MYFIFO, O_RDWR);
	if (fd == -1) {
		printf("Open fifo error\n");
		return fd;
	}

	ret = sem_init(&mutex, 0, 1);
	ret += sem_init(&avail, 0, BUFFER_SIZE);
	ret += sem_init(&fill, 0, 0);
	if (ret != 0) {
		printf("Any semaphore initialization failed\n");
		return ret;
	}
	printf("%d\n", sem_getvalue(&avail, &ava_count));
	printf("avail semaphore is: %d\n", ava_count);
	ret = pthread_create(&thrd_prd_id, NULL, producer, NULL);
	if (ret != 0) {
		printf("Create producer thread error\n");
		return ret;
	}
	ret = pthread_create(&thrd_cst_id, NULL, customer, NULL);
	if (ret != 0) {
		printf("Create customer thread error\n");
		return ret;
	}

	pthread_join(thrd_prd_id, NULL);
	pthread_join(thrd_cst_id, NULL);
	close(fd);
	unlink(MYFIFO);
	return 0;
}
