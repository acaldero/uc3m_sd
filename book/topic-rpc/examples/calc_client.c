 #include "calc.h"

 int sumar ( char *host, int a, int b )
 {
    int ret ;
    CLIENT *clnt;
    enum clnt_stat retval_1;

    clnt = clnt_create (host, SUMAR, SUMAVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror (host); exit (-1);
    }
    retval_1 = suma_1(a, b, &ret, clnt);
    if (retval_1 != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed"); exit (-1);
    }
    clnt_destroy (clnt);
    return ret ;
 }

 int restar ( char *host, int a, int b )
 {
    int ret ;
    CLIENT *clnt;
    enum clnt_stat retval_1;

    clnt = clnt_create (host, SUMAR, SUMAVER, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror (host); exit (-1);
    }
    retval_1 = resta_1(a, b, &ret, clnt);
    if (retval_1 != RPC_SUCCESS) {
        clnt_perror (clnt, "call failed"); exit (-1);
    }
    clnt_destroy (clnt);
    return ret ;
 }

  int main ( int argc, char *argv[] )
  {
     int res ;

     if (argc < 2) {
         printf ("usage: %s server_host\n", argv[0]);
         exit (1);
     }

     res = sumar(argv[1], 1, 2) ;
     printf("1 + 2 = %d\n", res) ;

     res = restar(argv[1], 1, 2) ;
     printf("1 - 2 = %d\n", res) ;

     return 0;
  }

