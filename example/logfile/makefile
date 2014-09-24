LIBS := -lpthread
OBJS := logfile.o
CC = gcc

thread_mutex_cond: thread_mutex_cond.o logfile.o
	$(CC) -o $@ $^ $(LIBS)

thread_test: thread_test.o logfile.o
	$(CC) -o $@ $^ $(LIBS)
test: test.o $(OBJS)
	$(CC) -o $@ $^ $(LIBS)
clean:
	rm -f *.o thread_test test log0 log1 log2 thread_mutex_cond

