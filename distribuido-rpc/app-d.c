
/*
 *  Copyright 2020-2021 Felix Garcia Carballeira, Alejandro Calderon Mateos,
 *
 *  This file is part of nanodt proyect.
 *
 *  nanodt is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nanodt is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with nanodt.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "message.h"


int   N = 10 ;
char *A = "nombre" ;


int main ( int argc, char *argv[] )
{
    CLIENT *clnt;
    enum clnt_stat retval;
    int ret ;

    if (argc < 2)
    {
        printf("Usage: %s <server_ip>\n", argv[0]) ;
        exit(-1) ;
    }

    // Inicializar sesi'on RPC
    char *host = argv[1] ;
    clnt = clnt_create(host, NANODT, NANODT_VERSION, "tcp") ;
    if (clnt == NULL) {
        clnt_pcreateerror(host) ;
        exit(-1) ;
    }

    // init
    retval = d_init_1(A, N, &ret, clnt) ;
    if (retval != RPC_SUCCESS) {
        clnt_perror(clnt, "d_init_1: ") ;
        exit(-1) ;
    }
    printf("d_init(\"%s\", %d) -> %d\n", A, N, ret) ;

    for (int i=0; i<N; i++)
    {
	    // set
	    retval = d_set_1(A, 100+i, i, &ret, clnt) ;
	    if (retval != RPC_SUCCESS) {
		clnt_perror(clnt, "d_set_1: ") ;
		exit(-1) ;
	    }
	    printf("d_set(\"%s\", %d, 0x%x) -> %d\n", A, 100+i, i, ret) ;
    }

    for (int i=0; i<N; i++)
    {
	    // get
	    struct get_res getarg ;
	    retval = d_get_1(A, 100+i, &getarg, clnt) ;
	    if (retval != RPC_SUCCESS) {
		clnt_perror(clnt, "d_get_1: ") ;
		exit(-1) ;
	    }
	    printf("d_get(\"%s\", %d) -> 0x%x\n", A, 100+i, getarg.value) ;
    }

    /* Finalizar sesi'on RPC */
    clnt_destroy(clnt) ;
    return 0 ;
}

