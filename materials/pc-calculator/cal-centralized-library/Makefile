
CC=gcc
CFLAGS=-g -Wall

all :: app-c

app-c: app-c.o lib.o
	$(CC) $(CFLAGS) app-c.o lib.o  -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f app-c *.o

