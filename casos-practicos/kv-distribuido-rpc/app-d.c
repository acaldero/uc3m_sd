
/*
 *  Copyright 2020-2024 Felix Garcia Carballeira, Alejandro Calderon Mateos,
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
#include "lib-client.h"


int   N = 10 ;
char *A = "nombre" ;


int main ( int argc, char *argv[] )
{
    int ret ;
    int valor ;

    if (argc < 2)
    {
        printf("Usage: %s <server_ip>\n", argv[0]) ;
        exit(-1) ;
    }
    setenv("SERVER_IP", argv[1], 1) ;

    // init
    ret = init(A, N) ;
    if (ret < 0) { exit(-1) ; }
    printf("d_init(\"%s\", %d) -> %d\n", A, N, ret) ;

    for (int i=0; i<N; i++)
    {
	    // set
            ret = set(A, 100+i, i) ;
	    if (ret < 0) { exit(-1) ; }
	    printf("d_set(\"%s\", %d, 0x%x) -> %d\n", A, 100+i, i, ret) ;
    }

    for (int i=0; i<N; i++)
    {
	    // get
            ret = get(A, 100+i, &valor) ;
	    if (ret < 0) { exit(-1) ; }
	    printf("d_get(\"%s\", %d) -> 0x%x\n", A, 100+i, valor) ;
    }

    /* Finalizar sesi'on RPC */
    finalize(A, N) ;
    return 0 ;
}

