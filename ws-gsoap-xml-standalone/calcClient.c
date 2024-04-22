  #include "soapH.h"
  #include "ns.nsmap"

  int main(int argc, char **argv)
  {
    struct soap soap;
    char *serverURL;
    int a, b, res;

    if (argc != 4) {
      printf("Uso: %s http://servidor:puerto numero1 numero2\n", argv[0]);
      exit(0);
    }

    soap_init(&soap);

    serverURL = argv[1];
    a = atoi(argv[2]) ;
    b = atoi(argv[3]) ;

    soap_call_ns__suma(&soap, serverURL, "", a, b, &res);
    if (soap.error) {
        soap_print_fault(&soap, stderr); exit(1);
    }

    printf("Resultado = %d \n", res);

    soap_destroy(&soap);
    soap_end(&soap);
    soap_done(&soap);

    return 0;
  }

