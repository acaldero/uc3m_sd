
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
#include "message.h"


// Sumar: *r = a + b Y devuelve 0
int add ( int *r, int a, int b )
{
    CLIENT *clnt;
    enum clnt_stat retval;
    struct result ret ;

    char *host = getenv("SERVER_IP") ;
    if (NULL == host) {
	printf("ERROR: please use SERVER_IP=server-host-name first\n") ;
	exit(-1) ;
    }

    // Inicializar sesi'on RPC
    clnt = clnt_create(host, CALC, CALC_VERSION, "tcp") ;
    if (clnt == NULL) {
        clnt_pcreateerror(host) ;
        exit(-1) ;
    }

    // init
    retval = d_add_1(a, b, &ret, clnt) ;
    if (retval != RPC_SUCCESS) {
        clnt_perror(clnt, "d_add_1: ") ;
        exit(-1) ;
    }

    clnt_destroy(clnt) ;

    *r = ret.value ;
    return ret.status ;
}

// Divide dos números enteros: *r = a + b Y devuele (-1 si b==0 / 0 si b!=0)
int divide ( int *r, int a, int b )
{
    CLIENT *clnt;
    enum clnt_stat retval;
    struct result ret ;

    char *host = getenv("SERVER_IP") ;
    if (NULL == host) {
	printf("ERROR: please use SERVER_IP=server-host-name first\n") ;
	exit(-1) ;
    }

    // Inicializar sesi'on RPC
    clnt = clnt_create(host, CALC, CALC_VERSION, "tcp") ;
    if (clnt == NULL) {
        clnt_pcreateerror(host) ;
        exit(-1) ;
    }

    // init
    retval = d_divide_1(a, b, &ret, clnt) ;
    if (retval != RPC_SUCCESS) {
        clnt_perror(clnt, "d_divide_1: ") ;
        exit(-1) ;
    }

    clnt_destroy(clnt) ;

    *r = ret.value ;
    return ret.status ;
}

// Cambio de signo: *r = -a Y devuelve 0
int neg ( int *r, int a )
{
    CLIENT *clnt;
    enum clnt_stat retval;
    struct result ret ;

    char *host = getenv("SERVER_IP") ;
    if (NULL == host) {
	printf("ERROR: please use SERVER_IP=server-host-name first\n") ;
	exit(-1) ;
    }

    // Inicializar sesi'on RPC
    clnt = clnt_create(host, CALC, CALC_VERSION, "tcp") ;
    if (clnt == NULL) {
        clnt_pcreateerror(host) ;
        exit(-1) ;
    }

    // init
    retval = d_neg_1(a, &ret, clnt) ;
    if (retval != RPC_SUCCESS) {
        clnt_perror(clnt, "d_neg_1: ") ;
        exit(-1) ;
    }

    clnt_destroy(clnt) ;

    *r = ret.value ;
    return ret.status ;
}


