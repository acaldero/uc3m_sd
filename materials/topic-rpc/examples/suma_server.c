
#include "suma.h"

bool_t suma_1_svc ( int a, int b, int *result,
                    struct svc_req *rqstp )
{
    *result = a + b; // código a añadir
  	return 1;        // 1 -> resultado ok
}

int sumar_1_freeresult ( SVCXPRT *transp,
                         xdrproc_t xdr_result, caddr_t result )
{
	xdr_free (xdr_result, result);
	return 1;
}

