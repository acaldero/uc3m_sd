
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
#include "lib-client.h"


int   N = 10 ;
char *A = "nombre" ;
int   E =  1 ;
int   V = 0x123 ;


int main ( int argc, char *argv[] )
{
    int ret ;
    int val ;

    // init
    ret = d_init(A, N) ;
    if (ret < 0) {
        printf("d_init: error code %d\n", ret) ;
        exit(-1) ;
    }

    // set
    ret = d_set (A, E, V) ;
    if (ret < 0) {
        printf("d_set: error code %d\n", ret) ;
        exit(-1) ;
    }
    printf("d_set(\"%s\", %d, 0x%x)\n", A, E, V) ;

    // get
    ret = d_get (A, E, &val) ;
    if (ret < 0) {
        printf("d_get: error code %d\n", ret) ;
        exit(-1) ;
    }
    printf("d_get(\"%s\", %d) -> 0x%x\n", A, E, val) ;

    return 0 ;
}

