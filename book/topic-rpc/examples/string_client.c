#include "string.h"

void test_string_1 ( char *host, char *cadena, int numero )
{
   CLIENT *clnt;
   enum clnt_stat retval_1;
   int   result_1;
   char  result_2;
   char *result_3;

   clnt = clnt_create (host, STRING, STRINGVER, "udp");
   if (clnt == NULL) {
       clnt_pcreateerror (host); exit (1);
   }

   retval_1 = vocales_1(cadena, &result_1, clnt);
   if (retval_1 != RPC_SUCCESS) {
       clnt_perror (clnt, "call failed"); exit (1);
   }
   printf(" vocales   = %d\n", result_1) ;

   retval_1 = first_1(cadena, &result_2, clnt);
   if (retval_1 != RPC_SUCCESS) {
       clnt_perror (clnt, "call failed"); exit (1);
   }
   printf(" first     = %c\n", result_2) ;

   result_3 = malloc(256) ;
   if (NULL == result_3) {
       perror("malloc: ") ; exit (1);
   }
   retval_1 = convertir_1(numero, &result_3, clnt);
   if (retval_1 != RPC_SUCCESS) {
       clnt_perror (clnt, "call failed"); exit (1);
   }
   printf(" convertir = %s\n", result_3) ;
   free(result_3) ;

   clnt_destroy (clnt);
}

int main (int argc, char *argv[])
{
   if (argc < 2) {
       printf ("Uso: %s <server host>\n", argv[0]);
       exit (1);
   }

   test_string_1 (argv[1], "murcielago", 12345) ;
   return 0 ;
}

