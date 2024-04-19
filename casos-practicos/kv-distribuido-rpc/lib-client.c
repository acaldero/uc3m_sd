
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


// Global variables
CLIENT *clnt;


// Inicializar un array distribuido de N números enteros.
int init ( char  *nombre,  int  N )
{
    enum clnt_stat retval;
    int ret ;

    char *host = getenv("SERVER_IP") ;
    if (NULL == host) {
	printf("ERROR: please use SERVER_IP=server-host-name first\n") ;
	return (-1) ;
    }

    // Inicializar sesi'on RPC
    clnt = clnt_create(host, NANODT, NANODT_VERSION, "tcp") ;
    if (clnt == NULL) {
        clnt_pcreateerror(host) ;
        return (-1) ;
    }

    // init
    retval = d_init_1(nombre, N, &ret, clnt) ;
    if (retval != RPC_SUCCESS) {
        clnt_perror(clnt, "d_init_1: ") ;
        return (-1) ;
    }

    return 1 ;
}

// Inserta el valor en la posición i del array nombre.
int set ( char *nombre, int i, int valor )
{
    enum clnt_stat retval;
    int ret ;

    retval = d_set_1(nombre, i, i, &ret, clnt) ;
    if (retval != RPC_SUCCESS) {
	clnt_perror(clnt, "d_set_1: ") ;
	return (-1) ;
    }

    return 1 ;
}

// Recuperar el valor del elemento i del array nombre. 
int get ( char *nombre, int i, int *valor )
{
    enum clnt_stat retval;
    struct get_res getarg ;

    retval = d_get_1(nombre, i, &getarg, clnt) ;
    if (retval != RPC_SUCCESS) {
	clnt_perror(clnt, "d_get_1: ") ;
	return (-1) ;
    }

    *valor = getarg.value ;
    return 1 ;
}

// Finalizar un array distribuido de N números enteros.
int finalize ( char  *nombre,  int  N )
{
    clnt_destroy(clnt) ;

    return 1 ;
}

