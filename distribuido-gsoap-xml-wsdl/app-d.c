
//
// https://www.genivia.com/dev.html#client-c
//

#include "calc.nsmap" // XML namespace mapping table (only needed once at the global level)
#include "soapH.h"    // client stubs, serializers, etc.

int main ( int argc, char *argv[] )
{
  struct soap *soap;
  double sum;
  int ret;

  soap = soap_new(); // allocate and initialize a context
  if (NULL == soap) {
      return -1;
  }

  ret = soap_call_ns2__add(soap, NULL, NULL, 1.23, 4.56, &sum) ;
  if (SOAP_OK == ret) {
      printf("Sum = %g\n", sum);
  }
  else {
      soap_print_fault(soap, stderr);
  }

  soap_destroy(soap); // delete managed deserialized C++ instances
  soap_end(soap);     // delete other managed data
  soap_free(soap);    // free the soap struct context data

  return 0;
}

