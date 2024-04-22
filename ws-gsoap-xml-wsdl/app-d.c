
//
// https://www.genivia.com/dev.html#client-c
//

#include "calc.nsmap"
#include "soapH.h"

int main ( int argc, char *argv[] )
{
  struct soap *soap ;
  int ret ;
  double res ;

  soap = soap_new();
  if (NULL == soap) {
      return -1;
  }

  ret = soap_call_ns2__add(soap, NULL, NULL, 1.2, 2.3, &res) ;
  if (SOAP_OK != ret) {
      soap_print_fault(soap, stderr);
      return -1;
  }

  printf("Sum = %g\n", res);

  soap_destroy(soap);
  soap_end(soap);
  soap_free(soap);

  return 0;
}
