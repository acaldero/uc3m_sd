
// https://people.maths.ox.ac.uk/gilesm/files/gsoap.pdf

#include "lib.h"
#include "soapH.h"
#include "calc.nsmap"

int main(int argc, char **argv)
{
   int m, s; /* main and secondary sockets */
   struct soap soap;

   if (argc < 2) {
       printf("Uso: %s <puerto>\n", argv[0]) ;
       exit(0) ;
   }

   soap_init(&soap) ;
   m = soap_bind(&soap, NULL, atoi(argv[1]), 100) ;
   while (1)
   { 
      s = soap_accept(&soap) ;
      soap_serve(&soap) ;
      soap_end(&soap) ;
   }

   return 0;
}


int ns__add ( struct soap *soap, int a, int b, int *result )
{
    int ret ;

    ret = add(result, a, b) ;

    return SOAP_OK;
}

int ns__divide ( struct soap *soap, int a, int b, int *result )
{
    int ret ;

    ret = divide(result, a, b) ;

    return SOAP_OK;
}

int ns__neg ( struct soap *soap, int a, int *result )
{
    int ret ;

    ret = neg(result, a) ;

    return SOAP_OK;
}

