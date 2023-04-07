
CFLAGS=-I/opt/homebrew/Cellar/gsoap/2.8.127/include/ \
       -L/opt/homebrew/Cellar/gsoap/2.8.127/lib/


all:
	wsdl2h -c -o calc.h http://www.genivia.com/calc.wsdl
	soapcpp2 -CL calc.h
	gcc -o app-d  $(CFLAGS) app-d.c soapC.c soapClient.c -lgsoap

install:
	brew install gsoap


clean:  
	rm -fr calc.nsmap \
	calc.add.req.xml \
	calc.add.res.xml \
	calc.div.req.xml \
	calc.div.res.xml \
	calc.mul.req.xml \
	calc.mul.res.xml \
	calc.pow.req.xml \
	calc.pow.res.xml \
	calc.sub.req.xml \
	calc.sub.res.xml \
	soapC.c \
	soapClient.c \
	soapH.h \
	soapStub.h

