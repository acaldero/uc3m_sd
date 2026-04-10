  #include "soapH.h"
  #include "ns.nsmap"

  int main(int argc, char **argv)
  {
    int m, s; /* sockets del cliente (s) y servidor (m) */
    struct soap soap;

    if (argc < 2)
    {
        printf("Usage: %s <port>\n",argv[0]); exit(-1);
    }

    soap_init(&soap);

    m = soap_bind(&soap, NULL, atoi(argv[1]), 100);
    if (m < 0) {
        soap_print_fault(&soap, stderr); exit(-1);
    }

    while (1) {
       s = soap_accept(&soap);
       if (s < 0) {
           soap_print_fault(&soap, stderr); exit(-1);
       }
       soap_serve(&soap);
       soap_end(&soap);
    }

    return 0;
  }

  int ns__suma (struct soap *soap, int a, int b, int *res)
  {
    *res = a + b;
    return SOAP_OK;
  }

  int ns__resta (struct soap *soap, int a, int b, int *res)
  {
    *res = a - b;
    return SOAP_OK;
  }

