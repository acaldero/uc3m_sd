
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


int main ( int argc, char *argv[] )
{
    int   N1 = 20 ;
    int   N2 = 10 ;
    int   val, ret ;

    // add
    ret = d_add(&val, N1, N2) ;
    printf("%d = add(%d, %d, %d)\n", ret, val, N1, N2) ;

    // sub
    ret = d_divide(&val, N1, N2) ;
    printf("%d = divide(%d, %d, %d)\n", ret, val, N1, N2) ;

    // neg
    ret = d_neg(&val, N2) ;
    printf("%d = neg(%d, %d)\n", ret, val, N2) ;

    return 0 ;
}

