#include "calc.h"

bool_t suma_1_svc ( int a, int b, int *result,  struct svc_req *rqstp )
{
    *result = a + b ;
    return TRUE ;
}

bool_t resta_1_svc ( int a, int b, int *result,  struct svc_req *rqstp )
{
    *result = a - b ;
    return TRUE ;
}

int sumar_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
   xdr_free (xdr_result, result);
   return 1;
}

