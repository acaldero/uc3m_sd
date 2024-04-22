CC=gcc
CFLAGS=-g \
       -I/opt/homebrew/Cellar/gsoap/2.8.127/include/ \
       -L/opt/homebrew/Cellar/gsoap/2.8.127/lib/


all:
	wsdl2h -c -o calc.h http://www.genivia.com/calc.wsdl
	soapcpp2 -C -c calc.h
	$(CC) $(CFLAGS) -c soapC.c          -o soapC.o
	$(CC) $(CFLAGS) -c soapClientLib.c  -o soapClientLib.o
	$(CC) $(CFLAGS) -c app-d.c          -o app-d.o
	$(CC) -o app-d  $(CFLAGS)  app-d.o soapClientLib.o soapC.o  -lgsoap

install:
	brew install gsoap


clean:  
	rm -fr CalculatorSoap.nsmap \
	CalculatorSoap.Add.req.xml \
	CalculatorSoap.Add.res.xml \
	CalculatorSoap.Divide.req.xml \
	CalculatorSoap.Divide.res.xml \
	CalculatorSoap.Multiply.req.xml \
	CalculatorSoap.Multiply.res.xml \
	CalculatorSoap.Subtract.req.xml \
	CalculatorSoap.Subtract.res.xml \
	*.o
