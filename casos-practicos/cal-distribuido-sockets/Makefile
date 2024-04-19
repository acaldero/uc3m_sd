
CC=gcc
CFLAGS=-g -Wall
LDFLAGS=


all :: app-d lib-server

app-d: app-d.o  lib-client.o  lib.o
	$(CC) $(CFLAGS) $(LDFLAGS) app-d.o lib.o lib-client.o       -o $@  $(LDFLAGS)

lib-server: lib-client.o  lib-server.o  lib.o
	$(CC) $(CFLAGS)            lib.o lib-client.o lib-server.o  -o $@  $(LDFLAGS)

mount:
	mkdir -p /dev/mqueue
	mount -t mqueue none /dev/mqueue

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f app-d lib-server *.o

