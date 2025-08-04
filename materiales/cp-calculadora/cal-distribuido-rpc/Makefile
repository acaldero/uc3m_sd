
 CC = gcc
#CFLAGS   = -g -Wall
 CFLAGS  += -g -Wall
#LDFLAGS  = -lpthread -ldl
 LDFLAGS += -lnsl -lpthread -ldl


all :: app-d lib-server

app-d: app-d.o lib-client.o message_clnt.o message_xdr.o 
	$(CC) $(CFLAGS) lib-client.o app-d.o message_clnt.o message_xdr.o  -o $@ $(LDFLAGS)

lib-server: lib.o lib-server.o message_svc.o message_xdr.o
	$(CC) $(CFLAGS) lib-server.o  lib.o  message_svc.o  message_xdr.o  -o $@ $(LDFLAGS)

rpcgen:
	rpcgen -N -M message.x

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f app-d lib-server *.o

