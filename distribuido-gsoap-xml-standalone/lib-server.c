
// https://people.maths.ox.ac.uk/gilesm/files/gsoap.pdf

#include <math.h>
#include "soapH.h"
#include "calc.nsmap"

int main(int argc, char **argv)
{
   int m, s; /* master and slave sockets */
   struct soap soap;

   soap_init(&soap);
   m = soap_bind(&soap,NULL,atoi(argv[1]),100);
   for ( ; ; )
   { 
     s = soap_accept(&soap);
     soap_serve(&soap);
     soap_end(&soap);
   }

   return 0;
}

int ns__add (struct soap *soap, double a, double b, double *result)
{
   *result = a + b;

   return SOAP_OK;
}

int ns__sub (struct soap *soap, double a, double b, double *result)
{
    *result = a - b;

    return SOAP_OK;
}


