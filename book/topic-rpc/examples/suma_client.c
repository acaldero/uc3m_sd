
#include "suma.h"

char *host = NULL ;
int sumar_1 ( int a, int b ) ;

int main ( int argc, char *argv[] )
{
   if (argc < 2) {
       printf ("Uso: %s <host>\n", argv[0]);
       exit (-1);
   }
   host = argv[1] ;
   
   int ret = sumar_1(1, 2);
   printf("Resultado de %d + %d es %d\n", 1, 2, ret) ;

   return 0 ;
}

int sumar_1 ( int a, int b )
{
   CLIENT *clnt ;
   enum clnt_stat retval ;
   int result ;

   clnt = clnt_create (host, SUMAR, SUMAVER, "tcp");
   if (clnt == NULL) {
       clnt_pcreateerror (host);
       exit (-1);
   }

   retval = suma_1(a, b, &result, clnt);
   if (retval != RPC_SUCCESS) {
       clnt_perror (clnt, "call failed");
   }

   clnt_destroy (clnt);

   return result ;
}

