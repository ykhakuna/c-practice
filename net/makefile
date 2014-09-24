CC := gcc
CFLAG := -o

all: client server

client: client.o
	$(CC) $(CFLAG) $@ $^

server: server.o
	$(CC) $(CFLAG) $@ $^

clean:
	rm *.o client server
