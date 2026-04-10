#include "vector.h"

bool_t sumar_1_svc ( t_vector v, int *result, struct svc_req *rqstp )
{
   *result = 0;
   for (int i=0; i<v.t_vector_len; i++)
         *result = *result + v.t_vector_val[i] ;
   return TRUE;
}

int vector_1_freeresult ( SVCXPRT *transp, xdrproc_t xdr_result,caddr_t result )
{
    xdr_free (xdr_result, result);
    return 1;
}

