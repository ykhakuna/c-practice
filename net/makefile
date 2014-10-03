CC := gcc
CFLAG := -o
DEBUG := -g

all: client server

client: client.o
	$(CC) $(CFLAG) $@ $^ $(DEBUG)

server: server.o
	$(CC) $(CFLAG) $@ $^ $(DEBUG)

clean:
	rm *.o client server
