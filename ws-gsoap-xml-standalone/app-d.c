
// https://people.maths.ox.ac.uk/gilesm/files/gsoap.pdf

#include "soapH.h"
#include "calc.nsmap"

const char server[] = "localhost:12345";

int main(int argc, char **argv)
{
   struct soap soap;
   double a, b, result;

   if (argc < 3)
   {
       printf("Usage:");
       printf(" %s <a|s> <operand 1> <operand 2>\n", argv[0]);
       exit(-1);
   }

   soap_init(&soap);
   a = strtod(argv[2], NULL);
   b = strtod(argv[3], NULL);

   switch (*argv[1])
   {
      case 'a':
           soap_call_ns__add(&soap, server, "", a, b, &result);
           break;
      case 's':
           soap_call_ns__sub(&soap, server, "", a, b, &result);
           break;
   }
   if (soap.error)
       soap_print_fault(&soap, stderr);
   else
       printf("result = %g\n", result);

   return 0;
}


