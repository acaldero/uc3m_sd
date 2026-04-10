#include "CalculatorSoap.nsmap"
#include "soapH.h"

int main ( int argc, char *argv[] )
{
  struct soap *soap;
  int ret;
  struct _tempuri__Add args ;
  struct _tempuri__AddResponse res ;

  soap = soap_new();
  if (NULL == soap) {
      return -1;
  }

  args.intA = 1;
  args.intB = 2;
  ret = soap_call___tempuri__Add(soap, NULL, NULL, &args, &res) ;
  if (SOAP_OK != ret) {
      soap_print_fault(soap, stderr);
      return -1;
  }

  printf("Sum = %d\n", res.AddResult);

  soap_destroy(soap);
  soap_end(soap);
  soap_free(soap);

  return 0;
}
