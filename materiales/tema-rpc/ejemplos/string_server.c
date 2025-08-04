#include "string.h"

bool_t vocales_1_svc ( char *arg1, int *result,  struct svc_req *rqstp )
{
    char *vowels = "aeiou" ;
    char *pos = NULL ;

    (*result) = 0 ;
    while (*arg1 != '\0')
    {
       pos = strchr(vowels, *arg1) ;
       if (pos != NULL) {
           (*result)++ ;
       }
       arg1++;
    }

    return TRUE ;
 }

 bool_t first_1_svc ( char *arg1, char *result,  struct svc_req *rqstp )
 {
     *result = arg1[0] ;

     return TRUE ;
 }

 bool_t convertir_1_svc ( int n, char **result,  struct svc_req *rqstp )
 {
     *result = (char *) malloc(256) ;
     if (*result != NULL) {
         sprintf(*result, "%d", n) ;
     }

     return TRUE ;
 }

 int string_1_freeresult ( SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result )
 {
      xdr_free (xdr_result, result);
      return 1;
 }

