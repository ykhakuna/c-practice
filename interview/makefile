LIBS := -lpthread
#OBJS := logfile.o
CC =gcc
DEBUG ?= debug/

struct-addr: struct-addr.o
	$(CC) -o $(DEBUG)$@ $^

#thread_test: thread_test.o logfile.o

clean:
	rm *.o $(DEBUG)*
#	rm -f *.o thread_test test log0 log1 log2 thread_mutex_cond

