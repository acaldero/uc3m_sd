
/*
 *  Copyright 2020-2023 Felix Garcia Carballeira, Alejandro Calderon Mateos,
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
#include "lib.h"


int   N = 10 ;
char *A = "nombre" ;


int main ( int argc, char *argv[] )
{
    int ret ;
    int val ;

    // init
    ret = init(A, N) ;
    if (ret < 0) {
        printf("init: error code %d\n", ret) ;
        exit(-1) ;
    }

    for (int i=0; i<N; i++)
    {
	    // set
	    ret = set (A, 100+i, i) ;
	    if (ret < 0) {
		printf("set: error code %d\n", ret) ;
		exit(-1) ;
	    }
	    printf("set(\"%s\", %d, 0x%x)\n", A, 100+i, i) ;
    }

    for (int i=0; i<N; i++)
    {
	    // get
	    ret = get (A, 100+i, &val) ;
	    if (ret < 0) {
		printf("get: error code %d\n", ret) ;
		exit(-1) ;
	    }
	    printf("get(\"%s\", %d) -> 0x%x\n", A, 100+i, val) ;
    }

    return 0 ;
}

