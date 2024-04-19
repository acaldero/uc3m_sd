
CC=gcc
CFLAGS=-I/opt/homebrew/Cellar/gsoap/2.8.127/include/ \
       -L/opt/homebrew/Cellar/gsoap/2.8.127/lib/


all: app-d lib-server

app-d: app-d.c soapC.c
	$(CC) -o app-d       $(CFLAGS) app-d.c lib-client.c  soapC.c soapClient.c -lgsoap

lib-server: lib-server.c soapC.c
	$(CC) -o lib-server  $(CFLAGS) lib-server.c lib.c    soapC.c soapServer.c -lgsoap

soapC.c:
	soapcpp2 -cL calc.h

%.o: %.c
	$(CC) $(CFLAGS) -c $<


clean:  
	rm -fr rm lib-server app-d
	rm -fr calc.nsmap \
	       calc.wsdl \
	       calc.add.req.xml \
	       calc.add.res.xml \
	       calc.divide.req.xml \
	       calc.divide.res.xml \
	       calc.neg.req.xml \
	       calc.neg.res.xml \
	       ns.xsd \
	       soapC.c \
	       soapServer.c \
	       soapClient.c \
	       soapH.h \
	       soapStub.h

