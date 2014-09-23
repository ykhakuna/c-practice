LIBS := -lpthread
OBJS := logfile.o
CC = gcc
thread_test: thread_test.o logfile.o
	$(CC) -o $@ $^ $(LIBS)
test: test.o $(OBJS)
	$(CC) -o $@ $^ $(LIBS)
clean:
	rm -f *.o thread_test test log0 log1 log2

