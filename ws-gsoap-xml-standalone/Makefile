
CFLAGS=-Wall -g  -I/opt/homebrew/Cellar/gsoap/2.8.127/include/ -I/opt/gsoap-linux-2.7/  -L/opt/homebrew/Cellar/gsoap/2.8.127/lib/

all:
	soapcpp2 -c calc.h
	gcc  $(CFLAGS) -c soapC.c        -o soapC.o
	gcc  $(CFLAGS) -c calcClient.c   -o calcClient.o
	gcc  $(CFLAGS) -c soapClient.c   -o soapClient.o
	gcc  $(CFLAGS) -c calcServer.c   -o calcServer.o
	gcc  $(CFLAGS) -c soapServer.c   -o soapServer.o
	gcc  -o client  calcClient.o  soapC.o  soapClient.o   -lgsoap
	gcc  -o server  calcServer.o  soapC.o  soapServer.o   -lgsoap

install:
	brew install gsoap

clean:  
	rm -fr ns.nsmap \
	ns.resta.req.xml \
	ns.resta.res.xml \
	ns.suma.req.xml \
	ns.suma.res.xml \
	ns.wsdl \
	ns.xsd \
	soapC.c \
	soapClient.c \
	soapH.h \
	soapStub.h \
	*.o
