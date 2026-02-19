#include "vector.h"

int sumar_vector_1 ( char *host, t_vector *sumar_1_v )
{
    CLIENT *clnt;
   enum clnt_stat retval_1;
   int result_1;

   clnt = clnt_create (host, VECTOR, VECTORVER, "tcp");
   if (clnt == NULL) {
       clnt_pcreateerror (host); exit (-1);
   }
   retval_1 = sumar_1(*sumar_1_v, &result_1, clnt);
   if (retval_1 != RPC_SUCCESS) {
       clnt_perror (clnt, "call failed"); exit(-1) ;
   }
   clnt_destroy (clnt);

   return result_1;
}

int main ( int argc, char *argv[] )
{
   long MAX;
   t_vector sumar_1_v;
   int ret;

   if (argc < 2) {
       printf ("Uso: %s <server host>\n", argv[0]);
       exit (1);
   }

   MAX = 100;
   sumar_1_v.t_vector_len= MAX;
   sumar_1_v.t_vector_val= (int *) malloc(MAX * sizeof(int));
   for (int i =0; i < MAX; i ++) {
          sumar_1_v.t_vector_val[i] = 2;	
   }

   ret = sumar_vector_1 (argv[1], &sumar_1_v);
   printf("La suma es %d\n", ret);

   free (sumar_1_v.t_vector_val);
   return (0);
}

